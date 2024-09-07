


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def_struct.h"
#include "Func_dataIO.h"
#include "Func_OutPrint.h"
#include "Func_HBV.h"
#include "Func_Routing.h"
#include "Func_Metric.h"
#include "Func_Para.h"
#include "Func_HBV_DynamicPara.h"

int flag_obs;
int flag_mute;
int flag_homo;

int main(int argc, char * argv[])
{
    ST_GP GP;
    import_global(*(++argv), &GP);
    
    flag_obs = 0;
    flag_mute = 0;
    flag_homo = 0;
    if (strncmp(GP.FLAG_Qobs, "TRUE", 4) == 0)
    {
        flag_obs = 1;
    }
    if (strncmp(GP.FLAG_Mute, "TRUE", 4) == 0)
    {
        flag_mute = 1;
    }
    if (strncmp(GP.HBV_PARA_flag, "homo", 4) == 0)
    {
        flag_homo = 1;
    }
    
    if (flag_mute == 0) {print_global(&GP);}
    
    /*********************
     * data and variables preparation
     * *******************/
    ST_VAR_HBV *p_vars_HBV;
    ST_VAR_IN *p_vars_in;
    ST_PARA *p_para;
    ST_DATE *ts_date;

    int len;
    len = GP.CALC_N;

    p_vars_HBV = (ST_VAR_HBV *)malloc(sizeof(ST_VAR_HBV) * len);
    p_vars_in = (ST_VAR_IN *)malloc(sizeof(ST_VAR_IN) * len);
    ts_date = (ST_DATE *)malloc(sizeof(ST_DATE) * len);
    import_data(GP.FP_DATA, len, ts_date, p_vars_in);
    if (flag_mute == 0) {preview_data(ts_date, p_vars_in, len);}

    if (flag_homo == 1)
    {
        // static parameterization:
        // parameters are extracted from one field-value pair in the GP.txt file
        p_para = (ST_PARA *)malloc(sizeof(ST_PARA) * 1);
        extract_parameters(GP.HBV_PARA, p_para);
        if (flag_mute == 0) {print_para_homo(p_para);}
    } else {
        // dynamic parameterization: parameters in a separate file
        p_para = (ST_PARA *)malloc(sizeof(ST_PARA) * len);
        read_HBVpara(
            GP.HBV_PARA,
            len,
            p_para);
        if (flag_mute == 0) {print_para_dynamic(len, p_para);}
    }
    
    
    /*********************
     * unit hydrograph generation: triangle weight
     * *******************/ 
    /****
     * attention:
     * the program assumes the UH can only be static, even though flag_homo == 1;
     * when flag_homo == 1, only the first P_MAXBAS value in dynamic parameter file is used.
     */
    double *UH;
    int P_MAXBAS_int;
    UH_triangle_generate(
        (p_para + 0)->P_MAXBAS,
        &UH,
        &P_MAXBAS_int);
    if (flag_mute == 0) {print_UH(UH, P_MAXBAS_int);}
    
    /*********************
     * HBV simulation
     * *******************/
    if (flag_homo == 1)
    {
        /* static parameters */
        HBV(p_vars_in,
            p_vars_HBV,
            p_para,
            len);
    } else {
        HBV_DynamicPara(p_vars_in,
                        p_vars_HBV,
                        p_para,
                        len);
    }
    
    /*********************
     * routing
     * *******************/
    double *Qsim, *QGW;
    Qsim = (double *)malloc(sizeof(double) * len);
    QGW = (double *)malloc(sizeof(double) * len);
    for (size_t i = 0; i < len; i++)
    {
        *(QGW + i) = (p_vars_HBV + i)->QGW;
    }
    UH_Routing(
        QGW,
        UH,
        &Qsim,
        P_MAXBAS_int,
        len);
    
    Write_HBV_sim2csv(
        GP.FP_OUT,
        ts_date,
        p_vars_in,
        p_vars_HBV,
        Qsim,
        len);
    if (flag_mute == 0)
    {
        printf("----------- HBV simulation done!\n");
    }

    /*********************
     * metric calculation: NSE, R2, RMSE, MSE, Re (%)
     * *******************/
    double nse = -99.9;
    double MSE = 99.9;
    double RMSE = 99.9;
    double R2 = 0.0;
    double Re = -99.9;
    if (flag_obs == 1)
    {
        double *Qobs;
        Qobs = (double *)malloc(sizeof(double) * len);
        for (size_t i = 0; i < len; i++)
        {
            *(Qobs + i) = (p_vars_in + i)->Qobs;
        }

        Metrics(
            Qsim, Qobs, len,
            &nse, &R2, &RMSE, &MSE, &Re);
        if (flag_mute == 0)
        {
            printf("----------- Metrics (obs vs. sim) \n");
            printf("%-4s:%6.3f\n%-4s:%6.3f\n%-4s:%6.3f\n%-4s:%6.3f\n%-4s:%6.2f%%\n",
                "NSE", nse,
                "R2", R2,
                "RMSE", RMSE,
                "MSE", MSE,
                "Re", Re * 100
            );
        }
    }
    if (flag_obs == 1)
    {
        printf("%f\n", nse);
    }
    
    /*********************
     * end of the program
     * *******************/
    free(p_vars_HBV);
    free(p_vars_in);
    free(p_para);
    free(Qsim);
    free(QGW);
    free(UH);

    return 0;
}
