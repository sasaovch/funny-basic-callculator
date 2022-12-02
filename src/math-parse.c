#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "math-parse.h"
#include "parse-inner.h"

struct parser_stack *push_parser_stack_value(struct parser_stack *stack,
                                             struct parser_stack_value value) {
    struct parser_stack *new_head = malloc(sizeof(struct parser_stack));
    new_head->value = value;
    new_head->next = stack;
    return new_head;
}

struct parser_stack *pop_parser_stack_value(struct parser_stack *stack) {
    struct parser_stack *new_stack = stack->next;
    free(stack);
    return new_stack;
}

struct parser_stack *create_parser_stack() {
    struct parser_stack *stack = malloc(sizeof(struct parser_stack));
    *stack = (struct parser_stack){0};
    return stack;
}

int get_next_state(struct parser_stack *stack, enum token_type tkn_type) {
    return parse_table[stack->value.state][tkn_type].value.next_state;
}

reduce_rule get_reduce_rule(struct parser_stack *stack, enum token_type tkn_type) {
    return parse_table[stack->value.state][tkn_type].value.rule;
}

double parse(struct token *tokens) {
    struct parser_stack *stack = create_parser_stack();
    int inp_pos = 0;
    while (true) {
        int state = stack->value.state;
        struct token token = tokens[inp_pos];
        struct parse_table_item next_action = parse_table[state][token.type];
        switch (next_action.action) {
        case ERROR:
            return NAN;
        case ACCEPT:
            return stack->value.value.tkn_value.num;
        case SHIFT:
            inp_pos++;
            struct parser_stack_value new_value =
                (struct parser_stack_value){.value = token, .state = next_action.value.next_state};
            stack = push_parser_stack_value(stack, new_value);
            break;
        case REDUCE:
            next_action.value.rule(&stack);
            break;
        default:
            return NAN;
        }
    }
    return NAN;
}

// EXPR -> EXPR + TERM
void reduce_rule_1(struct parser_stack **stack) {
    double val1 = (*stack)->value.value.tkn_value.num;
    *stack = pop_parser_stack_value(*stack);
    *stack = pop_parser_stack_value(*stack);
    double val2 = (*stack)->value.value.tkn_value.num;
    *stack = pop_parser_stack_value(*stack);
    struct parser_stack_value new_head = (struct parser_stack_value){
        .state = get_next_state(*stack, TKN_EXPR),
        .value = (struct token){.type = TKN_EXPR, .tkn_value.num = val1 + val2}
    };
    *stack = push_parser_stack_value(*stack, new_head);
}

// EXPR -> EXPR - TERM
void reduce_rule_2(struct parser_stack **stack) {
    double val1 = (*stack)->value.value.tkn_value.num;
    *stack = pop_parser_stack_value(*stack);
    *stack = pop_parser_stack_value(*stack);
    double val2 = (*stack)->value.value.tkn_value.num;
    *stack = pop_parser_stack_value(*stack);
    struct parser_stack_value new_head = (struct parser_stack_value){
        .state = get_next_state(*stack, TKN_EXPR),
        .value = (struct token){.type = TKN_EXPR, .tkn_value.num = val2 - val1}
    };
    *stack = push_parser_stack_value(*stack, new_head);
}

// EXPR -> TERM
void reduce_rule_3(struct parser_stack **stack) {
    (*stack)->value.value.type = TKN_EXPR;
    (*stack)->value.state = get_next_state((*stack)->next, TKN_EXPR);
}

// TERM -> TERM * NUMBER
void reduce_rule_4(struct parser_stack **stack) {
    double val1 = (*stack)->value.value.tkn_value.num;
    *stack = pop_parser_stack_value(*stack);
    *stack = pop_parser_stack_value(*stack);
    double val2 = (*stack)->value.value.tkn_value.num;
    *stack = pop_parser_stack_value(*stack);
    struct parser_stack_value new_head = (struct parser_stack_value){
        .state = get_next_state(*stack, TKN_TERM),
        .value = (struct token){.type = TKN_TERM, .tkn_value.num = val1 * val2}
    };
    *stack = push_parser_stack_value(*stack, new_head);
}

// TERM -> TERM / NUMBER
void reduce_rule_5(struct parser_stack **stack) {
    double val1 = (*stack)->value.value.tkn_value.num;
    *stack = pop_parser_stack_value(*stack);
    *stack = pop_parser_stack_value(*stack);
    double val2 = (*stack)->value.value.tkn_value.num;
    *stack = pop_parser_stack_value(*stack);
    struct parser_stack_value new_head = (struct parser_stack_value){
        .state = get_next_state(*stack, TKN_TERM),
        .value = (struct token){.type = TKN_TERM, .tkn_value.num = val2 / val1}
    };
    *stack = push_parser_stack_value(*stack, new_head);
}

// TERM -> NUMBER
void reduce_rule_6(struct parser_stack **stack) {
    (*stack)->value.value.type = TKN_TERM;
    (*stack)->value.state = get_next_state((*stack)->next, TKN_TERM);
}

// TERM -> (EXPR)
void reduce_rule_7(struct parser_stack **stack) {
    *stack = pop_parser_stack_value(*stack);              // pop (
    struct parser_stack_value new_head = (*stack)->value; // save EXPR
    *stack = pop_parser_stack_value(*stack);              // pop EXPR
    *stack = pop_parser_stack_value(*stack);              // pop )
    new_head.value.type = TKN_TERM;                       // TEMR -> EXPR
    new_head.state = get_next_state((*stack), TKN_TERM);  // Save TERM as new head
    *stack = push_parser_stack_value(*stack, new_head);
}
