#include <getopt.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "change_base.h"
#include "convert.h"
#include "math.h"

struct calc_mode {
    char *shortName;
    char *longName;
    int (*run)(int, char *[]);
};

static int run_math_with_options(int argc, char *argv[]);
static int run_convert_with_options(int argc, char *argv[]);
static int run_change_base_with_options(int argc, char *argv[]);
static int print_help(int argc, char *argv[]);
static bool find_mode_by_name(char mode_name[], const struct calc_mode modes[],
                              struct calc_mode *res);
static void fprint_mode_names(FILE *__restrict __stream, const struct calc_mode modes[]);

static const struct calc_mode modes[] = {
    {"m",  "math",        run_math_with_options       },
    {"c",  "convert",     run_convert_with_options    },
    {"cb", "change-base", run_change_base_with_options},
    {"h",  "help",        print_help                  },
    {0,    0,             0                           }
};

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Mode must be specified.\nAvailable modes:\n");
        fprint_mode_names(stdout, modes);
        return 1;
    }

    struct calc_mode choosen_mode;

    if (!find_mode_by_name(argv[1], modes, &choosen_mode)) {
        fprintf(stderr, "Illegal mode value '%s' available modes:\n", argv[1]);
        fprint_mode_names(stderr, modes);
        return 1;
    }

    return choosen_mode.run(argc, argv);
}

static bool find_mode_by_name(char mode_name[], const struct calc_mode modes[],
                              struct calc_mode *res) {
    for (size_t i = 0; modes[i].shortName && modes[i].longName; i++) {
        if (strcmp(mode_name, modes[i].shortName) == 0 ||
            strcmp(mode_name, modes[i].longName) == 0) {
            *res = modes[i];
            return true;
        }
    }

    return false;
}

static void fprint_mode_names(FILE *__restrict __stream, const struct calc_mode modes[]) {
    for (size_t i = 0; modes[i].run; i++) {
        fprintf(__stream, "\t%s\t|\t%s\n", modes[i].shortName, modes[i].longName);
    }
}

static double read_double() {
    double d;
    scanf("%lf", &d);
    return d;
}

static void print_math_help() {
    printf("Math: (can be inaccurate)\n"
           "There are two math modes (unary and binary), specified by flags:"
           " -u, --unary, -b, --binary\n"
           "If mode is not specified and operation is, it would be completed in any possible mode, "
           "priority in binary.\n"
           "Binary options:\n"
           "\t| flag                | result          |\n"
           "\t| ------------------- | --------------- |\n"
           "\t| -s --sub --subract  | a - b           |\n"
           "\t| -a --add            | a +  b          |\n"
           "\t| -m --mul --multiply | a * b           |\n"
           "\t| -d --div --divide   | a / b           |\n"
           "\t| -o --mod --modulo   | a %% b          |\n"
           "\t| -p --pow --power    | a ^ b           |\n"
           "\t| ------------------- | --------------- |\n\n"
           "Unary options:\n"
           "\t| flag           | result |\n"
           "\t| -------------- | ------ |\n"
           "\t| -f --factorial | a!     |\n"
           "\t| -e --exp       | e ^ a  |\n"
           "\t| -l --ln        | ln a   |\n"
           "\t| -a --abs       | |a|    |\n"
           "\t| -------------- | ------ |\n");
}

static void print_convert_help() {
    printf("Convert:\n"
           "\t| flag      | result      |\n"
           "\t| --------- | ----------- |\n"
           "\t| `--kmtom` | km -> mile  |\n"
           "\t| `--mtokm` | mile -> km  |\n"
           "\t| `--kgtop` | kg -> pound |\n"
           "\t| `--kgtop` | pound -> kg |\n"
           "\t| `--dtor`  | deg -> rad  |\n"
           "\t| `--rtod`  | rad -> rad  |\n"
           "\t| `--ctof`  | °C -> °F    |\n"
           "\t| `--ctok`  | °C -> K     |\n"
           "\t| `--ftoc`  | °F -> °C    |\n"
           "\t| `--ftok`  | °F -> K     |\n"
           "\t| `--ktoc`  | K -> °C     |\n"
           "\t| `--ktof`  | K -> °F     |\n"
           "\t| --------- | ----------- |\n");
}

static void print_cb_help() {
    printf("Change base:\n"
           "\t| flag            | result                  |\n"
           "\t| --------------- | ----------------------- |\n"
           "\t| --tb --to-bin   | -> uint base 2          |\n"
           "\t| --fb --from-bin | uint base 2 ->          |\n"
           "\t| --tx --to-hex   | uint base 10 ->         |\n"
           "\t| --fx --from-hex | -> uint base 16         |\n"
           "\t| -f --from       | uint base (argvalue) -> |\n"
           "\t| -t --to         | -> uint base (argvalue) |\n"
           "\t| --------------- | ----------------------- |\n");
}

