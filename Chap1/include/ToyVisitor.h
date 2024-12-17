#include "clang/AST/Decl.h"
#include "clang/AST/DeclVisitor.h"
#include "llvm/Support/raw_ostream.h"

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