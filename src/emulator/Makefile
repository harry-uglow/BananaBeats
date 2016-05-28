CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o .h

.PHONY: all clean

all: emulate

#assemble: assemble.o

emulate: emulate.o

emulate.o: cd emulator; make

emulate.o: emulate/pipeline.c emulate/emulate.h

emulate/pipeline.c: emulate/executeInstructions.c emulate/pipeline.h

emulate/executeInstructions.c: emulate/utils.c emulate/executeInstructions.h

emulate/utils.c: emulate/defs.h emulate/utils.h



clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
