#include <cstdio>
#include <fstream>
#include <string>

#include "antlr4-runtime.h"
#include "libs/LabeledExprLexer.h"
#include "libs/LabeledExprParser.h"

#include "libs/LabeledExprBaseVisitor.h"
#include "libs/LabeledExprParser.h"
#include <any>
#include <iostream>
#include <map>
#include <string>

#include <llvm-15/llvm/IR/BasicBlock.h>
#include <llvm-15/llvm/IR/DerivedTypes.h>
#include <llvm-15/llvm/IR/IRBuilder.h>
#include <llvm-15/llvm/IR/Intrinsics.h>
#include <llvm-15/llvm/IR/LLVMContext.h>
#include <llvm-15/llvm/IR/Module.h>
#include <llvm-15/llvm/IR/Type.h>

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <vector>

using namespace llvm;

static std::unique_ptr<LLVMContext> TheContext;
static std::unique_ptr<Module> TheModule;
static std::unique_ptr<IRBuilder<>> Builder;
static std::map<std::string, Value *> NamedValues;

class EvalVisitorImpl : LabeledExprBaseVisitor
{
	std::map<std::string, std::any> memory;

public:
	/* ID '=' expr NEWLINE */
	std::any visitAssign(LabeledExprParser::AssignContext *ctx)
	{
		std::string id = ctx->ID()->getText();
		std::cout << id;
		auto value = visit(ctx->expr());
		memory[id] = value;
		return std::any(value);
	}

	/* expr NEWLINE */
	std::any visitPrintExpr(LabeledExprParser::PrintExprContext *ctx)
	{
		auto value = visit(ctx->expr());
		std::cout << std::any_cast<int>(value) << '\n';
		return std::any(value);
	}

	/* INT */
	std::any visitInt(LabeledExprParser::IntContext *ctx)
	{

		return std::any(std::stoi(ctx->NUM()->getText()));
	}

	/* ID */
	std::any visitId(LabeledExprParser::IdContext *ctx)
	{
		std::string id = ctx->ID()->getText();
		if (memory.count(id))
			return memory[id];
		return std::any(id);
	}

	/* expr op=('*'|'/') expr */
	std::any visitMulDiv(LabeledExprParser::MulDivContext *ctx)
	{
		auto left = std::any_cast<int>(visit(ctx->expr(0)));
		auto right = std::any_cast<int>(visit(ctx->expr(1)));
		int resp;
		if (ctx->op->getType() == LabeledExprParser::MUL)
		{
			resp = left * right;
		}
		else
		{
			resp = left / right;
		}
		return std::any(resp);
	}

	/* expr op=('+'|'-') expr */
	std::any visitAddSub(LabeledExprParser::AddSubContext *ctx)
	{
		auto left = std::any_cast<int>(visit(ctx->expr(0)));
		auto right = std::any_cast<int>(visit(ctx->expr(1)));
		int resp;
		if (ctx->op->getType() == LabeledExprParser::ADD)
		{
			resp = left + right;
		}
		else
		{
			resp = left - right;
		}
		return std::any(resp);
	}

	/* '(' expr ')' */
	std::any visitParens(LabeledExprParser::ParensContext *ctx)
	{
		return visit(ctx->expr());
	}

	std::any visitProg(LabeledExprParser::ProgContext *ctx)
	{
		return visitChildren(ctx);
	}
};

int main(int argc, char **argv)
{

	if (argc <= 1)
		return -1;
	std::ifstream is;
	is.open(argv[1]);
	antlr4::ANTLRInputStream input(is);
	LabeledExprLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	LabeledExprParser parser(&tokens);
	auto tree = parser.prog();
	EvalVisitorImpl eval;
	eval.visitProg(tree);
	return 0;
}