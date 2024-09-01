
#include <stdio.h>
#include <stdlib.h>
#include "Func_Routing.h"


void UH_triangle_generate(
    double P_MAXBAS,
    double **UH,
    int *P_MAXBAS_int
)
{
    int m2;
    m2 = (int) ((P_MAXBAS / 2) - 1); // the middle point

    *P_MAXBAS_int = (int) P_MAXBAS + 1;
    
    double wsum = 0.0;
    
    *UH = (double *)malloc(sizeof(double) * *P_MAXBAS_int);

    for (int i = 0; i < *P_MAXBAS_int; i++)
    {
        if (i <= m2) 
        {
            *(*UH + i) = i + 1;
        } else {
            *(*UH + i) = *P_MAXBAS_int - i;
        }
        wsum += *(*UH + i);
    }
    for (size_t i = 0; i < *P_MAXBAS_int; i++)
    {
        *(*UH + i) /= wsum;
    }
}

void UH_Routing(
    double *QGW,
    double *UH,
    double **Qsim,
    int P_MAXBAS_int,
    int len
)
{
    for (size_t i = 0; i < len; i++)
    {
        *(*Qsim + i) = 0.0;
        for (size_t j = 0; j < P_MAXBAS_int; j++)
        {
            if (i - j >= 0)
            {
                *(*Qsim + i) += *(UH + j) * *(QGW + i - j);
            }
        }
    }    
}
