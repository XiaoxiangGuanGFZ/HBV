#ifndef DEF_STRUCT
#define DEF_STRUCT
typedef struct
{
    /* data */
} ST_GP;

typedef struct
{
    double Prec;
    double Tair;
    double Ep;
} ST_VAR_IN;


typedef struct 
{
    double SM;
    double Rainfall;
    double Snowfall;
    double Melt;
    double Snowpack;
    double Snowpack_ice;
    double Snowpack_liquid;
    double Eact;
    double S_SOIL;
    double I;
    
} ST_VAR_HBV;

typedef struct 
{
    double P_TT;
    double P_SFCF;
    double P_CFMAX;
    double P_CWH;
    double P_CFR;
    double P_FC;
    double P_LP;
    double P_PERC;
    double P_BETA;
    double P_K0;
    double P_K1;
    double P_K2;
    double P_MAXBAS;
    
} ST_PARA;


typedef struct
{
    int y;
    int m;
    int d;
} ST_DATE;


#endif