#define UNARY 1
#define BINARY 2
static int run_math_with_options(int argc, char *argv[]) {

    int mode = -1;
    int un_op = -1;
    int bin_op = -1;
    const struct option long_opt[] = {
        {"help",      no_argument, &mode,   'h'      },
        {"unary",     no_argument, &mode,   1        },
        {"binary",    no_argument, &mode,   2        },
        {"subract",   no_argument, &bin_op, MATH_SUB },
        {"add",       no_argument, &bin_op, MATH_ADD },
        {"multiply",  no_argument, &bin_op, MATH_MUL },
        {"divide",    no_argument, &bin_op, MATH_DIV },
        {"modulus",   no_argument, &bin_op, MATH_DIV },
        {"power",     no_argument, &bin_op, MATH_POW },
        {"factorial", no_argument, &un_op,  MATH_FACT},
        {"exp",       no_argument, &un_op,  MATH_EXP },
        {"ln",        no_argument, &un_op,  MATH_LN  },
        {"abs",       no_argument, &un_op,  MATH_ABS },
        {0,           0,           0,       0        }
    };

    int opt;
    int optIdx;
    while ((opt = getopt_long(argc, argv, "abdefhlmopsu", long_opt, &optIdx)) != -1) {
        switch (opt) {
        case 'a':
            un_op = MATH_ABS;
            bin_op = MATH_ADD;
            break;
        case 's':
            bin_op = MATH_SUB;
            break;
        case 'm':
            bin_op = MATH_MUL;
            break;
        case 'd':
            bin_op = MATH_DIV;
            break;
        case 'o':
            bin_op = MATH_MOD;
            break;
        case 'p':
            bin_op = MATH_POW;
            break;
        case 'f':
            un_op = MATH_FACT;
            break;
        case 'e':
            un_op = MATH_EXP;
            break;
        case 'l':
            un_op = MATH_LN;
            break;
        case 'u':
            mode = UNARY;
            break;
        case 'n':
            mode = BINARY;
            break;
        case 'h':
            print_math_help();
            return 0;
        default:
            break;
        }
    }

    double res = NAN;
    switch (mode) {
    case -1:
        // if mode is not specified
        if (bin_op != -1) {
            int val_x = read_double();
            res = calc_math_binary(bin_op, val_x, read_double());
        } else if (un_op != -1) {
            res = calc_math_unary(un_op, read_double());
        }
        break;
    case UNARY:
        res = calc_math_unary(un_op, read_double());
        break;
    case BINARY:
        res = calc_math_binary(bin_op, read_double(), read_double());
        break;
    default:
        break;
    }

    if (isnan(res)) {
        fprintf(stderr, "An error occurred, couldn't get any result.\n");
        return 1;
    }

    printf("%lf\n", res);
    return 0;
}

static int run_convert_with_options(int argc, char *argv[]) {

    static struct option long_opt[] = {
        {"kmtom", no_argument, 0, CONVERT_KMTOM},
        {"mtokm", no_argument, 0, CONVERT_MTOKM},
        {"kgtop", no_argument, 0, CONVERT_KGTOP},
        {"ptokg", no_argument, 0, CONVERT_PTOKG},
        {"dtor",  no_argument, 0, CONVERT_DTOR },
        {"rtod",  no_argument, 0, CONVERT_RTOD },
        {"ctof",  no_argument, 0, CONVERT_CTOF },
        {"ftoc",  no_argument, 0, CONVERT_FTOC },
        {"ctok",  no_argument, 0, CONVERT_CTOK },
        {"ktoc",  no_argument, 0, CONVERT_KTOC },
        {"ftok",  no_argument, 0, CONVERT_FTOK },
        {"ktof",  no_argument, 0, CONVERT_KTOF },
        {"help",  no_argument, 0, 'h'          },
        {0,       0,           0, 0            }
    };

    int opt;
    int optIdx;
    while ((opt = getopt_long(argc, argv, "h", long_opt, &optIdx)) != -1) {
        switch (opt) {
        case 'h':
            print_convert_help();
            return 0;
        default:
            break;
        }
    }

    if (opt == -1) {
        fprintf(stdout, "Unable to convert, no argument specified");
        return 1;
    }

    printf("%lf\n", convert(read_double(), opt));

    return 0;
}

static int run_change_base_with_options(int argc, char *argv[]) {
    int to_base = 10;
    int from_base = 10;
    struct option long_opt[] = {
        {"to-bin",   no_argument,       &to_base,   2  },
        {"tb",       no_argument,       &to_base,   2  },
        {"from-bin", no_argument,       &from_base, 2  },
        {"fb",       no_argument,       &from_base, 2  },
        {"to-hex",   no_argument,       &to_base,   16 },
        {"tx",       no_argument,       &to_base,   16 },
        {"from-hex", no_argument,       &from_base, 16 },
        {"fx",       no_argument,       &from_base, 16 },
        {"to",       required_argument, 0,          't'},
        {"from",     required_argument, 0,          'f'},
        {"help",     no_argument,       0,          'h'},
        {0,          0,                 0,          0  }
    };

    int opt;
    int optIdx;
    extern char *optarg;
    while ((opt = getopt_long(argc, argv, "hf:t:", long_opt, &optIdx)) != -1) {
        switch (opt) {
        case 'f':
            from_base = atoi(optarg);
            break;
        case 't':
            to_base = atoi(optarg);
            break;
        case 0:
            break;
        case 'h':
            print_cb_help();
            return 0;
        default:
            return 1;
        }
    }

    char *line;
    size_t len = 0;
    ssize_t lineSize = 0;
    lineSize = getline(&line, &len, stdin);

    // line[lineSize - 1] = \n, we don't need it
    line[lineSize - 1] = 0;

    unsigned long val;
    char *res_str;
    enum change_base_result res;
    res = convert_string_to_base_n(line, from_base, &val);
    if (res == INVALID_BASE) {
        printf("Unable to convert: base must be an int value between 2 and 16 (both included)");
    }
    if (res == OVERFLOW) { printf("Unable to convert, entered value is too big"); }

    res = convert_to_base_n_string(val, to_base, &res_str);
    if (res == INVALID_BASE) {
        printf("Unable to convert: base must be an int value between 2 and 16 (both included)");
    }

    printf("%s\n", res_str);

    free(line);
    free(res_str);

    return 0;
}

static int print_help(int argc, char *argv[]) {
    printf("Calc usage : calc MODE [OPTIONS]\nAvailable modes :\n");
    fprint_mode_names(stdout, modes);
    printf("Use (calc MODE -h | --help) to get available options.\n");

    return 0;
}
