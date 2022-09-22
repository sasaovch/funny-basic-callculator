#ifndef CALC_CONVERT
#define CALC_CONVERT

enum calc_convert_options {
    CONVERT_KMTOM,
    CONVERT_MTOKM,
    CONVERT_KGTOP,
    CONVERT_PTOKG,
    CONVERT_DTOR,
    CONVERT_RTOD,
    CONVERT_CTOF,
    CONVERT_FTOC,
    CONVERT_CTOK,
    CONVERT_KTOC,
    CONVERT_FTOK,
    CONVERT_KTOF
};

double convert(double value, enum calc_convert_options option);

#endif
