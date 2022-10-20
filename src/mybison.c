#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include "mybison.h"
#include "mylex.h"

int main(int argc, char *argv[])
{
    struct stack_int64 *stack_int = create_stack_int64();
    struct stack_operation *stack_op = create_stack_op();
    struct lexer_t* lexer = buildLexer();
    for (size_t lexIndex = 0; lexIndex < lexer->size; lexIndex++) {
        struct token_t lexer_token = lexer->token_array[lexIndex];
        if (lexer_token.type == TKN_EOF) {
            while (stack_op != NULL) {
            float b = stack_int->value;
            stack_int = pop_int64(stack_int);
            float a = stack_int->value;
            stack_int = pop_int64(stack_int);
            char operation = stack_op->operation;
            if (operation == '+') {
                stack_int = push_int64(stack_int, a + b);
            } else if (operation == '-') {
                stack_int = push_int64(stack_int, a - b);
            } else if (operation == '*') {
                stack_int = push_int64(stack_int, a * b);
            } else if (operation == '/') {
                stack_int = push_int64(stack_int, a / b);
            }
            stack_op = pop_operation(stack_op);
            }
        } else if (lexer_token.type == TKN_NUM) {
            stack_int = push_int64(stack_int, atoi(lexer_token.value));
        } else if (lexer_token.type == TKN_LPAREN) {
            stack_op = push_operation(stack_op, lexer_token.type);
        } else if (lexer_token.type == TKN_RPAREN) {
            while (stack_op != NULL && stack_op->operation != '(') {
            float b = stack_int->value;
            stack_int = pop_int64(stack_int);
            float a = stack_int->value;
            stack_int = pop_int64(stack_int);
            char operation = stack_op->operation;
            if (operation == '+') {
                stack_int = push_int64(stack_int, a + b);
            } else if (operation == '-') {
                stack_int = push_int64(stack_int, a - b);
            } else if (operation == '*') {
                stack_int = push_int64(stack_int, a * b);
            } else if (operation == '/') {
                stack_int = push_int64(stack_int, a / b);
            }
            stack_op = pop_operation(stack_op);
            }
            stack_op = pop_operation(stack_op);
        } else {
            int priority = atoi(lexer_token.value);
            if (priority > stack_op->priority) {
                stack_op = push_operation(stack_op, lexer_token.type);
            } else {
                while (stack_op->priority >= priority) {
                    float b = stack_int->value;
                    stack_int = pop_int64(stack_int);
                    float a = stack_int->value;
                    stack_int = pop_int64(stack_int);
                    char operation = stack_op->operation;
                    stack_op = pop_operation(stack_op);
                    if (operation == '+') {
                stack_int = push_int64(stack_int, a + b);
            } else if (operation == '-') {
                stack_int = push_int64(stack_int, a - b);
            } else if (operation == '*') {
                stack_int = push_int64(stack_int, a * b);
            } else if (operation == '/') {
                stack_int = push_int64(stack_int, a / b);
            }
                    if (stack_op == NULL) {
                        break;
                    }
                }
                stack_op = push_operation(stack_op, lexer_token.type);
            }
        }
    }
    printf("%f\n", stack_int->value);
}