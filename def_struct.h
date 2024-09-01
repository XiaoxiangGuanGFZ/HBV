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
    
} ST_VAR_HBV;


typedef struct
{
    int y;
    int m;
    int d;
} ST_DATE;


#endif
