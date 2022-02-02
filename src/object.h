#ifndef fuego_object_h
#define fuego_object_h

#include "common.h"
#include "value.h"
#include "chunk.h"
#include "table.h"

#define OBJ_TYPE(value)     (AS_OBJ(value)->type)

/*
    We use a function, instead of writing the simple logical clause here, to avoid incurring in multiple evaluation.
    Since the macro parametre value is present more than once in the boolean logic, when the preprocessor evaluate the
    macro the arguments is replaces as is. This can cause problems if it has side effects. Think about the function
    pop() as argument, I would like to pop the element and evaluate the marco with that value once. Without the function
    isObjType we will pop two elements from the stack.
*/
#define IS_CLASS(value)     isObject(value, OBJ_CLASS)
#define IS_CLOSURE(value)   isObject(value, OBJ_CLOSURE)
#define IS_FUNCTION(value)  isObjType(value, OBJ_FUNCTION)
#define IS_INSTANCE(value)  isObjType(value, OBJ_INSTANCE)
#define IS_NATIVE(value)    isObject(value, OBJ_NATIVE)
#define IS_STRING(value)    isObjType(value, OBJ_STRING)

#define AS_CLASS(value)     ((ObjClass*)AS_OBJ(value))
#define AS_CLOSURE(value)   ((ObjClosure*)AS_OBJ(value))
#define AS_FUNCTION(value)  ((ObjFunction*)AS_OBJ(value))
#define AS_INSTANCE(value)  ((ObjInstance*)AS_OBJ(value))
#define AS_NATIVE(value)    (((ObjNative*)AS_OBJ(value))->function)
#define AS_STRING(value)    ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value)   (((ObjString*)AS_OBJ(value))->chars)

typedef enum {
    OBJ_CLASS,
    OBJ_CLOSURE,
    OBJ_FUNCTION,
    OBJ_INSTANCE,
    OBJ_NATIVE,
    OBJ_STRING,
    OBJ_UPVALUE,
} ObjType;

struct Obj {
    ObjType type;
    bool isMarked;
    struct Obj* next;
};

typedef struct {
    Obj obj;
    int arity;
    int upvalueCount;
    Chunk chunk;
    ObjString* name;
} ObjFunction;

typedef Value (*NativeFn)(int argCount, Value* args);

typedef struct {
    Obj obj;
    NativeFn function;
} ObjNative;

struct ObjString {
    Obj obj;
    int length;
    char* chars;
    uint32_t hash;
};

typedef struct ObjUpValue {
    Obj obj;
    Value* location;
    Value closed;
    struct ObjUpValue* next;
} ObjUpValue;

typedef struct {
    Obj obj;
    ObjFunction* function;
    ObjUpValue** upvalues;
    int upvalueCount;
} ObjClosure;

typedef struct {
    Obj obj;
    ObjString* name;
} ObjClass;

typedef struct {
    Obj obj;
    ObjClass* klass;
    Table fields;
} ObjInstance;

ObjClass* newClass(ObjString* name);
ObjClosure* newClosure(ObjFunction* function);
ObjFunction* newFunction();
ObjInstance* newInstance(ObjClass* klass);
ObjString* takeString(char* chars, int length);
ObjNative* newNative(NativeFn function);
ObjString* copyString(const char* chars, int length);
ObjUpValue* newUpValue(Value* slot);
void printObject(Value value);

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif