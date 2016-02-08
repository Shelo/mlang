cmake_minimum_required(VERSION 3.3)
project(mlang)

include_directories(sources)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp sources/Lexer.cpp sources/Lexer.hpp sources/TokenBuffer.cpp sources/TokenBuffer.hpp sources/Types.hpp sources/TokenParsers.cpp sources/TokenParsers.hpp sources/Parser.cpp sources/Parser.h)
add_executable(mlang ${SOURCE_FILES})
