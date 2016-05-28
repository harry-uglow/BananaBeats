CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o .h

.PHONY: all clean

all: emulate
# Add assemble when complete

#assemble: assemble.o

emulate: emulate.o

emulate.o: emulator/pipeline.c

emulator/pipeline.c: emulator/executeInstructions.c emulator/pipeline.h

emulator/executeInstructions.c: emulator/utils.c emulator/executeInstructions.h

emulator/utils.c: emulator/defs.h

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
