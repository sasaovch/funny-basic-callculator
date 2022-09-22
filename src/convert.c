#include <getopt.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "convert.h"

double convert(double value, enum calc_convert_options option) {
    static const double KM_TO_M_COEF = 1.6;
    static const double KG_TO_POUND_COEF = 2.2046;
    static const double DEG_TO_RAD_KOEF = M_PI / 180;
    static const double CEL_TO_FAR_KOEF = 9.0 / 5.0;
    static const double CEL_TO_FAR_CONST = 32;
    static const double CEL_TO_KEL_CONST = 273;

    switch (option) {
    case CONVERT_KMTOM:
        return value * KM_TO_M_COEF;
    case CONVERT_MTOKM:
        return value / KM_TO_M_COEF;
    case CONVERT_KGTOP:
        return value * KG_TO_POUND_COEF;
    case CONVERT_PTOKG:
        return value / KG_TO_POUND_COEF;
    case CONVERT_DTOR:
        return value * DEG_TO_RAD_KOEF;
    case CONVERT_RTOD:
        return value / DEG_TO_RAD_KOEF;
    case CONVERT_CTOF:
        return value * CEL_TO_FAR_KOEF + CEL_TO_FAR_CONST;
    case CONVERT_FTOC:
        return (value - CEL_TO_FAR_CONST) / CEL_TO_FAR_KOEF;
    case CONVERT_CTOK:
        return value + CEL_TO_KEL_CONST;
    case CONVERT_KTOC:
        return value - CEL_TO_KEL_CONST;
    case CONVERT_FTOK:
        return (value - CEL_TO_FAR_CONST) / CEL_TO_FAR_KOEF + CEL_TO_KEL_CONST;
    case CONVERT_KTOF:
        return (value - CEL_TO_KEL_CONST) * CEL_TO_FAR_KOEF + CEL_TO_FAR_CONST;
    default:
        return NAN;
    }
}
