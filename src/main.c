#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h> 
#include "my_math.h"
#include "convert.h"
#include "change_base.h"

int main(int argc, char* argv[])
{
    char* operation = argv[1];
    char* mathMode = "math";
    char* mMode = "m";
    char* convertMode = "convert";
    char* cMode = "c";
    char* changeBaseMode = "change-base";
    char* cbMode = "cb";
    if (*operation == 'm') {
        if (strcmp(operation, mathMode) == 0 || strcmp(operation, mMode) == 0) {
            printf("Math mode \n");
            printf("%lf", parseCommand(argc, argv));
        }
    }
    if (*operation == 'c') {
        if (strcmp(operation, convertMode) == 0 || strcmp(operation, cMode) == 0) {
            printf("Convert mode\n");
            printf("%lf", convert(argc, argv));
        }
        if (strcmp(operation, changeBaseMode) == 0 || strcmp(operation, cbMode) == 0) {
            printf("Change base mode\n");
        }
    }
    exit(EXIT_SUCCESS);
}
