#include "Visitor/ToyFrontendAction.h"
#include "Matcher/ToyMatcher.h"

#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"

#include <cstdlib>
#include <string>

// TODO: replace this by cl::opt.
enum Opt { DeclVisitor, RecursiveVisitor, Matcher };
Opt tmpOpt = Opt::Matcher;

static llvm::cl::OptionCategory toolCategory("clang-toy options");

static llvm::cl::extrahelp CommonHelp(
    clang::tooling::CommonOptionsParser::HelpMessage);

static llvm::cl::opt<std::string> UseDeclOrRecursive {
    "visitor-type", llvm::cl::init("decl"),
    llvm::cl::desc {"the argument should be either 'decl', 'recurs', or 'matcher' to choose the visitor"}};

int main(int argc, const char **argv) {
  auto expectedParser = clang::tooling::CommonOptionsParser::create(argc, argv, toolCategory);
  
  if (!expectedParser) {
    llvm::errs() << expectedParser.takeError();
    return 1;
  }

  clang::tooling::ClangTool tool(
        expectedParser->getCompilations(),
        expectedParser->getSourcePathList());

  switch (tmpOpt) {
  case Opt::DeclVisitor:
      return tool.run(clang::tooling::newFrontendActionFactory<
          declv::ToyFrontendAction>().get());
  case Opt::RecursiveVisitor:
      return tool.run(clang::tooling::newFrontendActionFactory<
          recursivev::ToyFrontendAction>().get());
  case Opt::Matcher:
      matcher::MatchCallback MC;
      clang::ast_matchers::MatchFinder Finder;
      Finder.addMatcher(matcher::M, &MC);

      return tool.run(clang::tooling::newFrontendActionFactory(&Finder).get());
  }

}