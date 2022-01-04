#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

/**
 *  A test class. A more elaborate class description.
 */
int main(int argc, const char* argv[]) {

    initVM();

    Chunk chunk;
    initChunk(&chunk);

    int constant = addCostant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);
    writeChunk(&chunk, OP_NEGATE, 123);
    writeChunk(&chunk, OP_RETURN, 123);

    // disassembleChunk(&chunk, "test chunk");
    interpret(&chunk);

    freeVM();

    freeChunk(&chunk);

    return 0;
}