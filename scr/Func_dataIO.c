
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "def_struct.h"
#include "Func_dataIO.h"

#define MAXCHAR 1000

void import_global(
    char fname[], ST_GP *p_gp)
{
    /**************
     * import the global parameters
     *
     * -- Parameters:
     *      fname: a string (1-D character array), file path and name of the global parameters
     * -- Output:
     *      return a structure containing the key fields
     * ********************/

    char row[MAXCHAR];
    FILE *fp;
    char *token;
    char *token2;
    int i;

    if ((fp = fopen(fname, "r")) == NULL)
    {
        printf("cannot open global parameter file: %s\n", fname);
        exit(1);
    }
    while (fgets(row, MAXCHAR, fp) != NULL)
    {
        // the fgets() function comes from <stdbool.h>
        // Reads characters from stream and stores them as a C string

        /***
         * removeLeadingSpaces():
         * remove all the leading white spaces in the string if exist,
         * otherwise do nothing!
         */
        removeLeadingSpaces(row);

        if (row != NULL && strlen(row) > 1)
        {
            /*non-empty row(string)*/
            if (row[0] != '#')
            {
                /* the first character of row should not be # */
                for (i = 0; i < strlen(row); i++)
                {
                    /* remove (or hide) all the characters after # */
                    if (row[i] == '#')
                    {
                        row[i] = '\0';
                        break;
                    }
                }
                // puts(row);
                /*assign the values to the parameter structure: key-value pairs*/
                token = strtok(row, ",");       // the first column: key
                token2 = strtok(NULL, ",\r\n"); // the second column: value
                // printf("token: %s\n", token);
                /********
                 * file paths and file names
                 * *****/
                if (strncmp(token, "FP_DATA", 7) == 0)
                {
                    strcpy(p_gp->FP_DATA, token2);
                }
                else if (strncmp(token, "FP_OUT", 6) == 0)
                {
                    strcpy(p_gp->FP_OUT, token2);
                }
                else if (strncmp(token, "HBV_PARA_flag", 13) == 0)
                {
                    strcpy(p_gp->HBV_PARA_flag, token2);
                }
                else if (strncmp(token, "HBV_PARA", 8) == 0)
                {
                    strcpy(p_gp->HBV_PARA, token2);
                }
                else if (strncmp(token, "CALC_N", 5) == 0)
                {
                    p_gp->CALC_N = atoi(token2);
                }
                else if (strncmp(token, "FLAG_Qobs", 9) == 0)
                {
                    strcpy(p_gp->FLAG_Qobs, token2);
                }
                else if (strncmp(token, "FLAG_Mute", 9) == 0)
                {
                    strcpy(p_gp->FLAG_Mute, token2);
                }
                else
                {
                    printf("Error in opening global parameter file: unrecognized parameter field: %s\n", token);
                    exit(1);
                }
            }
        }
    }
    fclose(fp);
}

void removeLeadingSpaces(char *str)
{
    if (str != NULL)
    {
        int i, j = 0;
        int len = strlen(str);
        // Find the first non-space character
        for (i = 0; i < len && isspace(str[i]); i++)
        {
            // Do nothing, just iterate until the first non-space character is found
        }
        // Shift the string to remove leading spaces
        for (; i < len; i++)
        {
            str[j++] = str[i];
        }
        // Null-terminate the modified string
        str[j] = '\0';
    }
}



void import_data(
    char FP_DATA[],
    int CALC_N,
    ST_DATE *ts_date,
    ST_VAR_IN *p_vars_in)
{
    FILE *fp;
    if ((fp = fopen(FP_DATA, "r")) == NULL)
    {
        printf("Cannot open data file: %s\n", FP_DATA);
        exit(1);
    }    
    char *token;
    char row[MAXCHAR];
    char row_first[MAXCHAR];
    int i = 0; // record the number of rows in the data file
    fgets(row_first, MAXCHAR, fp); // skip the first row
    while (fgets(row, MAXCHAR, fp) != NULL && i < CALC_N)
    {
        (ts_date + i)->y = atoi(strtok(row, ",")); 
        (ts_date + i)->m = atoi(strtok(NULL, ","));
        (ts_date + i)->d = atoi(strtok(NULL, ","));
        (p_vars_in + i)->Tair = atof(strtok(NULL, ","));
        (p_vars_in + i)->Prec = atof(strtok(NULL, ","));
        (p_vars_in + i)->Epot = atof(strtok(NULL, ","));
        if (flag_obs == 1)
        {
            (p_vars_in + i)->Qobs = atof(strtok(NULL, ","));
        }
        i++;
    }
    fclose(fp);
    if (i != CALC_N)
    {
        printf("conflict numbers of lines in data file: %s\n", FP_DATA);
        exit(1);
    }
}



void Write_HBV_sim2csv(
    char *FP_OUT,
    ST_DATE *ts_date,
    ST_VAR_IN *p_vars_in,
    ST_VAR_HBV *p_vars_HBV,
    double *Qsim,
    int CALC_N)
{
    FILE *pf_out;
    if ((pf_out = fopen(FP_OUT, "w")) == NULL)
    {
        printf("Failed to create / open output file: %s\n", FP_OUT);
        exit(1);
    }

    fprintf(pf_out, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
            "y", "m", "d", 
            "Rainfall", "Snowfall", "Melt", "Refreeze", "Snowpack", "Snowpack_ice", 
            "Eact", "I",
            "S_SOIL", "S_UZ", "S_LZ",
            "QGW0", "QGW1", "QGW2", "QGW", "Qsim"
            );
    if (flag_obs == 1)
    {
        fprintf(pf_out, ",%s\n", "Qobs");
    } else {
        fprintf(pf_out, "\n");
    }
    
    for (size_t i = 0; i < CALC_N; i++)
    {
        fprintf(pf_out, "%d,%d,%d,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f",
                (ts_date + i)->y, (ts_date + i)->m, (ts_date + i)->d,
                (p_vars_HBV + i)->Rainfall,
                (p_vars_HBV + i)->Snowfall,
                (p_vars_HBV + i)->Melt,
                (p_vars_HBV + i)->Refreeze,
                (p_vars_HBV + i)->Snowpack,
                (p_vars_HBV + i)->Snowpack_ice,
                (p_vars_HBV + i)->Eact,
                
                (p_vars_HBV + i)->I,
                (p_vars_HBV + i)->S_SOIL,
                (p_vars_HBV + i)->S_UZ,
                (p_vars_HBV + i)->S_LZ,
                (p_vars_HBV + i)->QGW0,
                (p_vars_HBV + i)->QGW1,
                (p_vars_HBV + i)->QGW2,
                (p_vars_HBV + i)->QGW,
                *(Qsim + i));
        if (flag_obs == 1)
        {
            fprintf(pf_out, ",%.2f\n", (p_vars_in + i)->Qobs);
        } else {
            fprintf(pf_out, "\n");
        }
    }
    fclose(pf_out);
}



