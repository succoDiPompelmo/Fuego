#include <stdio.h>

#include "common.h"
#include "vm.h"
#include "debug.h"

VM vm;

static void resetStack() {
    vm.stackTop = vm.stack;
}

void initVM() {
    resetStack();
}

void freeVM() {

}

void push(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}

static InterpretResult run() {
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    /*
        I know... this is not magic but the C preprocessor to full throttle. I will share with you the trick (that are two, fell
        yourself lucky):
        - Yes, you can pass operator to C macro, baam. C doesn't care that operators are not first-class citizens in C.
          They are tokens and that's enough for him (her/its ?).
        - The do/while block is necessary to avoid strange behaviour that injecting multiple lines of code could cause.
          For example, try to run:
            if (binary) BINARY_OP();
          Have you tried? Well, a do-while block is the only construct that allows stacking together multiple statements
          closing with a semicolon without causing any disaster.
    */
    #define BINARY_OP(op) \
        do { \
            double b = pop(); \
            double a = pop(); \
            push(a op b); \
        } while (false)

    for (;;) {
        #ifdef DEBUG_TRACE_EXECUTION
            printf("        ");
            for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
                printf("[ ");
                printValue(*slot);
                printf(" ]");
            }
            printf("\n");
            disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
        #endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
        case OP_CONSTANT: {
            Value constant = READ_CONSTANT();
            push(constant);
            printValue(constant);
            printf("\n");
            break;
        }
        case OP_ADD: BINARY_OP(+); break;
        case OP_SUBTRACT: BINARY_OP(-); break;
        case OP_MULTIPLY: BINARY_OP(*); break;
        case OP_DIVIDE: BINARY_OP(/); break;
        case OP_NEGATE: {
            push(-pop()); 
            break;   
        }
        case OP_RETURN: {
            printValue(pop());
            printf("\n");
            return INTERPRET_OK;
            }
        }
    }

    #undef READ_BYTE
    #undef READ_CONSTANT
    #undef BINARY_OP
}

InterpretResult interpret(const char* source) {
    compile(source);
    return INTERPRET_OK;
}