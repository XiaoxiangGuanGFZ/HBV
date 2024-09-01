## HBV hydrological model
### Introduction
The HBV model is a semi-distributed model, which means
that a catchment can be separated into different elevation
and vegetation zones as well as into different subcatchments. 
The model consists of different routines and simulates
catchment discharge, usually on a daily time step,
based on time series of precipitation and air temperature
as well as estimates of monthly long-term potential evaporation
rates. In the snow routine snow accumulation and
snowmelt are computed by a degree-day method. In the soil
routine groundwater recharge and actual evaporation are simulated
as functions of actual water storage. In the response
(or groundwater) routine, runoff is computed as a function
of water storage. Finally, in the routing routine a triangular
weighting function is used to simulate the routing of the
runoff to the catchment outlet.

### Snow routine

The snow routine of the model controls snow accumulation and melt and works separately for each elevation and vegetation zone. Precipitation is considered to be either snow or rain, depending on whether the temperature is above
or below a threshold temperature ($P_{TT}$). The precipitation accumulates as snow when the air temperature drops below a threshold value ($P_{TT}$). To account for undercatch of snow precipitation and winter evaporation, which is little known, snow accumulation is adjusted by a free parameter, $P_{SFCF}$, the snowfall correction factor.

$$
P_{rain} = P, T_{air} > P_{TT}
$$

$$
P_{snow} = P \cdot P_{SFCF}, T_{air} <= P_{TT}
$$


The precipitation accumulates as snow when the air temperature drops below a threshold value ($P_{TT}$). To account for undercatch of snow precipitation and winter evaporation, which is little known, snow accumulation is adjusted by a free parameter, $C_{SF}$, the snowfall correction factor.

Melt starts with temperatures above the threshold, $P_{TT}$, according to a simple degree-day expression:

$$
M = P_{CFMAX} \cdot (T(t) - P_{TT})
$$

where:

- $M$: snowmelt (mm/day)
- $P_{CFMAX}$: degree-day factor ($mm / (^{\circ}C \cdot day)$)
- $P_{TT}$: threshold temperature ($^{\circ}C$)

Meltwater and rainfall (liquid state) are retained within the snowpack until they exceed a certain fraction, $P_{CWH}$ (–), of the water equivalent of the snow, which is usually preset to 10 %. When temperatures drop below $P_{TT}$, the amount of refreezing liquid water within the snowpack, R (mm d−1), is computed using a refreezing coefficient, $P_{CFR}$ (–)

$$
R = P_{CFR} \cdot P_{CFMAX} \cdot (P_{TT} - T(t))
$$


Thus the snow routine of the HBV model has primarily three free parameters that have to be estimated by calibration: $P_{TT}$, $P_{CFMAX}$ and $P_{CFR}$· lf a separation into vegetation zones is used, the number doubles. It is also common to use separate threshold temperatures for snow accumulation and melt.


### Soil moistue routine

The soil moisture accounting routine computes an index of the wetness of the entire basin and integrates interception and soil moisture storage. 

Based on the amount of input to the soil (sum of rainfall and
snowmelt) at a certain time step, $I(t)$ (mm/d), the flux to the groundwater, $F(t)$ (mm/d), is computed. The remaining part of $P(t)$ is added to the soil box. The partition is a function of the ratio between current water content of the
soil box ($S_{SOIL}(t)$, mm) and its maximum value ($P_{FC}$, mm). 

The actual evaporation from the soil box equals the potential evaporation if $S_{SOIL}(t) / P_{FC}$ is above $P_{LP} / {P_{FC}}$, while a linear reduction is uded when $S_{SOIL}(t) / P_{FC}$ is below the value.

$$
F(t) / I(t) = (S_{SOIL}(t) / P_{FC}) ^{P_{BETA}}
$$


$$
E_{act} = E_{pot} \cdot \min(S_{SOIL}(t) / (P_{FC} \cdot P_{LP}), 1)
$$

Groundwater recharge is added to the upper groundwater box ($Z_{SU}$, mm). 
$P_{PERC}$ (mm/d) defines the maximum percolation rate from the upper to the lower groundwater box ($S_{LZ}$, mm). 

Runoff from the groundwater boxes is computed as the sum of two or three linear outflow equations $P_{K0}$,$P_{K1}$ and $P_{K2}$ (d−1), depending on whether $Z_{SU}$ is above a threshold value, $P_{UZL}$ (mm). This runoff is finally transformed by a triangular weighting function defined by the parameter $P_{MAXBAS}$ to give the simulated runoff (mm/d).

$$
Q_{GW}(t) = P_{K2} \cdot S_{LZ} + P_{K1} \cdot S_{UZ} + P_{K0} \cdot \max(S_{UZ} - P_{UZL}, 0)
$$

$$
Q_{sim}(t) = \sum_{i=1}^{P_{MAXBAS}}{c(i) \cdot Q_{GW}(t - i + 1)}
$$

where 

$$
c(i) = \int_{i-1}^{i}{2/P_{MAXBAS} - 4 / P_{MAXBAS}^2 \cdot |u - P_{MAXBAS} / 2| \, du}
$$

### Others

The long-term mean values of the potential evaporation, $E_{POT,M}(t)$, for a certain day of the year are corrected to its value at day $t$, $E_{POT}(t)$, by using the deviations of the temperature, $T(t)$, at a certain day, from its long-term mean, $T_{M}$, and a correction factor, $P_{CET}$ (C−1).

$$
E_{POT}(t) = (1 + P_{CET} \cdot (T(t) - T_{M})) \cdot E_{POT,M}
$$

but make sure:

$$
0<= E_{POT}(t) <= 2 E_{POT,M}
$$


### References

Seibert, J. and Vis, M.J.P.  2012.  Teaching hydrological modeling with a user-friendly catchment-runoff-model software package. Hydrol. Earth Syst. Sci., 16(9), 3315-3325. doi: 10.5194/hess-16-3315-2012.

Mendez, M. and Calvo-Valverde, L.  2016.  Development of the HBV-TEC Hydrological Model. Procedia Engineering, 154, 1116-1123. doi: https://doi.org/10.1016/j.proeng.2016.07.521.

AghaKouchak A., Habib E., 2010, Application of a Conceptual Hydrologic
Model in Teaching Hydrologic Processes, International Journal of Engineering Education, 26(4), 963-973. 

AghaKouchak A., Nakhjiri N., and Habib E., 2012, An educational model for ensemble streamflow simulation and uncertainty analysis, Hydrology and Earth System Sciences Discussions, 9, 7297-7315, doi:10.5194/hessd-9-7297-2012.
