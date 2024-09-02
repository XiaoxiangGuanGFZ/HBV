
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def_struct.h"
#include "Func_Para.h"


void extract_parameters(char *param_str, ST_PARA *params) 
{
        char *token;
    int token_count = 0;

    // Initialize the parameter values with a default invalid value (e.g., -9999) to check for missing data
    double *parameters[] = {
        &params->P_TT, &params->P_CFMAX, &params->P_SFCF, &params->P_CFR, &params->P_CWH,
        &params->P_FC, &params->P_LP, &params->P_BETA, &params->P_K0, &params->P_K1,
        &params->P_K2, &params->P_UZL, &params->P_PERC, &params->P_MAXBAS
    };

    for (int i = 0; i < 14; i++) {
        parameters[i][0] = -9999;  // Initialize with a sentinel value
    }

    // Extract each value and convert to double
    token = strtok(param_str, ";");
    while (token != NULL && token_count < 14) {
        parameters[token_count][0] = atof(token);
        token = strtok(NULL, ";");
        token_count++;
    }

    // Check if all parameters were successfully extracted
    if (token_count != 14) {
        printf("Error: Missing or extra parameters in the input string.\n");
        exit(1);
    }

    // Check for missing data (any parameter still set to the sentinel value)
    for (int i = 0; i < 14; i++) {
        if (parameters[i][0] == -9999) {
            printf("Error: Missing parameter at position %d in the input string.\n", i + 1);
            exit(1);
        }
    }
}

