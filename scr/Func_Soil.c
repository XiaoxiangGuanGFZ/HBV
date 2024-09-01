
#include <stdio.h>
#include <math.h>
#include "Func_Soil.h"



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
)
{
    //The distribution of infiltration water: sum of snowmelt and rainfall

    *flux_GW = I * pow(SM_pre / P_FC, P_BETA); // groundwater recharge
    *flux_Soil = I - *flux_GW; // soil recharge
    
    // evaporation from soil
    double tmp;
    tmp = SM_pre / (P_FC * P_LP);
    if (tmp > 1)
    {
        tmp = 1.0;
    }
    *Eact = Epot * tmp; // the actual estimated evaporation

    tmp = *flux_Soil + SM_pre - *Eact;
    if (tmp > P_FC)
    {
        // the soil is full (with SM reaching its capacity P_FC)
        *flux_GW += tmp - P_FC; // excess water into groundwater
        *SM_post = P_FC;
    } 
    else if (tmp < 0.0)
    {
        // not enough soil water for evaporation, 
        *Eact = *flux_Soil + SM_pre;
        *SM_post = 0.0;
    } else {
        *SM_post = tmp;
    }
}

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
)
{
    *S_UZ_post = S_UZ + flux_GW;
    if (*S_UZ_post > P_UZL)
    {
        //If the upper reservoir water level is above the threshold for near surface flow
        *QGW0 = P_K0 * (*S_UZ_post - P_UZL);
        *S_UZ_post -= *QGW0;
    } else {
        *QGW0 = 0.0;
    }
    
    if (*S_UZ_post > 0.0)
    {
        *QGW1 = P_K1 * *S_UZ_post;
        *S_UZ_post -= *QGW1;
    } else {
        *QGW1 = 0.0;
    }

    if (*S_UZ_post > P_PERC)
    {
        *S_LZ_post = S_LZ + P_PERC;
        *S_UZ_post -= P_PERC;
    } else {
        *S_LZ_post += *S_UZ_post;
        *S_UZ_post = 0.0;
    }
    
    if (*S_LZ_post > 0.0)
    {
        *QGW2 = P_K2 * *S_LZ_post;
        *S_LZ_post -= *QGW2;
    } else {
        *QGW2 = 0.0;
    }
    
    *QGW = *QGW0 + *QGW1 + *QGW2;
}