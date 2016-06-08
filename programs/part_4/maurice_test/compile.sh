#!/bin/bash
gcc -shared -I/usr/include/python2.7/ -lpython2.7 -o myModule.so myModule.c -fPIC
gcc -shared -I/usr/include/python2.7/ -lpython2.7 -o touchHat.so touchHat.c -fPIC
