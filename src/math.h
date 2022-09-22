#ifndef CALC_MATH
#define CALC_MATH

enum calc_math_unary_operations { MATH_FACT, MATH_EXP, MATH_LN, MATH_ABS };

enum calc_math_binary_operations {
    MATH_SUB,
    MATH_ADD,
    MATH_MUL,
    MATH_DIV,
    MATH_MOD,
    MATH_POW
};

double calc_math_unary(enum calc_math_unary_operations operation, double val);

double calc_math_binary(enum calc_math_binary_operations operation,
                        double val_x, double val_y);

#endif