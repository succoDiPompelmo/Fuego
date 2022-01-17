#include "unity.h"
#include "chunk.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_FindFunction_WhichIsBroken_ShouldReturnZeroIfItemIsNotInList_WhichWorksEvenInOurBrokenCode(void)
{
  /* All of these should pass */
  TEST_ASSERT_EQUAL(0, 0);

  Chunk chunk;
  initChunk(&chunk);

}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_FindFunction_WhichIsBroken_ShouldReturnZeroIfItemIsNotInList_WhichWorksEvenInOurBrokenCode);
    return UNITY_END();
}