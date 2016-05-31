cmake_minimum_required(VERSION 3.5)
project(arm11_19)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -std=c99")

set(SOURCE_FILES src)
    add_executable(emulate ${SOURCE_FILES} src/emulate.c)
    add_executable(assemble ${SOURCE_FILES}
            src/assemble.c
            src/assembler/encodeInstructions.c
            src/assembler/getFormat.c
            src/assembler/symbolTable.c
            src/assembler/utils.c)
