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

char* parseCommand(int argc, char* argv[]) {
    int c;
    while (1) {
        static struct option long_opt[] = {
            {"to-bin", no_argument, 0, GETOPT_TOBIN_CHAR},
            {"tb", no_argument, 0, GETOPT_TOBIN_CHAR},
            {"from-bin", no_argument, 0, GETOPT_FROMBIN_CHAR},
            {"fb", no_argument, 0, GETOPT_TOBIN_CHAR},
            {"to-hex", no_argument, 0, GETOPT_TOHEX_CHAR},
            {"tx", no_argument, 0, GETOPT_TOHEX_CHAR},
            {"from-hex", no_argument, 0, GETOPT_FROMHEX_CHAR},
            {"fx", no_argument, 0, GETOPT_FROMHEX_CHAR},
            {"to", no_argument, 0, 't'},
            {"from", no_argument, 0, 'f'},
            {0,0,0,0}
                    };
        int optIdx;
        if((c = getopt_long(argc, argv, 0, long_opt, &optIdx)) == -1)
        break;
        switch(c){
            case GETOPT_TOBIN_CHAR:
                int k;
                int a = strtol(optarg, NULL, 10);
                int i = 0;
                char *b;
                for (c = 31; c >= 0; c--)
                {
                    k = a >> c;
                    if (k & 1)
                    b[i] = '1';
                    else
                    b[i] = '0';
                    i++;
                }
                return b;
            case GETOPT_FROMBIN_CHAR:
                return strtol(optarg, NULL, 2);
            case GETOPT_TOHEX_CHAR:
                long int num_decimal , remainder , quotient ;
                int a = 1 , b , var ;
                char hexanum_decimal[ 100 ] ;
                quotient = strtol(optarg, NULL, 10);
                while( quotient != 0 ) {
                var = quotient % 16 ;
                if( var < 10 )
                var = var + 48 ;
                else
                var = var + 55 ;
                hexanum_decimal[a++]= var ;
                quotient = quotient / 16;
                }
                return hexanum_decimal;
            case GETOPT_FROMHEX_CHAR:
                return strtol(optarg, NULL, 16);
            default:
                return(-1);
        }
    }
}