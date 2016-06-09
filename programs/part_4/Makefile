GTK_FLAGS = $(shell pkg-config --cflags --libs gtk+-3.0)
PYTHON_FLAGS = -shared -I/usr/include/python2.7/ -lpython2.7 -fPIC
CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -pedantic -c $(GTK_FLAGS) $(PYTHON_FLAGS)

.SUFFIXES: .c .o .h
.PHONY: all clean

all: touchHat.so

touchHat.so: touchHat.c guiUtils.o symbolTable.o initialiser.o
guiUtils.o: guiUtils.c 
initialiser.o: initialiser.c
symbolTable.o: symbolTable.c

touchHat.c: initialiser.h guiUtils.h
guiUtils.c: guiUtils.h
initialiser.c: initialiser.h
symbolTable.c: symbolTable.h

initialiser.h: soundsTable.h
soundsTable.h: symbolTable.h

clean:
	rm -rf $(wildcard *.o)
	rm -rf $(wildcard *.so)
