#pragma once

#include "ToyVisitor.h"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/Frontend/ASTConsumers.h"
#include <memory>

namespace declv {

class ToyConsumer: public clang::ASTConsumer {
public:
  ToyConsumer() : V(std::make_unique<ToyVisitor>()) {}
  
  virtual void HandleTranslationUnit(clang::ASTContext &context) override {
    V->Visit(context.getTranslationUnitDecl());
  }

private:
  std::unique_ptr<ToyVisitor> V;
};

} // namespace declv

namespace recursivev {

class ToyConsumer: public clang::ASTConsumer {
public:
  ToyConsumer() : V(std::make_unique<ToyVisitor>()) {}
  
  virtual void HandleTranslationUnit(clang::ASTContext &context) override {
    V->TraverseDecl(context.getTranslationUnitDecl());
  }

private:
  std::unique_ptr<ToyVisitor> V;
};

} // namespace recursivev