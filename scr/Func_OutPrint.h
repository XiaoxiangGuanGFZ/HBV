#ifndef FUNC_PRINT
#define FUNC_PRINT

extern int flag_obs;

void print_global(
    ST_GP *p_gp
);

void print_UH(
    double *UH,
    int P_MAXBAS_int
);

void preview_data(
    ST_DATE *ts_date,
    ST_VAR_IN *p_vars_in,
    int len
);

void print_para_homo(
    ST_PARA *p_para);

#endif
