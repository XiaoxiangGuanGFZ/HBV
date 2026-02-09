
#include <stdio.h>
#include "Func_Snow.h"


void prec_partition(
    double Prec,
    double Tair,
    double P_TT,
    double P_SFCF,
    double *Rainfall,
    double *Snowfall
)
{
    /***************
     * rainfall and snowfall partition,
     * based just on air temperature
     * -- inputs:
     * Prec: total precipitation, mm/d
     * Tair: (daily average) air temperature, degree C
     * -- parameters: 
     * P_TT: a threshold temperature, degree C. 
     * P_SFCF: To account for undercatch of snow precipitation and winter evaporation, 
     *  which is little known, 
     *  snow accumulation is adjusted by a free parameter, P_SFCF, 
     *  the snowfall correction factor.
     * ************/
    if (Tair > P_TT)
    {
        *Rainfall = Prec;
        *Snowfall = 0.0;
    } else {
        *Snowfall = Prec * P_SFCF;
        *Rainfall = 0.0;
    }
}

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
)
{
    /******************
     * The snow routine of the model controls snow accumulation and melt
     * -- inputs:
     * Tair: (daily average) air temperature, degree C
     * Rainfall: rainfall (liquid water) from precipitation partition 
     * Snowfall: snowfall (solid water)
     * 
     * -- parameters:
     * P_TT: a threshold temperature, degree C. 
     * P_CFMAX: degree-day factor (mm/C/day), which controls the rate of snowmelt per degree-day, melting capacity
     * P_CFR: refreezing coefficient, fraction of melted snow that refreezes
     * ****************/
    double Melt_tmp;
    double Refreeze_tmp;
    
    // Snowpack_ice: the solid water content of the snow pack
    // Snowpack_liquid: the liquid water content of the snow pack

    if (Tair > P_TT)
    {
        // air temperature is higher than the threshold; solid (ice) snow will melt
        if (Snowpack_ice > 0.0)
        {
            Melt_tmp = P_CFMAX * (Tair - P_TT);
            if (Melt_tmp > Snowpack_ice)
            {
                *Melt = Snowpack_ice;
            } else {
                *Melt = Melt_tmp;
            }
        } else {
            *Melt = 0.0;
        }
        *Refreeze = 0.0;
    } else {
        // air temperature is lower than the threshold, Tair <= P_TT, refreezing ... 
        if (Snowpack_liquid > 0.0)
        {
            Refreeze_tmp = P_CFR * P_CFMAX * (P_TT - Tair);
            if (Refreeze_tmp > Snowpack_liquid)
            {
                *Refreeze = Snowpack_liquid;
            } else {
                *Refreeze = Refreeze_tmp;
            }
        }
        *Melt = 0.0;
    }
    
    // update snowpack state (after the calculation time step)
    *Snowpack_ice_post = Snowpack_ice + Snowfall + *Refreeze - *Melt;
    *Snowpack_liquid_post = Snowpack_liquid + Rainfall + *Melt - *Refreeze;
    double max_liq; // liquid water retaining capacity
    max_liq = P_CWH * *Snowpack_ice_post; 
    if (*Snowpack_liquid_post > max_liq) {
        *I = *Snowpack_liquid_post - max_liq;
        *Snowpack_liquid_post = max_liq;
    } else {
        *I = 0.0;
    }

    *Snowpack_post = *Snowpack_ice_post + *Snowpack_liquid_post;
}

