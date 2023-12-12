CC=gcc
CXX=g++
AR=ar
RANLIB=ranlib


libconio_64.a: conio_64.o
	$(AR) r libconio_64.a conio_64.o
	$(RANLIB) libconio_64.a

conio_64.o: conio.c conio3.h
	$(CC) -Wall -Wextra -g3 -O3 -s -c conio.c -o conio_64.o -m64
