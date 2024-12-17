#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"

static llvm::cl::OptionCategory toolCategory("clang-toy options");

static llvm::cl::extrahelp CommonHelp(
    clang::tooling::CommonOptionsParser::HelpMessage);

int main(int argc, const char **argv) {
  auto expectedParser = clang::tooling::CommonOptionsParser::create(argc, argv, toolCategory);
  
  if (!expectedParser) {
    llvm::errs() << expectedParser.takeError();
    return 1;
  }

  clang::tooling::ClangTool tool(
        expectedParser->getCompilations(),
        expectedParser->getSourcePathList());

  return tool.run(clang::tooling::newFrontendActionFactory<clang::SyntaxOnlyAction>().get());
}