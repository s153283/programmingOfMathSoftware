# Makefile for Assignment 2, DTU 02635, Fall 2017
CC=gcc
CFLAGS=-Wall -std=c99 -g
EXECUTABLE=lssolve test

# Detect OS and set linker flags accordingly
ifdef SystemRoot
 # Windows
LDFLAGS=-L.
LDLIBS=-lopenblas -lgfortran -lm
else
ifeq ($(shell uname), Darwin)
		# macOS
LDLIBS=-llapack -lblas -lm
else
# Code to compile on Simon's Unix systme
#LDLIBS=-llapack -lblas -lgfortran -lm

# Gbar
LDFLAGS=-L/usr/lib64/atlas
LDLIBS=-llapack -lf77blas -latlas -lgfortran -lm
endif
endif

.PHONY: all clean run

all: $(EXECUTABLE)

lssolve: matrix_io.o lssolve.o


lssolve.o: lssolve.h matrix_io.h
matrix_io.o: matrix_io.h

test: matrix_io.o test.o
test.o: lssolve.h matrix_io.h




clean:
	-$(RM) *.o $(EXECUTABLE)

run: lssolve
	./$< $(ARGS) A.txt b.txt solution.txt
