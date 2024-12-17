#include "ToyFrontendAction.h"

#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"

#include <string>

static llvm::cl::OptionCategory toolCategory("clang-toy options");

static llvm::cl::extrahelp CommonHelp(
    clang::tooling::CommonOptionsParser::HelpMessage);

static llvm::cl::opt<std::string> UseDeclOrRecursive {
    "visitor-type", llvm::cl::init("decl"),
    llvm::cl::desc {"the argument should be either 'decl' or 'recursive' to choose the visitor"}};

int main(int argc, const char **argv) {
  auto expectedParser = clang::tooling::CommonOptionsParser::create(argc, argv, toolCategory);
  
  if (!expectedParser) {
    llvm::errs() << expectedParser.takeError();
    return 1;
  }

  clang::tooling::ClangTool tool(
        expectedParser->getCompilations(),
        expectedParser->getSourcePathList());

  return tool.run(clang::tooling::newFrontendActionFactory<
      recursivev::ToyFrontendAction>().get());
}