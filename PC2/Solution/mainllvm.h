#ifndef __MAINLLVM_H__
#define __MAINLLVM_H__

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include <memory>
#include <string>

class MainLLVM
{
public:
    MainLLVM();
    void exec(const std::string &program);

private:
    void saveModuleToFile(const std::string &fileName);
    void moduleInit();

    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<llvm::IRBuilder<>> builder;
};

#endif