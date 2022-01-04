CC=clang
CFLAGS=-I.

build: ./src/main.o ./src/chunk.o ./src/memory.o ./src/debug.o ./src/value.o ./src/vm.o
	$(CC) -o ./build/Fuego ./src/main.o ./src/chunk.o ./src/memory.o ./src/debug.o ./src/value.o ./src/vm.o

run:
	./build/Fuego

test: ./src/test.o ./src/chunk.o ./src/memory.o ./src/debug.o ./src/value.o ./src/vm.o
	$(CC) -o ./build/Test ./src/test.o ./src/chunk.o ./src/memory.o ./src/debug.o ./src/value.o ./src/vm.o -lcriterion

doc:
	doxygen

clean:
	find ./src -name "*.o" -type f -delete