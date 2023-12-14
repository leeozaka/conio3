CC=gcc
CXX=g++
AR=ar
RANLIB=ranlib

libc.a: c.o
	$(AR) r libc.a c.o
	$(RANLIB) libc.a

c.o: c.c conio3.h
	$(CC) -O3 -s -c c.c -o c.o -m64