CC      = gcc
CFLAGS  = -Wall -std=c99 -pedantic
THREAD_FLAGS = -lpthread
GTK_FLAGS = $$(pkg-config --cflags --libs gtk+-3.0)
PYTHON_FLAGS = -shared -I/usr/include/python2.7/ -lpython2.7 -fPIC -rdynamic

.SUFFIXES: .c .o .h
.PHONY: all clean

all: main

main: guiUtils.o touchHat.so
	$(CC) $(CFLAGS) $(PYTHON_FLAGS) $(GTK_FLAGS) $(THREAD_FLAGS) guiUtils.o main.c -o main

touchHat.so: initialiser.o symbolTable.o guiUtils.o
	$(CC) $(CFLAGS) $(PYTHON_FLAGS) $(GTK_FLAGS) touchHat.c symbolTable.o initialiser.o guiUtils.o -o touchHat.so

guiUtils.o:
	$(CC) $(CFLAGS) $(PYTHON_FLAGS) $(GTK_FLAGS) -c guiUtils.c -o guiUtils.o

initialiser.o:
	$(CC) $(CFLAGS) -c initialiser.c -o initialiser.o

symbolTable.o:
	$(CC) $(CFLAGS) -c symbolTable.c -o symbolTable.o

clean:
	rm main
	rm -rf $(wildcard *.o)
	rm -rf $(wildcard *.so)
