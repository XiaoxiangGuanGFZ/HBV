


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
    double Melt_tmp;
    double Refreeze_tmp;
    
    // initialize the snowpack states
    *Snowpack_ice_post = Snowpack_ice + Snowfall;
    *Snowpack_liquid_post = Snowpack_liquid + Rainfall;

    if (Tair > P_TT)
    {
        // air temperature is higher than the threshold
        if (*Snowpack_ice_post > 0.0)
        {
            Melt_tmp = P_CFMAX * (Tair - P_TT);
            if (Melt_tmp > *Snowpack_ice_post)
            {
                *Melt = *Snowpack_ice_post;
                *Snowpack_ice_post = 0.0;
            } else {
                *Melt = Melt_tmp;
                *Snowpack_ice_post -= Melt_tmp;
            }
        } else {
            *Melt = 0.0;
        }
        *Refreeze = 0.0;
    } else {
        // air temperature is lower than the threshold, Tair <= P_TT
        if (*Snowpack_liquid_post > 0.0)
        {
            Refreeze_tmp = P_CFR * P_CFMAX * (P_TT - Tair);
            if (Refreeze_tmp > *Snowpack_liquid_post)
            {
                *Refreeze = *Snowpack_liquid_post;
                *Snowpack_liquid_post = 0.0;
            } else {
                *Refreeze = Refreeze_tmp;
                *Snowpack_liquid_post -= Refreeze_tmp;
            }
        }
        *Melt = 0.0;
    }
    
    // update snowpack state (after the calculation time step)
    *Snowpack_ice_post += *Refreeze;
    *Snowpack_liquid_post += *Melt;
    
    if (*Snowpack_liquid_post > P_CWH * *Snowpack_ice_post) {
        // liquid water retaining capacity: P_CWH * *Snowpack_ice_post
        *I = *Snowpack_liquid_post - P_CWH * *Snowpack_ice_post;
        *Snowpack_liquid_post = P_CWH * *Snowpack_ice_post;
    } else {
        *I = 0.0;
    }

    *Snowpack_post = *Snowpack_ice_post + *Snowpack_liquid_post;
}

