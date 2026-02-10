
#include <stdio.h>
#include "def_struct.h"
#include "Func_HBV.h"
#include "Func_Snow.h"
#include "Func_Soil.h"
#include "Func_Groundwater.h"
#include "Func_Routing.h"

void HBV_DynamicPara(
    ST_VAR_IN *p_vars_in,
    ST_VAR_HBV *p_vars_HBV,
    ST_PARA *p_para,
    int len
)
{
    // initial state
    double pre_Snowpack, pre_Snowpack_liquid, pre_Snowpack_ice;
    double pre_S_SOIL;
    double flux_GW, flux_Soil;
    double pre_S_UZ, pre_S_LZ;

    for (int i = 0; i < len; i++)
    {
        if (i == 0)
        {
            /* code */
            pre_Snowpack = 0.0;
            pre_Snowpack_liquid = 0.0;
            pre_Snowpack_ice = 0.0;
            pre_S_SOIL = 0.3 * (p_para + i)->P_FC;
            pre_S_UZ = 5;
            pre_S_LZ = 5;
        } else {
            pre_Snowpack = (p_vars_HBV + i - 1)->Snowpack;
            pre_Snowpack_liquid = (p_vars_HBV + i - 1)->Snowpack_liquid;
            pre_Snowpack_ice = (p_vars_HBV + i - 1)->Snowpack_ice;
            pre_S_SOIL = (p_vars_HBV + i - 1)->S_SOIL;
            pre_S_UZ = (p_vars_HBV + i - 1)->S_UZ;
            pre_S_LZ = (p_vars_HBV + i - 1)->S_LZ;
        }
        
        /**************
         * snow routine
         * ************/
        prec_partition(
            (p_vars_in + i)->Prec,
            (p_vars_in + i)->Tair,
            (p_para + i)->P_TT,
            (p_para + i)->P_SFCF,
            &((p_vars_HBV + i)->Rainfall),
            &((p_vars_HBV + i)->Snowfall));
        Routine_snow(
            (p_vars_in + i)->Tair,
            (p_vars_HBV + i)->Rainfall,
            (p_vars_HBV + i)->Snowfall,
            pre_Snowpack,
            pre_Snowpack_ice,
            pre_Snowpack_liquid,
            &((p_vars_HBV + i)->Snowpack),
            &((p_vars_HBV + i)->Snowpack_ice),
            &((p_vars_HBV + i)->Snowpack_liquid),
            &((p_vars_HBV + i)->Melt),
            &((p_vars_HBV + i)->Refreeze),
            &((p_vars_HBV + i)->I),
            (p_para + i)->P_TT,
            (p_para + i)->P_CFMAX,
            (p_para + i)->P_CFR,
            (p_para + i)->P_CWH);
        Routine_soil(
            pre_S_SOIL,
            (p_vars_in + i)->Epot,
            (p_vars_HBV + i)->I,
            &((p_vars_HBV + i)->Eact),
            &((p_vars_HBV + i)->S_SOIL),
            &flux_GW,
            &flux_Soil,
            (p_para + i)->P_BETA,
            (p_para + i)->P_FC,
            (p_para + i)->P_LP);
        Routine_groundwater(
            flux_GW,
            pre_S_UZ,
            pre_S_LZ,
            &((p_vars_HBV + i)->S_UZ),
            &((p_vars_HBV + i)->S_LZ),
            &((p_vars_HBV + i)->QGW),
            &((p_vars_HBV + i)->QGW0),
            &((p_vars_HBV + i)->QGW1),
            &((p_vars_HBV + i)->QGW2),
            (p_para + i)->P_K0,
            (p_para + i)->P_K2,
            (p_para + i)->P_K2,
            (p_para + i)->P_UZL,
            (p_para + i)->P_PERC);
    }
}


