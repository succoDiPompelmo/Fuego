#ifndef fuego_vm_h
#define fuego_vm_h

#include "chunk.h"
#include "value.h"
#include "compiler.h"
#include "table.h"
#include "object.h"

#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)

typedef struct {
    ObjClosure* closure;
    uint8_t* ip;
    Value* slots;
} CallFrame;

/*
    Module representing the Virtual Machine (VM) that will run bytecode on the targeted host machine.
    Some characteristics of the VM to keep track of:
    - Stack Based: When is required to solve an expression we make use of a stack. The stack is implemented from zero using C arrays as backup.
    - Singleton: To simplify the first deployment a global variable store the VM, mimicking a Singleton pattern.
*/

typedef struct {
    CallFrame frames[FRAMES_MAX];
    int frameCount;
    Value stack[STACK_MAX]; // Array backing the stack implementation
    Value* stackTop; // Pointer to stack last element.
    Table globals; // global variables
    Table strings; // String interning
    ObjUpValue* openUpvalues;

    size_t bytesAllocated;
    size_t nextGC;
    Obj* objects;
    int grayCount;
    int grayCapacity;
    Obj** grayStack;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();
InterpretResult interpret(const char* source); 

void push(Value value);
Value pop();

#endif