# CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
project(HBV)  # Set your project name here
enable_language(C)

# Add your source files here
set(SOURCE_FILES
    main.c
    Func_Snow.c
    Func_Soil.c
    Func_Routing.c
    Func_dataIO.c
    Func_OutPrint.c
    Func_HBV.c
    Func_Metric.c
    Func_Para.c
)


# Add the executable target
add_executable(HBV ${SOURCE_FILES})
# Link against the math library
target_link_libraries(HBV m)


## cmake -G "MinGW Makefiles" ..
## mingw32-make
