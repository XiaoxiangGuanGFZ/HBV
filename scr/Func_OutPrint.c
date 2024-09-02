
#include <stdio.h>
#include <stdlib.h>
#include "def_struct.h"
#include "Func_OutPrint.h"



void print_global(
    ST_GP *p_gp
)
{
    printf("----------- HBV setup -----------\n");
    printf("%-13s:%s\n%-13s:%s\n%-13s:%s\n%-13s:%s\n%-13s:%s\n%-13s:%d\n%-13s:%d\n",
           "FP_DATA", p_gp->FP_DATA,
           "FP_OUT", p_gp->FP_OUT,
           "HBV_PARA_flag", p_gp->HBV_PARA_flag,
           "HBV_PARA", p_gp->HBV_PARA,
           "FLAG_Qobs", p_gp->FLAG_Qobs,
           "FLAG_Mute", p_gp->FLAG_Mute,
           "CALC_N", p_gp->CALC_N);
}

