#include "libs/LabeledExprBaseVisitor.h"
#include "libs/LabeledExprParser.h"
#include <any>
#include <iostream>
#include <map>
#include <string>

#include <llvm/ADT/APFloat.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <vector>

using namespace llvm;

class EvalVisitorImpl : LabeledExprBaseVisitor
{
	auto TheContext = std::make_unique<llvm::LLVMContext>();
	auto TheModule = std::make_unique<Module>("Mi cool jit", *TheContext);
	auto TheBuilder = std::make_unique<IRBuilder<>>(*TheContext);
	std::map<std::string, std::any> memory;

public:
	/* ID '=' expr NEWLINE */
	std::any visitAssign(LabeledExprParser::AssignContext *ctx)
	{
		std::string id = ctx->ID()->getText();
		std::cout<<id;
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