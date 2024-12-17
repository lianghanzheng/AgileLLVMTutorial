#include "ToyConsumer.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/FrontendActions.h"
#include "llvm/ADT/StringRef.h"
#include <memory>

class ToyFrontendAction: public clang::ASTFrontendAction {
public:
  virtual std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &CI, 
                    llvm::StringRef File) override {
    return std::make_unique<ToyConsumer>();
  }
};
