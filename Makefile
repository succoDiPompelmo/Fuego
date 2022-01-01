CC=clang
CFLAGS=-I.

build: ./src/main.o ./src/chunk.o ./src/memory.o ./src/debug.o
	$(CC) -o ./build/Fuego ./src/main.o ./src/chunk.o ./src/memory.o ./src/debug.o

run:
	./build/Fuego

test: ./src/test.c
	$(CC) -o test ./src/test.c -lcriterion

doc:
	doxygen

clean:
	find ./src -name "*.o" -type f -delete