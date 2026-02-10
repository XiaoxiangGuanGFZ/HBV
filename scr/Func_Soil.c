
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
    /**************
     * water balance in the soil box
     * -- inputs:
     * I:       water flux to the soil box, source from rainfall, and snowmelt water. 
     * Epot:    potential evaporation, mm/d
     * SM_pre: the soil water content at the current time step
     * -- parameters:
     * P_FC:    Maximum soil moisture storage, mm
     * P_LP:    Fraction of FC at which potential evapotranspiration is reduced, 
     * P_BETA:  Shape Parameter for Runoff Generation, which controls the nonlinearity of runoff generation from the soil moisture zone
     * ***********/

    // The distribution of infiltration water: sum of snowmelt and rainfall
    // a certain amount of water goes to groundwater zone (boxes); 
    // remaining water goes to the soil box. 
    *flux_GW = I * pow(SM_pre / P_FC, P_BETA); // groundwater recharge, >= 0.0 
    *flux_Soil = I - *flux_GW; // soil recharge, >= 0.0
    
    // evaporation from soil
    double tmp;
    tmp = SM_pre / (P_FC * P_LP);
    if (tmp > 1)
    {
        tmp = 1.0;
    }
    *Eact = Epot * tmp; // the actual estimated evaporation, from soil box (moisture)

    // compute the water balance in the soil box
    tmp = *flux_Soil + SM_pre - *Eact;
    if (tmp > P_FC)
    {
        // the soil is full (with SM reaching its capacity P_FC)
        *flux_GW += tmp - P_FC; // *** excess water goes to the groundwater ***
        *SM_post = P_FC;
    } 
    else if (tmp < 0.0)
    {
        // *** not enough soil water for evaporation *** 
        *Eact = *flux_Soil + SM_pre;
        *SM_post = 0.0;
    } else {
        *SM_post = tmp;
    }
}
