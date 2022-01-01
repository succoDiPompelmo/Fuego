#include <criterion/criterion.h>
#include "chunk.h"

Test(chunk_suite, basics) {
    Chunk chunk;
    initChunk(&chunk);

    cr_assert_eq(chunk.capacity, 0);
    cr_assert_eq(chunk.count, 0);
    cr_assert_eq(chunk.code, NULL);

    freeChunk(&chunk);

    cr_assert_eq(chunk.capacity, 0);
    cr_assert_eq(chunk.count, 0);
    cr_assert_eq(chunk.code, NULL);

    writeChunk(&chunk, OP_RETURN);

    cr_assert_eq(chunk.capacity, 8);
    cr_assert_eq(chunk.count, 1);
    cr_assert_eq(chunk.code[0], OP_RETURN);

    freeChunk(&chunk);

    cr_assert_eq(chunk.capacity, 0);
    cr_assert_eq(chunk.count, 0);
    cr_assert_eq(chunk.code, NULL);
}