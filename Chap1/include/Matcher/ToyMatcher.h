#pragma once

#include "clang/AST/Decl.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "llvm/Support/raw_ostream.h"

namespace matcher {

namespace cam = clang::ast_matchers;

static const char* MatchID = "match-id";

cam::DeclarationMatcher M = 
    cam::functionDecl(cam::decl().bind(MatchID), cam::matchesName("max"));

class MatchCallback: public cam::MatchFinder::MatchCallback {
public:
  virtual void run(const cam::MatchFinder::MatchResult &result) final {
    if (const auto *FD = result.Nodes.getNodeAs<clang::FunctionDecl>(MatchID)) {
      const auto &SM = result.SourceManager;
      const auto &Loc = FD->getLocation();
      llvm::outs() << "Found 'max' function at " << SM->getFilename(Loc) << ":"
                   << SM->getSpellingLineNumber(Loc) << ":"
                   << SM->getSpellingColumnNumber(Loc) << "\n";
    }
  }
};

} // namespace matcher