cmake_minimum_required(VERSION 3.0)
project(quantization)

set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra")

set(SOURCE_FILES
        src/commands.h
        src/commands.c
        src/find_and_union.h
        src/find_and_union.c
        src/main.c
        src/parser.h
        src/parser.c
        src/trie.h
        src/trie.c
        src/vector.h
        src/vector.c)

add_executable(map ${SOURCE_FILES})