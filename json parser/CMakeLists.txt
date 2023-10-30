cmake_minimum_required(VERSION 3.24)
project(command_line)

set(CMAKE_CXX_STANDARD 17)

add_executable(command_line main.cpp  cmake-build-debug/scanner.h cmake-build-debug/parser.h cmake-build-debug/Json_element.h Scanner.cpp parser.cpp)
