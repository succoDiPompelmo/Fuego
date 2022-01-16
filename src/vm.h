#ifndef fuego_vm_h
#define fuego_vm_h

#include "chunk.h"
#include "value.h"
#include "compiler.h"

#define STACK_MAX 256

/*
    Module representing the Virtual Machine (VM) that will run bytecode on the targeted host machine.
    Some characteristics of the VM to keep track of:
    - Stack Based: When is required to solve an expression we make use of a stack. The stack is implemented from zero using C arrays as backup.
    - Singleton: To simplify the first deployment a global variable store the VM, mimicking a Singleton pattern.
*/

typedef struct {
    Chunk* chunk;
    uint8_t* ip; // Instruction Pointer.
    Value stack[STACK_MAX]; // Array backing the stack implementation
    Value* stackTop; // Pointer to stack last element.
    Obj* objects;
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