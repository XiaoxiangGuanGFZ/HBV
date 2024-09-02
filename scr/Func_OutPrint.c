
#include <stdio.h>
#include <stdlib.h>
#include "def_struct.h"
#include "Func_OutPrint.h"



void print_global(
    ST_GP *p_gp
)
{
    printf("----------- HBV setup \n");
    printf("%-13s:%s\n%-13s:%s\n%-13s:%s\n%-13s:%s\n%-13s:%s\n%-13s:%s\n%-13s:%d\n",
           "FP_DATA", p_gp->FP_DATA,
           "FP_OUT", p_gp->FP_OUT,
           "HBV_PARA_flag", p_gp->HBV_PARA_flag,
           "HBV_PARA", p_gp->HBV_PARA,
           "FLAG_Qobs", p_gp->FLAG_Qobs,
           "FLAG_Mute", p_gp->FLAG_Mute,
           "CALC_N", p_gp->CALC_N);
}


void print_UH(
    double *UH,
    int P_MAXBAS_int
)
{
    printf("----------- triangle UH\n");
    printf("%5s %5s\n", "time", "UH");
    double uh_sum = 0;
    for (int i = 0; i < P_MAXBAS_int; i++)
    {
        uh_sum += *(UH + i);
        printf("%5d %5.3f\n", i + 1, *(UH + i));
    }
    printf("%5s %5s\n%5s %4.3f\n", "-----", "-----", "sum", uh_sum);
}


void preview_data(
    ST_DATE *ts_date,
    ST_VAR_IN *p_vars_in,
    int len
)
{
    int print_len = 6;
    if (print_len > len)
    {
        print_len = len;
    }
    printf("----------- data preview\n");
    printf("%5s %5s %5s %5s %5s %5s", "y", "m", "d", "Tair", "Prec", "Epot");
    if (flag_obs == 1)
    {
        printf(" %5s\n", "Qobs");
    } else {
        printf("\n");
    }
    for (int i = 0; i < print_len; i++)
    {
        printf(
            "%5d %5d %5d %5.2f %5.2f %5.2f",
            (ts_date + i)->y, (ts_date + i)->m, (ts_date + i)->d,
            (p_vars_in + i)->Tair, (p_vars_in + i)->Prec, (p_vars_in + i)->Epot);
        if (flag_obs == 1)
        {
            printf(" %5.3f\n", (p_vars_in + i)->Qobs);
        }
        else
        {
            printf("\n");
        }
    }
    
}

void print_para_homo(
    ST_PARA *p_para)
{
    printf("----------- HBV parameters \n");
    printf("* %6s: %f\n* %6s: %f\n* %6s: %f\n* %6s: %f\n* %6s: %f\n* %6s: %f\n* %6s: %f\n* %6s: %f\n* %6s: %f\n* %6s: %f\n* %6s: %f\n* %6s: %f\n* %6s: %f\n* %6s: %f\n",
           "TT", p_para->P_TT,
           "CFMAX", p_para->P_CFMAX,
           "SFCF", p_para->P_SFCF,
           "CFR", p_para->P_CFR,
           "CWH", p_para->P_CWH,
           "FC", p_para->P_FC,
           "LP", p_para->P_LP,
           "BETA", p_para->P_BETA,
           "K0", p_para->P_K0,
           "K1", p_para->P_K1,
           "K2", p_para->P_K2,
           "UZL", p_para->P_UZL,
           "PERC", p_para->P_PERC,
           "MAXBAS", p_para->P_MAXBAS);
}