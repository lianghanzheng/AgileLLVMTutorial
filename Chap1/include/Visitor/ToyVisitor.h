#pragma once

#include "clang/AST/Decl.h"
#include "clang/AST/DeclVisitor.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "llvm/Support/raw_ostream.h"

namespace declv {

class ToyVisitor : public clang::DeclVisitor<ToyVisitor> {
public:
  void VisitFunctionDecl(const clang::FunctionDecl *FD) {
    llvm::outs() << "Function: " << FD->getName() << "\n";
    for (const auto param: FD->parameters()) {
      Visit(param);
    }
  }

  void VisitParmVarDecl(const clang::ParmVarDecl *PVD) {
    llvm::outs() << "  -> ParamName: " << PVD->getName() << "\n";
  }

  void VisitTranslationUnitDecl(const clang::TranslationUnitDecl *TU) {
    for (const auto decl: TU->decls()) {
      Visit(decl);
    }
  }
};

} // namespace declv

namespace recursivev {

class ToyVisitor: public clang::RecursiveASTVisitor<ToyVisitor> {
public:
  bool VisitFunctionDecl(const clang::FunctionDecl *FD) {
    llvm::outs() << "Function: " << FD->getName() << "\n";
    return true;
  }

  bool VisitParmVarDecl(const clang::ParmVarDecl *PVD) {
    llvm::outs() << "  -> Paramname: " << PVD->getName() << "\n";
    return true;
  }
}; 

} // namespace recursivev