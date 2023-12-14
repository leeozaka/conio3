CC=gcc
CXX=g++
AR=ar
RANLIB=ranlib


libc_64.a: c.o
	$(AR) r libc.a c.o
	$(RANLIB) libc.a

c.o: c.c conio3.h
	$(CC) -Wall -Wextra -g3 -O3 -s -c c.c -o c.o -m64
