CC=clang
CFLAGS=-I.

build: ./src/main.o
	$(CC) -o ./build/Fuego ./src/main.o

test: ./src/test.c
	$(CC) -o test ./src/test.c -lcriterion