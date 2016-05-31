CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic

.SUFFIXES: .c .o .h

.PHONY: all clean

all: assemble emulate

###***--- Emulator dependencies ---***###

emulate: emulate.o emulator/pipeline.o emulator/executeInstructions.o \
	emulator/utils.o
emulate.o: emulate.c
pipeline.o: pipeline.c
executeInstructions.o: executeInstructions.c
utils.o: utils.c

emulate.c: pipeline.h
pipeline.c: pipeline.h
executeInstructions.c: executeInstructions.h
utils.c: utils.h
pipeline.h: executeInstructions.h
executeInstructions.h: utils.h
utils.h: emulator/defs.h


###***--- Assembler dependencies ---***###

assemble: assemble.o assembler/utils.o assembler/encodeInstructions.o \
	assembler/getFormat.o assembler/symbolTable.o
assemble.o: assemble.c
utils.o: utils.c
encodeInstructions.o: encodeInstructions.c
getFormat.o: getFormat.c
symbolTable.o: symbolTable.c

assemble.c: utils.h utils.c
utils.c: utils.h
encodeInstructions.c: encodeInstructions.h
getFormat.c: getFormat.h
symbolTable.c: symbolTable.h
utils.h: encodeInstructions.h
encodeInstructions.h: getFormat.h
getFormat.h: assembler/defs.h assembler/symbolTable.h


clean:
	rm -rf $(wildcard *.o)
	rm -rf $(wildcard emulator/*.o)
	rm -rf $(wildcard assembler/*.o)
	rm -f assemble
	rm -f emulate
