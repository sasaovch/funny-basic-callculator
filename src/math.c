#include <math.h>

#include "math.h"

double calc_math_unary(enum calc_math_unary_operations operation, double val) {
    switch (operation) {
    case MATH_FACT:
        for (double i = val - 1; i > 1; i--) {
            val *= i;
        }
        return val;
    case MATH_EXP:
        return exp(val);
    case MATH_LN:
        return log(val);
    case MATH_ABS:
        return val >= 0 ? val : -val;
    default:
        return NAN;
    }
};

double calc_math_binary(enum calc_math_binary_operations operation, double val_x, double val_y) {
    switch (operation) {
    case MATH_SUB:
        return val_x - val_y;
    case MATH_ADD:
        return val_x + val_y;
    case MATH_MUL:
        return val_x * val_y;
    case MATH_DIV:
        return val_x / val_y;
    case MATH_MOD:
        return fmod(val_x, val_y);
    case MATH_POW:
        return pow(val_x, val_y);
    default:
        return NAN;
    }
};