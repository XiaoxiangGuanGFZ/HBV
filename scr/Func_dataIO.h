#ifndef FUNC_IO
#define FUNC_IO

extern int flag_obs;
extern int flag_mute;
extern int flag_homo;

void import_global(
    char fname[], ST_GP *p_gp);

void removeLeadingSpaces(char *str);

void import_data(
    char FP_DATA[],
    int CALC_N,
    ST_DATE *ts_date,
    ST_VAR_IN *p_vars_in);

void Write_HBV_sim2csv(
    char *FP_OUT,
    ST_DATE *ts_date,
    ST_VAR_IN *p_vars_in,
    ST_VAR_HBV *p_vars_HBV,
    double *Qsim,
    int CALC_N);


#endif
