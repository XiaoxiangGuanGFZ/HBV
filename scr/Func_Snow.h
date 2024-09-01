#ifndef FUNC_SNOW
#define FUNC_SNOW

void prec_partition(
    double Prec,
    double Tair,
    double P_TT,
    double P_SFCF,
    double *Rainfall,
    double *Snowfall
);

void Routine_snow(
    double Tair,
    double Rainfall,
    double Snowfall,
    double Snowpack,
    double Snowpack_ice,
    double Snowpack_liquid,
    double *Snowpack_post,
    double *Snowpack_ice_post,
    double *Snowpack_liquid_post,
    double *Melt,
    double *Refreeze,
    double *I,
    double P_TT,
    double P_CFMAX,
    double P_CFR,
    double P_CWH
);


#endif


