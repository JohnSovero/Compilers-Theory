#include "pcdosVisitorImpl.h"
#include "libs/pcdosParser.h"
#include <any>
#include <llvm/ADT/APFloat.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <memory>
#include <string>

std::any pcdosVisitorImpl::visitProg(pcdosParser::ProgContext *ctx) {
  std::cout << "visitProg\n";
  // Creates the main Function
  std::vector<llvm::Type *> Doubles(0, llvm::Type::getDoubleTy(*context));
  llvm::FunctionType *FT = llvm::FunctionType::get(llvm::Type::getVoidTy(*context), Doubles, false);

  F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "_anon_", module.get());

  // Creates the entry to the function
  llvm::BasicBlock *BB = llvm::BasicBlock::Create(*context, "entry", F);
  builder->SetInsertPoint(BB);

  // visit the body
  visitChildren(ctx);

  // Close the main Function
  builder->CreateRet(nullptr);

  return std::any(nullptr);
}

std::any pcdosVisitorImpl::visitPrintExpr(pcdosParser::PrintExprContext *ctx) {
  std::cout << "visitPrintExpr\n";

  llvm::Value *value = std::any_cast<llvm::Value *>(visit(ctx->expr()));
  value->print(llvm::errs(), false);

	return std::any();
}

std::any pcdosVisitorImpl::visitAssign(pcdosParser::AssignContext *ctx) {
  std::cout << "visitAssign\n";
  std::string id = std::any_cast<std::string>(ctx->ID()->getText());

  auto value = visit(ctx->expr());

  if (value.type() == typeid(llvm::Value *))
  {
    // Create an alloca for this variable.
    llvm::AllocaInst *allocaInst = CreateEntryBlockAlloca(id);
    // Cast the value any to a llvm::Value *
    llvm::Value *valueToStore = std::any_cast<llvm::Value *>(value);
    // Create the IR code for the assignment instruction
    builder->CreateStore(valueToStore, allocaInst);
    // Store the value in the memory
    memory[id] = valueToStore;
  }
  return std::any(nullptr);
}

std::any pcdosVisitorImpl::visitStatdef(pcdosParser::StatdefContext *ctx) {
  std::cout << "visitStatdef\n";
  return visitChildren(ctx);
}

std::any
pcdosVisitorImpl::visitStatextern(pcdosParser::StatexternContext *ctx) {
  std::cout << "visitStatextern\n";
  return visitChildren(ctx);
}

std::any pcdosVisitorImpl::visitBlank(pcdosParser::BlankContext *ctx) {
  std::cout << "visitBlank\n";
  return visitChildren(ctx);
}

std::any pcdosVisitorImpl::visitCall(pcdosParser::CallContext *ctx) {
  std::cout << "visitCall\n";
  return visitChildren(ctx);
}

std::any pcdosVisitorImpl::visitNumber(pcdosParser::NumberContext *ctx) {
  std::cout << "visitNumber\n";
  auto numVal = std::stod(ctx->NUMBER()->getText());
  llvm::Value *val  = llvm::ConstantFP::get(*context, llvm::APFloat(numVal));
  return std::any(val);
}

std::any pcdosVisitorImpl::visitMulDiv(pcdosParser::MulDivContext *ctx) {
  std::cout << "visitMulDiv\n";
  return visitChildren(ctx);
}

std::any pcdosVisitorImpl::visitAddSub(pcdosParser::AddSubContext *ctx) {
  std::cout << "visitAddSub\n";
  llvm::Value *L = std::any_cast<llvm::Value *>(visit(ctx->expr(0)));
  llvm::Value *R = std::any_cast<llvm::Value *>(visit(ctx->expr(1)));
  if (ctx->op->getType() == pcdosParser::ADD) 
  {
    return std::any(builder->CreateFAdd(L, R, "addTemp"));
  } 
  else 
  {
    return std::any(builder->CreateFSub(L, R, "subTemp"));
  }
}

std::any pcdosVisitorImpl::visitParens(pcdosParser::ParensContext *ctx) {
  std::cout << "visitParens\n";
  return visitChildren(ctx);
}

std::any pcdosVisitorImpl::visitId(pcdosParser::IdContext *ctx) {
  std::cout << "visitId\n";
  std::string idName = ctx->ID()->getText();
  // Check if the variable is in the memory
  if (memory.find(idName) != memory.end())
    return std::any(memory[idName]);
  return std::any(idName);
}

std::any pcdosVisitorImpl::visitProto(pcdosParser::ProtoContext *ctx) {
  std::cout << "visitProto\n";
  return visitChildren(ctx);
}

std::any pcdosVisitorImpl::visitDef(pcdosParser::DefContext *ctx) {
  std::cout << "visitDef\n";
  return visitChildren(ctx);
}

std::any pcdosVisitorImpl::visitExtern(pcdosParser::ExternContext *ctx) {
  std::cout << "visitExtern\n";
  return visitChildren(ctx);
}

// vim: set ts=2:sw=2:et:sts=2: