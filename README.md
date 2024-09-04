## The HBV hydrological model

## Introduction

It is a program written in C for hydrological simulation with HBV model.
The model is a conceptual and semi-lumped hydrological model for runoff simulation and prediction. 

### file structure

- `scr`: the c source code files and header files, together with a `CMakeLists.txt` file for compiling and building the executable with `CMake` tool.
- `data`: contains example data file `example_data.csv` and program configuration file `gp.txt`
- `Rscr`: R scripts for model parameter optimization based on SCE-UA algorithm
- `doc`: a technical document, where the HBV model structure and parameters are documented.
- `references`: some academic papers related to HBV model
- `README.md`: what you see right now.

## How-To-Use

### compile 
navigate to `scr` directory in command-line or shell environment, and then call `CMake` tool to compile and build the executable. Use the following commands to compile: 

```sh
cd ./HBV/scr/
mkdir build
cd build
cmake ..
make
```

then in command-line to run the program:

```sh
./HBV.exe ../../data/gp.txt
```

the configure file `gp.txt` contains some field-value pairs to controls the behaviors of the program.

### program configure file `gp.txt`

The configuration file `gp.txt` gives the key arguments for program running, including the file paths and names to data file and simulation output file, the HBV parameters, and the simulation length.

see `./data/gp.txt` for an example.

### data file preparation
For HBV model simulation, the following weather variables are required: air temperature, precipitation and potential evapotranspiration. The observed runoff is optional, which could be placed on the last column and the field `FLAG_Qobs` then could be set as `TRUE` in the configure file `gp.txt`. If no observed runoff is available, `FLAG_Qobs` must be `FALSE`.

The variables should be put in a comma-delimited text file, and here is an example data file:

```
y,m,d,T(ºC),P(mm/d),PET(mm/d),qout(mm/d)
2000,12,16,12.72,0,0,0
2000,12,17,15.23,0,20,0.63
2000,12,18,15.31,0,19.99,0.74
2000,12,19,12.82,0,19.99,0.63
2000,12,20,10.45,0,19.98,0.53
...
```

### program output

the simulated runof, together with some sub-process variables, is returned from the program. See `./data/example_sim.csv` for an example.

The progam log is printed to the screen when `FLAG_Mute` in `gp.txt` is set as `FALSE`.

If `FLAG_Qobs` is `TRUE`, in the end the program will print the calculated Nash–Sutcliffe efficiency coefficient (NSE) in the screen.

## Others
### parameter optimization

A R script `./Rscr/HBV_SCEUA.R` gives the guide how to optimize the parameters in HBV with the support of R library `rtop`, where the SCE-UA optimization algorithm can be relied on. See the comments in the script for guidence.


## Contact

[Xiaoxiang Guan](guan@gfz-potsdam.de)


