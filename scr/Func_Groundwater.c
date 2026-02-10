
#include <stdio.h>
#include <math.h>
#include "Func_Groundwater.h"

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
    /***************
     * model the water dynamics in the groundwater boxes
     * -- inputs:
     * flux_GW: water flux from soil box into the groundwater box (upper box),
     * S_UZ:    water content in the upper groundwater box
     * S_LZ:    water content in the lower groundwater box
     * 
     * -- parameters:
     * P_UZL:   Threshold level in the upper zone before quick flow occurs
     * P_PERC:  Maximum percolation rate from the upper zone to the lower zone
     * *************/
    double S_UZ_afterQ0, S_UZ_afterQ1; 
    double UpLow;

    if (S_UZ > P_UZL) {
        *QGW0 = P_K0 * (S_UZ - P_UZL + flux_GW);
        S_UZ_afterQ0 = (1/P_K0 - 1) * *QGW0 + P_UZL;
    } else {
        *QGW0 = 0.0;
        S_UZ_afterQ0 = S_UZ + flux_GW;
    }
    // ensures: S_UZ_afterQ0 + *QGW0 = S_UZ + flux_GW

    if (S_UZ_afterQ0 >= P_PERC){
        UpLow = P_PERC;
        *QGW1 = P_K1 * (S_UZ_afterQ0 - UpLow);
        S_UZ_afterQ1 = (1 / P_K1 - 1) * *QGW1;
    } else {
        UpLow = S_UZ_afterQ0;
        *QGW1 = 0.0;
        S_UZ_afterQ1 = 0.0;
    }
    // ensures: S_UZ_afterQ1 + *QGW1 + UpLow = S_UZ_afterQ0

    *QGW2 = P_K2 * (S_LZ + UpLow);
    *S_LZ_post = (1 / P_K2 - 1) * *QGW2;
    // ensures: *S_LZ_post + *QGW2 = S_LZ + UpLow;

    *S_UZ_post = S_UZ_afterQ1;

    *QGW = *QGW0 + *QGW1 + *QGW2;
    
}
