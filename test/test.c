#include "unity.h"
#include "table.h"
#include "value.h"
#include "object.h"
#include "vm.h"

void setUp(void) {
  initVM();
}
void tearDown(void) {}

void test_Table(void)
{
  Table table;
  initTable(&table);

  TEST_ASSERT_EQUAL(table.capacity, 0);
  TEST_ASSERT_EQUAL(table.count, 0);
  TEST_ASSERT_EQUAL(table.entries, NULL);

  Value boolVal = BOOL_VAL(true);
  Value numberVal = NUMBER_VAL(1);
  Value result;

  ObjString* key = takeString("key", 3);

  tableSet(&table, key, boolVal);

  TEST_ASSERT_TRUE(tableGet(&table, key, &result));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_Table);
    return UNITY_END();
}