#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include <limits.h>

enum
{
GETOPT_KMTOM_CHAR = (CHAR_MIN - 2),
GETOPT_MTOKM_CHAR = (CHAR_MIN - 3),
GETOPT_KGTOP_CHAR = (CHAR_MIN - 4),
GETOPT_PTOKG_CHAR = (CHAR_MIN - 5),
GETOPT_DTOR_CHAR = (CHAR_MIN - 6),
GETOPT_RTOD_CHAR = (CHAR_MIN - 7),
GETOPT_CTOF_CHAR = (CHAR_MIN - 8),
GETOPT_FTOC_CHAR = (CHAR_MIN - 9),
GETOPT_CTOK_CHAR = (CHAR_MIN - 10),
GETOPT_KTOC_CHAR = (CHAR_MIN - 11),
GETOPT_FTOK_CHAR = (CHAR_MIN - 12),
GETOPT_KTOF_CHAR = (CHAR_MIN - 13)
};

double convert(int argc, char* argv[]) {
    int c;
    while (1) {
        static struct option long_opt[] = {
            {"kmtom", required_argument, 0, GETOPT_KMTOM_CHAR},
            {"mtokm", required_argument, 0, GETOPT_MTOKM_CHAR},
            {"kgtop", required_argument, 0, GETOPT_KGTOP_CHAR},
            {"ptokg", required_argument, 0, GETOPT_PTOKG_CHAR},
            {"dtor", required_argument, 0, GETOPT_DTOR_CHAR},
            {"rtod", required_argument, 0, GETOPT_RTOD_CHAR},
            {"ctof", required_argument, 0, GETOPT_CTOF_CHAR},
            {"ftoc", required_argument, 0, GETOPT_FTOC_CHAR},
            {"ctok", required_argument, 0, GETOPT_CTOK_CHAR},
            {"ktoc", required_argument, 0, GETOPT_KTOC_CHAR},
            {"ftok", required_argument, 0, GETOPT_FTOK_CHAR},
            {"ktof", required_argument, 0, GETOPT_KTOF_CHAR},
            {0,0,0,0}
                    };
        int optIdx;
        if((c = getopt_long(argc, argv, "", long_opt, &optIdx)) == -1)
        break;
        switch(c){
            case GETOPT_KMTOM_CHAR:
                return(strtod(optarg, NULL) * 1.6);
            case GETOPT_MTOKM_CHAR:
                return(strtod(optarg, NULL) / 1.6);
            case GETOPT_KGTOP_CHAR:
                return(strtod(optarg, NULL)  * 2.2046);
            case GETOPT_PTOKG_CHAR:
                return(strtod(optarg, NULL) / 2.2046);
            case GETOPT_DTOR_CHAR:
                return(strtod(optarg, NULL) / 180 * 3.14);
            case GETOPT_RTOD_CHAR:
                return(strtod(optarg, NULL) / 3.14 * 180);
            case GETOPT_CTOF_CHAR:
                return((strtod(optarg, NULL) * 9 / 5) + 32);
            case GETOPT_FTOC_CHAR:
                return((strtod(optarg, NULL) - 32) * 5 / 9);
            case GETOPT_CTOK_CHAR:
                return(strtod(optarg, NULL) + 273);
            case GETOPT_KTOC_CHAR:
                return(strtod(optarg, NULL) - 273);
            case GETOPT_FTOK_CHAR:
                return((strtod(optarg, NULL) - 32) * 5 / 9 + 273);
            case GETOPT_KTOF_CHAR:
                return((strtod(optarg, NULL) - 273) * 9 / 5 + 32);
            default:
                return(-1);
        }
    }
}