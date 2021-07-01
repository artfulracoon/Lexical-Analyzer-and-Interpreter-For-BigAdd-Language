cmake_minimum_required(VERSION 3.19)
project(LxForBigAdd C)

set(CMAKE_C_STANDARD 99)

add_executable(LxForBigAdd main.c detectWord.c detectWord.h checkKeyword.c checkKeyword.h interpreter.c interpreter.h)