#ifndef fuego_compiler_h
#define fuego_compiler_h

#include "vm.h"
#include "object.h"
#include "scanner.h"

typedef enum {
    TYPE_FUNCTION,
    TYPE_INITIALIZER,
    TYPE_METHOD,
    TYPE_SCRIPT,
} FunctionType;

typedef struct {
    Token name;
    bool isCaptured;
    int depth;
} Local;

typedef struct {
    uint8_t index;
    bool isLocal;
} Upvalue;

typedef struct Compiler {
    // What am i doing ?
    struct Compiler* enclosing;
    ObjFunction* function;
    FunctionType type;

    Local locals[UINT8_COUNT];
    int localCount;
    Upvalue upvalues[UINT8_COUNT];
    int scopeDepth;
} Compiler;

ObjFunction* compile(const char* source);
void initCompiler(Compiler* compiler, FunctionType type);
uint8_t makeCostant(Value value);
void markCompilerRoots();

#endif