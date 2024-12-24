cmake_minimum_required(VERSION 3.16.0)

project("toy clang tool")

set(CXX_STANDARD 17)
set(C_STANDARD 99)

# General options
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17")

find_package(LLVM REQUIRED CONFIG)
message(STATUS "FOUND LLVMConfig.cmake in ${LLVM_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

find_package(Clang REQUIRED CONFIG)
message(STATUS "FOUND ClangConfig.cmake in ${Clang_DIR}")
list(APPEND CMAKE_MODULE_PATH "${CLANG_CMAKE_DIR}")
include(AddClang)

# Handle LLVM built without ENABLE_RTTI=ON
if (NOT ${LLVM_ENABLE_RTTI})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

# Include path
include_directories(${LLVM_INCLUDE_DIR})
include_directories(${CLANG_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)

# Libraries
link_directories(${LLVM_LIBRARY_DIRS})
set(LLVM_LINK_COMPONENTS Support FrontendOpenMP)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_llvm_executable(clang-toy
  main.cc
)

target_link_libraries(clang-toy
  PRIVATE
  clangAST
  clangASTMatchers
  clangBasic
  clangFrontend
  clangSerialization
  clangTooling
)