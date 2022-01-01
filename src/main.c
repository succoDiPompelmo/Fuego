#include "common.h"
#include "chunk.h"

/**
 *  A test class. A more elaborate class description.
 */
int main(int argc, const char* argv[]) {

    Chunk chunk;
    initChunk(&chunk);
    writeChunk(&chunk, OP_RETURN);
    freeChunk(&chunk);

    return 0;
}