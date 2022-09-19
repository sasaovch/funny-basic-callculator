#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include <limits.h>

enum
{
GETOPT_TOBIN_CHAR = (CHAR_MIN - 2),
GETOPT_FROMBIN_CHAR = (CHAR_MIN - 3),
GETOPT_TOHEX_CHAR = (CHAR_MIN - 4),
GETOPT_FROMHEX_CHAR = (CHAR_MIN - 5)
};

static char* result;

char* changeBase(int argc, char* argv[]) {
    int a, c, length;
    long x;
    while (1) {
        static struct option long_opt[] = {
            {"to-bin", required_argument, 0, GETOPT_TOBIN_CHAR},
            {"tb", required_argument, 0, GETOPT_TOBIN_CHAR},
            {"from-bin", required_argument, 0, GETOPT_FROMBIN_CHAR},
            {"fb", required_argument, 0, GETOPT_FROMBIN_CHAR},
            {"to-hex", required_argument, 0, GETOPT_TOHEX_CHAR},
            {"tx", required_argument, 0, GETOPT_TOHEX_CHAR},
            {"from-hex", required_argument, 0, GETOPT_FROMHEX_CHAR},
            {"fx", required_argument, 0, GETOPT_FROMHEX_CHAR},
            {"to", required_argument, 0, 't'},
            {"from", required_argument, 0, 'f'},
            {0,0,0,0}
                    };
        int optIdx;
        if((c = getopt_long(argc, argv, "", long_opt, &optIdx)) == -1)
        break;
        switch(c){
            case GETOPT_TOBIN_CHAR:
                long long int binNumber = 0;
                int power = 0;
                long num = strtol(optarg, NULL, 10);
                while (num > 0) {
                    int rem = num % 2;
                    long long int temp = pow(10, power);
                    binNumber += rem * temp;
                    power++;
                    num /= 2;
                }
                length = snprintf(NULL, 0, "%lld", binNumber);
                result = malloc(length + 1);
                snprintf(result, length + 1, "%lld", binNumber);   
                return result;
            case GETOPT_FROMBIN_CHAR:
                x = strtol(optarg, NULL, 2);
                length = snprintf( NULL, 0, "%ld", x);
                result = malloc(length + 1);
                snprintf(result, length + 1, "%ld", x);   
                return result;
            case GETOPT_TOHEX_CHAR:
                long int num_decimal, remainder, quotient ;
                result = malloc(255);
                a = 0; 
                int var;
                quotient = strtol(optarg, NULL, 10);
                while(quotient != 0) {
                var = quotient % 16 ;
                if(var < 10)
                var = var + 48 ;
                else
                var = var + 55 ;
                result[a++]= var ;
                quotient = quotient / 16;
                }
                return result;
            case GETOPT_FROMHEX_CHAR:
                x = strtol(optarg, NULL, 16);
                length = snprintf( NULL, 0, "%ld", x);
                result = malloc(length + 1);
                snprintf(result, length + 1, "%ld", x);   
                return result;
            default:
                return("Error");
        }
    }
}