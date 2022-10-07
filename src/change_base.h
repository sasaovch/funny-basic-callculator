#ifndef CALC_CHANGE_BASE
#define CALC_CHANGE_BASE

enum change_base_result { OK, INVALID_BASE, OVERFLOW };

enum change_base_result changeBase(char *str, int from_radix, int to_radix, char **res);

enum change_base_result convert_to_base_n_string(unsigned long val, int radix, char **res);

enum change_base_result convert_string_to_base_n(const char *str, int radix, unsigned long *val);

#endif