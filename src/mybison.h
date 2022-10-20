#include <inttypes.h>

struct stack_int64 {
    float value;
    struct stack_int64* next;
};

struct stack_operation {
    char operation;
    int priority;
    struct stack_operation* next;
};

struct stack_int64* push_int64(struct stack_int64* stack, float value) {
    struct stack_int64* new_stack = malloc(sizeof(struct stack_int64));
    new_stack->value = value;
    new_stack->next = stack;
    return new_stack;
}

struct stack_operation* push_operation(struct stack_operation* stack, int type) {
    struct stack_operation* new_stack = malloc(sizeof(struct stack_operation));
    switch(type) {
        case 2:
            new_stack->operation = '+';
            new_stack->priority = 1;
            break;
        case 3:
            new_stack->operation = '-';
            new_stack->priority = 1;
            break;
        case 4:
            new_stack->operation = '*';
            new_stack->priority = 2;
            break;
        case 5:
            new_stack->operation = '/';
            new_stack->priority = 2;
            break;
        case 6:
            new_stack->operation = '(';
            new_stack->priority = 0;
            break;
        case 7:
            new_stack->operation = ')';
            new_stack->priority = 0;
            break;
    }
    new_stack->next = stack;
    return new_stack;
}

struct stack_int64* pop_int64(struct stack_int64* stack) {
    struct stack_int64* new_stack = stack->next;
    free(stack);
    return new_stack;
}

struct stack_operation* pop_operation(struct stack_operation* stack) {
    struct stack_operation* new_stack = stack->next;
    free(stack);
    return new_stack;
}

struct stack_operation* create_stack_op() {
    struct stack_operation* stack = malloc(sizeof(struct stack_operation));
    stack->operation = '+';
    stack->priority = 0;
    stack->next = NULL;
    return stack;
}

struct stack_int64* create_stack_int64() {
    struct stack_int64* stack = malloc(sizeof(struct stack_int64));
    stack->value = 0;
    stack->next = NULL;
    return stack;
}