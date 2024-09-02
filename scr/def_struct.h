#ifndef DEF_STRUCT
#define DEF_STRUCT
typedef struct
{
    /* data */
    char FP_DATA[300];
    char FP_OUT[300];
    char HBV_PARA_flag[10];
    char HBV_PARA[300];
    char FLAG_Qobs[10];
    char FLAG_Mute[10];
    int CALC_N;

} ST_GP;

typedef struct
{
    double Prec;
    double Tair;
    double Epot;
    double Qobs;
} ST_VAR_IN;


typedef struct 
{
    double Rainfall;
    double Snowfall;
    double Melt;
    double Refreeze;
    double Snowpack;
    double Snowpack_ice;
    double Snowpack_liquid;
    double Eact;
    double S_SOIL;
    double I;
    double S_UZ;
    double S_LZ;
    double QGW;
    double QGW0;
    double QGW1;
    double QGW2;

} ST_VAR_HBV;

typedef struct 
{
    double P_TT;
    double P_CFMAX;
    double P_SFCF;
    double P_CFR;
    double P_CWH;
    double P_FC;
    double P_LP;
    double P_BETA;
    double P_K0;
    double P_K1;
    double P_K2;
    double P_UZL;
    double P_PERC;
    double P_MAXBAS;
} ST_PARA;


typedef struct
{
    int y;
    int m;
    int d;
} ST_DATE;


#endif
