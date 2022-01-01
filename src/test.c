#include <criterion/criterion.h>

#include "value.h"
#include "chunk.h"

Test(chunk_suite, basics) {
    Chunk chunk;
    initChunk(&chunk);

    cr_assert_eq(chunk.capacity, 0);
    cr_assert_eq(chunk.count, 0);
    cr_assert_eq(chunk.code, NULL);
    cr_assert_eq(chunk.constants.values, NULL);
    cr_assert_eq(chunk.constants.capacity, 0);
    cr_assert_eq(chunk.constants.count, 0);

    freeChunk(&chunk);

    cr_assert_eq(chunk.capacity, 0);
    cr_assert_eq(chunk.count, 0);
    cr_assert_eq(chunk.code, NULL);
    cr_assert_eq(chunk.constants.values, NULL);
    cr_assert_eq(chunk.constants.capacity, 0);
    cr_assert_eq(chunk.constants.count, 0);

    writeChunk(&chunk, OP_RETURN);

    cr_assert_eq(chunk.capacity, 8);
    cr_assert_eq(chunk.count, 1);
    cr_assert_eq(chunk.code[0], OP_RETURN);
    cr_assert_eq(chunk.constants.values, NULL);
    cr_assert_eq(chunk.constants.capacity, 0);
    cr_assert_eq(chunk.constants.count, 0);

    Value value = 2.1;
    addCostant(&chunk, value);

    cr_assert_eq(chunk.capacity, 8);
    cr_assert_eq(chunk.count, 1);
    cr_assert_eq(chunk.code[0], OP_RETURN);
    cr_assert_eq(chunk.constants.values[0], 2.1);
    cr_assert_eq(chunk.constants.capacity, 8);
    cr_assert_eq(chunk.constants.count, 1);

    freeChunk(&chunk);

    cr_assert_eq(chunk.capacity, 0);
    cr_assert_eq(chunk.count, 0);
    cr_assert_eq(chunk.code, NULL);
    cr_assert_eq(chunk.constants.values, NULL);
    cr_assert_eq(chunk.constants.capacity, 0);
    cr_assert_eq(chunk.constants.count, 0);
}

