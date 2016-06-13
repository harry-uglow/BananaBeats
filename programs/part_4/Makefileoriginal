CC      = gcc
CFLAGS  = -Wall -std=c99 -pedantic
THREAD_FLAGS = -lpthread
GTK_FLAGS = $$(pkg-config --cflags --libs gtk+-3.0)
PYTHON_FLAGS = -shared -I/usr/include/python2.7/ -lpython2.7 -fPIC -rdynamic

.SUFFIXES: .c .o .h
.PHONY: all clean

all: main.o touchHat.so
	$(CC) -o main main.o guiUtils.o $(GTK_FLAGS) $(THREAD_FLAGS) -lpython2.7

main.o: guiUtils.o
	$(CC) $(CFLAGS) $(PYTHON_FLAGS) $(GTK_FLAGS) -c main.c -o main.o

touchHat.so: touchHat.o initialiser.o symbolTable.o
	$(CC) $(CFLAGS) $(PYTHON_FLAGS) $(GTK_FLAGS) touchHat.o initialiser.o symbolTable.o -o touchHat.so

touchHat.o:
	$(CC) $(CFLAGS) $(PYTHON_FLAGS) $(GTK_FLAGS) -c touchHat.c -o touchHat.o

guiUtils.o:
	$(CC) $(CFLAGS) $(PYTHON_FLAGS) $(GTK_FLAGS) -c guiUtils.c -o guiUtils.o

initialiser.o:
	$(CC) $(CFLAGS) -fPIC -c initialiser.c -o initialiser.o

symbolTable.o:
	$(CC) $(CFLAGS) -fPIC -c symbolTable.c -o symbolTable.o

clean:
	rm main
	rm -rf $(wildcard *.o)
	rm -rf $(wildcard *.so)
