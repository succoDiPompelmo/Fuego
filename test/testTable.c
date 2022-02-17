#include "unity.h"
#include "table.h"
#include "value.h"
#include "object.h"
#include "vm.h"

Table testTable;

void setUp(void) {
  initVM();
  initTable(&testTable);
}
void tearDown(void) {
  freeTable(&testTable);
}

void test_TableInit(void)
{
  TEST_ASSERT_EQUAL(testTable.capacity, 0);
  TEST_ASSERT_EQUAL(testTable.count, 0);
  TEST_ASSERT_EQUAL(testTable.entries, NULL);
}

void test_TableSetBool(void) {
  ObjString* key = takeString("key", 3);
  Value value = BOOL_VAL(true);
  Value result;

  tableSet(&testTable, key, value);
  TEST_ASSERT_TRUE(tableGet(&testTable, key, &result));
  TEST_ASSERT_TRUE(AS_BOOL(result));
}

void test_TableSetNumber(void) {
  double num = 10;
  ObjString* key = takeString("key", 3);
  Value value = NUMBER_VAL(num);
  Value result;

  tableSet(&testTable, key, value);
  TEST_ASSERT_TRUE(tableGet(&testTable, key, &result));
  TEST_ASSERT_EQUAL(num, AS_NUMBER(result));
}

void test_TableSetNil(void) {
  ObjString* key = takeString("key", 3);
  Value value = NIL_VAL;
  Value result;

  tableSet(&testTable, key, value);
  TEST_ASSERT_TRUE(tableGet(&testTable, key, &result));
  TEST_ASSERT_TRUE(IS_NIL(result));
}

void test_TableSetSameKey() {
  ObjString* key = takeString("key", 3);
  Value beforeValue = NUMBER_VAL(20);
  Value afterValue = NUMBER_VAL(2000);
  Value result;

  tableSet(&testTable, key, beforeValue);
  TEST_ASSERT_TRUE(tableGet(&testTable, key, &result));
  TEST_ASSERT_EQUAL(20, AS_NUMBER(result));

  tableSet(&testTable, key, afterValue);
  TEST_ASSERT_TRUE(tableGet(&testTable, key, &result));
  TEST_ASSERT_EQUAL(2000, AS_NUMBER(result));

  TEST_ASSERT_EQUAL(1, testTable.count);
  TEST_ASSERT_EQUAL(8, testTable.capacity);
}

void test_TableGrowthRate() {
  int start = 8;
  char str[100];
  Value value = BOOL_VAL(true);
  for (int i = 0; i < 300; i++) {
    sprintf(str, "%d", i);
    ObjString* key = takeString(str, 4);
    tableSet(&testTable, key, value);

    // Check that the Table capacity grow as a power of 2.
    if ((((i & (i - 1)) == 0)) && (i >= 7)) {
      start = start * 2;
      TEST_ASSERT_EQUAL(start, testTable.capacity);
    }
  }  
}