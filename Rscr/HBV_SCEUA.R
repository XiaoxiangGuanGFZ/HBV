# ------------ introduction -----------
# HBV hydrological model, 
# coupled with SCE-UA algorithm (from library rtop)
# parameter optimization.
# author: Xiaoxiang Guan (guan@gfz-potsdam.de)
# Last updated: Sep-2024

# ---- set work space, load libraries
library(tidyverse)
library(rtop)
source("D:/HBV/Rscr/metrics.R")

# ---- file path and name 
ws <- "D:/HBV/"
fp_HBV <<- paste0(ws, "scr/build/HBV.exe ")  # the PML c program
fp_gp <<- paste0(ws, "data/gp_SCEUA.txt")   # the PML.exe program configure file
fp_data <- paste0(ws, "data/example_data_Chitan.csv")  # the weather variable data file
fp_out <- paste0(ws, "data/example_sim.csv") # the output file 
# fp_para <<- paste0(ws, "data/PMLpara_AU-Whr.csv") # the PML parameter file
CALC_N <<- 12784     # the number of lines (observations) in data file, excluding the header line


para_initial <<- c(0.0,   5,  1.0,  0.02, 0.05, 100, 0.5,   3, 0.5,  0.1,  0.05,  10,  1,  3)
para_str = paste(para_initial, collapse = ";")
# ------- 
df_gp <<- data.frame(
  field_name = c("FP_DATA", "FP_OUT", "HBV_PARA_flag", "HBV_PARA", "CALC_N", "FLAG_Qobs", "FLAG_Mute"),
  field_value = c(
    fp_data, fp_out, "homo", para_str, CALC_N, "TRUE", "TRUE"
  )
)

write.table(
  df_gp,
  file = fp_gp, 
  col.names = F, row.names = F, quote = F, append = F, sep = ","
)


fit = function(x) {
  
  # ---------
  # update parameter file
  # 
  para_str = paste(x, collapse = ";")
  df_gp$field_value[df_gp$field_name == "HBV_PARA"] = para_str
  write.table(
    df_gp, file = fp_gp,
    col.names = F, row.names = F, quote = F, sep = ",", append = F
  )
  
  # ----- 
  # run the HBV model
  NSE = system(paste0(fp_HBV, fp_gp), intern = TRUE) 
  NSE = as.numeric(NSE)
  
  return(1 - NSE)
}


# define the PML V2 parameter ranges --------
#                 TT,CFMAX,SFCF,   CFR,  CWH,  FC,  LP,BETA,  K0,   K1,   K2,  UZL,PERC,MAXBAS
para_lower =   c( -2,   1,  0.5,     0, 0.01,  50, 0.3,   1, 0.1, 0.01, 0.001,   0,  0,  1)
para_upper =   c(  2,  10,  2.0,   0.1,  0.1, 900, 1.0,   6, 1.0,  0.5,  0.10, 100,  3,  7)
para_initial = c(0.0,   5,  1.0,  0.02, 0.05, 100, 0.5,   3, 0.5,  0.1,  0.05,  10,  1,  3)

# optimizing 
sceua_HBV = sceua(
  fit, 
  pars = para_initial, lower = para_lower, upper = para_upper, 
  maxn = 6000, pcento = 0.0001, iprint = 1
)

# check the optimization result
sceua_HBV

system(paste0(fp_HBV, fp_gp), intern = TRUE) 

sceua_HBV
