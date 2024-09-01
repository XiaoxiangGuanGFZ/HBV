
#include <stdio.h>
#include "def_struct.h"
#include "Func_HBV.h"
#include "Func_Snow.h"

void HBV(
    ST_VAR_IN *p_vars_in,
    ST_VAR_HBV *p_vars_HBV,
    ST_PARA *p_para,
    int len
)
{

    // initial state
    (p_vars_HBV + 0)->Snowpack = 0.0;
    (p_vars_HBV + 0)->Snowpack_ice = 0.0;
    (p_vars_HBV + 0)->Snowpack_liquid = 0.0;
    (p_vars_HBV + 0)->S_SOIL = 0.3 * p_para->P_FC;

    // define temporary variables
    double Melt_tmp;
    double Refreeze_tmp;

    for (int i = 0; i < len; i++)
    {
        /**************
         * snow routine
         * ************/
        prec_partition(
            (p_vars_in + i)->Prec,
            (p_vars_in + i)->Tair,
            p_para->P_TT,
            p_para->P_SFCF,
            &((p_vars_HBV + i)->Rainfall),
            &((p_vars_HBV + i)->Snowfall));
        
    }
}