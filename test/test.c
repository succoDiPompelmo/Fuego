#include "unity.h"
#include "table.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Table(void)
{
  Table table;
  initTable(&table);

  TEST_ASSERT_EQUAL(table.capacity, 0);
  TEST_ASSERT_EQUAL(table.count, 0);
  TEST_ASSERT_EQUAL(table.entries, NULL);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_Table);
    return UNITY_END();
}