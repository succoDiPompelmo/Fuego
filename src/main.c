#include "common.h"
#include "chunk.h"
#include "debug.h"

/**
 *  A test class. A more elaborate class description.
 */
int main(int argc, const char* argv[]) {

    Chunk chunk;
    initChunk(&chunk);

    int constant = addCostant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT);
    writeChunk(&chunk, constant);

    writeChunk(&chunk, OP_RETURN);

    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);

    return 0;
}