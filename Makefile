CC=clang
CFLAGS=-I.

build: ./src/main.o ./src/chunk.o ./src/memory.o
	$(CC) -o ./build/Fuego ./src/main.o ./src/chunk.o ./src/memory.o

run:
	./build/Fuego

test: ./src/test.c
	$(CC) -o test ./src/test.c -lcriterion

doc:
	doxygen