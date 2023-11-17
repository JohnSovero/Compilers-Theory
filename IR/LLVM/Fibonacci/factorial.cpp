#include "llvm/ADT/APInt.h"
#include "llvm/IR/Verifier.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

using namespace llvm;

static Function *CreateFibFunction(Module *M, LLVMContext &Context) {
  // Create the fib function and insert it into module M. This function is said
  // to return an int and take an int parameter.
  FunctionType *FacTy = FunctionType::get(Type::getInt32Ty(Context), {Type::getInt32Ty(Context)}, false);
  Function *FactF = Function::Create(FacTy, Function::ExternalLinkage, "factorial", M);

  // Add a basic block to the function.
  BasicBlock *BB = BasicBlock::Create(Context, "EntryBlock", FactF);

  // Get pointers to the constants.
  Value *One = ConstantInt::get(Type::getInt32Ty(Context), 1);
  Value *Two = ConstantInt::get(Type::getInt32Ty(Context), 2);

  // Get pointer to the integer argument of the add1 function...
  Argument *N = &*FactF->arg_begin(); // Get the arg.
  N->setName("n");            // Give it a nice symbolic name for fun.

  // Create the true_block.
  BasicBlock *RetBB = BasicBlock::Create(Context, "return", FactF);
  // Create an exit block.
  BasicBlock* RecurseBB = BasicBlock::Create(Context, "recurse", FactF);

  // Create the "if (arg <= 1) 
  Value *CondInst = new ICmpInst(*BB, ICmpInst::ICMP_SLE, N, One, "cond");
  BranchInst::Create(RetBB, RecurseBB, CondInst, BB);

  // if(arg <= 1) return 1
  ReturnInst::Create(Context, One, RetBB);

  // create fact(x-1)
  Value *Sub = BinaryOperator::CreateSub(N, One, "arg", RecurseBB);
  CallInst *CallFactX1 = CallInst::Create(FactF, Sub, "fact1", RecurseBB);
  CallFactX1->setTailCall();

  // n * fact(n - 1)
  Value *ans = BinaryOperator::CreateMul(N, CallFactX1, "answer", RecurseBB);

  // Create the return instruction and add it to the basic block
  ReturnInst::Create(Context, ans, RecurseBB);

  return FactF;
}

int main(int argc, char **argv) {
  int n = argc > 1 ? atol(argv[1]) : 5;

  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  LLVMContext Context;

  // Create some module to put our function into it.
  std::unique_ptr<Module> Owner(new Module("test", Context));
  Module *M = Owner.get();

  // We are about to create the "fib" function:
  Function *FibF = CreateFibFunction(M, Context);

  // Now we going to create JIT
  std::string errStr;
  ExecutionEngine *EE =
    EngineBuilder(std::move(Owner))
    .setErrorStr(&errStr)
    .create();

  if (!EE) {
    errs() << argv[0] << ": Failed to construct ExecutionEngine: " << errStr
           << "\n";
    return 1;
  }

  errs() << "verifying... ";
  if (verifyModule(*M)) {
    errs() << argv[0] << ": Error constructing function!\n";
    return 1;
  }

  errs() << "OK\n";
  errs() << "We just constructed this LLVM module:\n\n---------\n" << *M;
  errs() << "---------\nstarting fibonacci(" << n << ") with JIT...\n";

  // Call the Fibonacci function with argument n:
  std::vector<GenericValue> Args(1);
  Args[0].IntVal = APInt(32, n);
  GenericValue GV = EE->runFunction(FibF, Args);

  // import result of execution
  outs() << "Result: " << GV.IntVal << "\n";

  return 0;
}