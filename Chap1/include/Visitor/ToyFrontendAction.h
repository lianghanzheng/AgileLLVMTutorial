#pragma once

#include "ToyConsumer.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/FrontendAction.h"
#include "llvm/ADT/StringRef.h"
#include <memory>

namespace declv {

class ToyFrontendAction: public clang::ASTFrontendAction {
public:
  virtual std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &CI, 
                    llvm::StringRef File) override {
    return std::make_unique<ToyConsumer>();
  }
};

} // namespace declv

namespace recursivev {

class ToyFrontendAction: public clang::ASTFrontendAction {
public:
  virtual std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &CI, 
                    llvm::StringRef File) override {
    return std::make_unique<ToyConsumer>();
  }
};

} // namespace recursivev