#ifndef FUNC_SOIL
#define FUNC_SOIL

void Routine_soil(
    double SM_pre,
    double Epot,
    double I,
    double *Eact,
    double *SM_post,
    double *flux_GW,
    double *flux_Soil,
    double P_BETA,
    double P_FC,
    double P_LP
);


#endif


