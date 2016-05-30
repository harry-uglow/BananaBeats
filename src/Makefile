CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o .h

.PHONY: all clean

all: emulate assembler

###--- Emulator dependencies ---###
emulate: emulate.o
emulate.o: emulator/pipeline.c
emulator/pipeline.c: emulator/executeInstructions.c emulator/pipeline.h
emulator/executeInstructions.c: emulator/utils.c emulator/executeInstructions.h
emulator/utils.c: emulator/defs.h

###--- Assembler dependencies ---###
assembler: assembler/assembler.o
assembler/assembler.o: assembler/assembler.c
assembler/utils.h: assembler/encodeInstructions.h
assembler/encodeInstructions.h: assembler/getFormat.h
assembler/getFormat.h: assembler/defs.h assembler/SymbolTable.h

assembler/utils.o: assembler/utils.c assembler/utils.h
assembler/symbolTable.o: assembler/.c assembler/.h
assembler/getFormat.o: assembler/getFormat.c assembler/getFormat.h
assembler/encodeInstructions.o: assembler/encodeInstructions.c assembler/encodeInstructions.h

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
