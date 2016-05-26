CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o .h

.PHONY: all clean

all: assemble emulate

assemble: assemble.o

emulate: emulate.o

emulate.o: pipeline.c emulate.h

pipeline.c: executeInstructions.c pipeline.h

executeInstruction.c: utils.c executeInstructions.h

utils.c: defs.h utils.h



clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
