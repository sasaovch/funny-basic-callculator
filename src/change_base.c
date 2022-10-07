#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "change_base.h"

enum change_base_result changeBase(char *str, int from_radix, int to_radix, char **res) {
    unsigned long val;

    enum change_base_result conv_res = convert_string_to_base_n(str, from_radix, &val);
    if (!conv_res) { return conv_res; }

    return convert_to_base_n_string(val, to_radix, res);
}

enum change_base_result convert_to_base_n_string(unsigned long val, int radix, char **res) {
    // if radix is not supported
    if (radix > 16 || radix < 2) { return INVALID_BASE; }

    static const char int_to_char_map[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                           '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    // log2(val) / log2(radix) == log(val, radix)
    int str_len = floor(log2(val) / log2(radix)) + 1;
    *res = malloc(str_len + 1);
    (*res)[str_len] = 0;

    for (int i = str_len - 1; i > -1; i--) {
        (*res)[i] = int_to_char_map[val % radix];
        val /= radix;
    }

    return OK;
}

enum change_base_result convert_string_to_base_n(const char *str, int radix, unsigned long *val) {
    // if radix is not supported
    if (radix > 16 || radix < 2) { return INVALID_BASE; }

    static const int char_to_int_map[] = {['0'] = 0, 1, 2,          3,  4,  5,  6,  7,
                                          8,         9, ['a'] = 10, 11, 12, 13, 14, 15};

    *val = 0;
    unsigned long prev;
    // TODO: Change condition to match only valid digits for choosen base
    for (unsigned long i = 0;
         str[i] && ((str[i] >= 0x30 && str[i] <= 0x3A) || (str[i] >= 0x61 && str[i] <= 0x66));
         i++) {
        prev = *val;
        *val *= radix;
        *val += char_to_int_map[(int)str[i]];
        if (prev > *val) { return OVERFLOW; }
    }

    return OK;
}