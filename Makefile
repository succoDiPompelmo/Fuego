CC=clang
CFLAGS=-I.

build: ./src/main.o
	$(CC) -o ./build/Fuego ./src/main.o