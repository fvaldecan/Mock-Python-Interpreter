cmake_minimum_required(VERSION 3.14)
project(CS460_Project3)

set(CMAKE_CXX_STANDARD 17)

add_executable(CS460_Project3 main.cpp ArithExpr.cpp ArithExpr.hpp Parser.cpp Parser.hpp Statements.cpp Statements.hpp SymTab.cpp SymTab.hpp Token.cpp Token.hpp Tokenizer.cpp Tokenizer.hpp Descriptor.cpp Descriptor.hpp Testlist.cpp Testlist.hpp Range.cpp Range.hpp Functions.cpp Functions.hpp)