# LLVM学习记录

LLVM是一个极为复杂、但是无论在科研还是在业界都有重要的编译器基础设施。

一般的LLVM教程都会从一个前端（词法、语法）入手，然后逐步扩展到代码生成（CodeGen）。
套用软件工程的术语来说，这种学习方式是“瀑布式的”。
这种学习方式适合一个本科学生利用自己的课余时间去学习。
然而，对于高年级学生和研究生而言，这种学习方法存在两个潜在问题：

1. 这些学生通常拥有一定基础知识（编译原理），继续从前端学习、逐步实现一个比较完整的前端是很消磨学习热情的事情
2. 这些学生学习LLVM是出于主动还是被动，但是多半会将自己学习的技能落地到一个项目中（本科毕设、复现论文、开展自己的实验等），而这些技能都零散地分布在整个教程中，所以不太敢跳过某些章节
3. 教程大多将整个组件集成在一个程序中，而真正的编译过程是一个由驱动程序点火的工具链，包含对多个可执行的二进制文件的调用、临时文件的生成等；想在特定的部分工作必须了解不同的工具的具体作用，以方便插入自己编写的工具

这篇教程将聚焦于高年级学生以及研究生基于LLVM进行实践时所需的技能，帮助同学们快速进入科研生活，产出高质量的论文。

目前本项目仍然处于开发阶段，即使笔者在大纲中罗列了很多主题，但是笔者也并非高级的开发者，对很多主题的探索可能只会停留在“能用就行”、甚至写下这篇前言时只是感兴趣但是尚未调研的水平，对这些组件的设计理念、设计模式不会进行深入的探讨。
这篇教程只是学习的起点，而不是终点。

本教程计划包含的主题有：

* [] **Chapter 0**：提供LLVM的预览
* [] **Chapter 1**：基于LibTooling编写工具，并利用FrontendAction改变clang前端的行为
* [] **Chapter 2**：基于clang plugin编写的前端工具，初步集成 `llvm-lit` 测试
* [] **Chapter ?**：pass的编写、不同的调用方式、基于pass plugin的扩展
* [] **Chapter ?**：调试这些项目
* [] **Chapter ?**：MLIR的使用概览
* [] **Chatper ?**：后端相关

## Prerequisite

* 对CMake有基本了解：本教程涉及的代码会尽力以out-of-tree的形式编写，因此CMake文件相对轻量级
* 了解并掌握递归下降程序的编写：本教程不涉及前端，因此不会在这个方面浪费笔墨

## LLVM编译命令

```sh
mkdir build && cd build

cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DLLVM_BUILD_LLVM_DYLIB=ON \
-DLLVM_ENABLE_ASSERTIONS=OFF -DLLVM_OPTIMIZED_TABLEGEN=ON -DLLVM_TARGETS_TO_BUILD="ARM;AArch64" \
-DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra;mlir;openmp;polly" -DLLVM_BUILD_TOOLS=ON \
-DLLVM_ENABLE_EH=ON -DLLVM_ENABLE_RTTI=ON \
-DLLVM_PARALLEL_LINK_JOBS=16 -DCMAKE_INSTALL_PREFIX=/opt/llvm17 -DLLVM_ENABLE_DOXYGEN=OFF \
-DLLVM_ENABLE_SPHINX=OFF -DLLVM_ENABLE_LLD=OFF -DLLVM_ENABLE_BINDINGS=OFF -DLLVM_ENABLE_LIBXML2=OFF \
-DOPENMP_ENABLE_LIBOMPTARGET=OFF -DLLVM_STATIC_LINK_CXX_STDLIB=ON ../llvm
```

所有示例代码在17.0.6和20.0.0上均编译通过，未来可能额外验证支持一个CIR正式发布的LLVM版本。