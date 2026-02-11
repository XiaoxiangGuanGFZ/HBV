library(tidyverse)
library(ggplot2)

## ----- soil flux -------

P_FC = 100  ## 50 - 500
P_BETA = 3  ## 1- 6 

x = seq(0,1,0.02)

df <- data.frame(
  x = rep(x, 3),
  y = c(
    x ^ 1,
    x^3, 
    x^5
  ),
  beta = as.character(c(
    rep(1,length(x)),
    rep(3,length(x)),
    rep(5,length(x))
  ))
)


ggplot(data = df) +
  geom_line(
    aes(x = x, y = y, color = beta)
  ) +
  labs(x = NULL, y = NULL, color = NULL) +
  theme_minimal() +
  theme(
    legend.position = c(0.22, 0.75)
  )


## ----- actual evaporation -------

x = seq(0, 1.4, 0.1)
y = ifelse(x < 1, x, 1)

df <- data.frame(
  x , y 
)

ggplot(df) +
  geom_line(
    aes(x, y)
  ) +
  labs(x = NULL, y = NULL, color = NULL) +
  theme_minimal() 
