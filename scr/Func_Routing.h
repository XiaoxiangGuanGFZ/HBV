#ifndef FUNC_ROUTING
#define FUNC_ROUTING

void UH_triangle_generate(
    double P_MAXBAS,
    double **UH,
    int *P_MAXBAS_int
);

void UH_Routing(
    double *QGW,
    double *UH,
    double **Qsim,
    int P_MAXBAS_int,
    int len
);


#endif