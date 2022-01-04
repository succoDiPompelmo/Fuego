/*
    Here goes the definitions of our code representation. "chunk" is used to refer to sequences of bytecode.
*/
#ifndef fuego_chunk_h
#define fuego_chunk_h

#include "common.h"
#include "value.h"

// Enum representing the one byte operation code (aka OpCode) 
// that controls what kind of instructions we are dealing with.
typedef enum {
    OP_CONSTANT,
    OP_NEGATE,
    OP_RETURN,
} OpCode;

// Struct to store data related to bytecode instructions. It represents a Dynamic Array of bytes.
typedef struct {
    int count;
    int capacity;
    uint8_t* code;
    int* lines;
    ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addCostant(Chunk* chunk, Value value);

#endif