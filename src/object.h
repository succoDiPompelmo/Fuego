#ifndef fuego_object_h
#define fuego_object_h

#include "common.h"
#include "value.h"

#define OBJ_TYPE(value)     (AS_OBJ(value)->type)

/*
    We use a function, instead of writing the simple logical clause here, to avoid incurring in multiple evaluation.
    Since the macro parametre value is present more than once in the boolean logic, when the preprocessor evaluate the
    macro the arguments is replaces as is. This can cause problems if it has side effects. Think about the function
    pop() as argument, I would like to pop the element and evaluate the marco with that value once. Without the function
    isObjType we will pop two elements from the stack.
*/
#define IS_STRING(value)    isObjType(value, OBJ_STRING)

#define AS_STRING(value)    ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value)   (((ObjString*)AS_OBJ(value))->chars)

typedef enum {
    OBJ_STRING,
} ObjType;

struct Obj {
    ObjType type;
    struct Obj* next;
};

struct ObjString {
    Obj obj;
    int length;
    char* chars;
};

ObjString* takeString(char* chars, int length);
ObjString* copyString(const char* chars, int length);
void printObject(Value value);

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif