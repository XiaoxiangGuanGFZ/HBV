#ifndef FUNC_Groundwater
#define FUNC_Groundwater

void Routine_groundwater(
    double flux_GW,
    double S_UZ,
    double S_LZ,
    double *S_UZ_post,
    double *S_LZ_post,
    double *QGW,
    double *QGW0,
    double *QGW1,
    double *QGW2,
    double P_K0,
    double P_K1,
    double P_K2,
    double P_UZL,
    double P_PERC
);


#endif


