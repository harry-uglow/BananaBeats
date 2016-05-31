CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o .h

.PHONY: all clean

all: assemble emulate

###--- Emulator dependencies ---###
emulate: emulate.o
emulate.o: emulator/pipeline.c
emulator/pipeline.c: emulator/executeInstructions.c emulator/pipeline.h
emulator/executeInstructions.c: emulator/utils.c emulator/executeInstructions.h
emulator/utils.c: emulator/defs.h

###--- Assembler dependencies ---###
assemble: assemble.o assembler/utils.o assembler/encodeInstructions.o assembler/getFormat.o assembler/symbolTable.o
assemble.o: assemble.c
utils.o: assembler/utils.c
encodeInstructions.o: assembler/encodeInstructions.c
getFormat.o: assembler/getFormat.c
symbolTable.o: assembler/symbolTable.c

assemble.c: assembler/utils.h assembler/utils.c
assembler/utils.c: assembler/utils.h
assembler/encodeInstructions.c: assembler/encodeInstructions.h
assembler/getFormat.c: assembler/getFormat.h
assembler/symbolTable.c: assembler/symbolTable.h
assembler/utils.h: assembler/encodeInstructions.h
assembler/encodeInstructions.h: assembler/getFormat.h
assembler/getFormat.h: assembler/defs.h assembler/symbolTable.h

clean:
	rm -rf $(wildcard *.o)
	rm -rf assembler/*.o
	rm -f assemble
	rm -f emulate
