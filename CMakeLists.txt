cmake_minimum_required(VERSION 3.5)
project(BananaBeats)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -std=c99")

set(SOURCE_FILES src/main.c)
add_executable(BananaBeats ${SOURCE_FILES})
#            src/emulate.c
#            src/emulator/executeInstructions.c
#            src/emulator/pipeline.c
#            src/emulator/utils.c)
#    add_executable(assemble ${SOURCE_FILES}
#            src/assemble.c
#            src/assembler/encodeInstructions.c
#            src/assembler/getFormat.c
#            src/assembler/symbolTable.c
#            src/assembler/utils.c)


