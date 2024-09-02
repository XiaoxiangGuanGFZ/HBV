
library(tidyverse)
library(HBV.IANIGLA)
data("lumped_hbv")
head(lumped_hbv)
dim(lumped_hbv)
view(lumped_hbv)

lumped_hbv_df <- lumped_hbv %>% mutate(
  date = as.Date(Date)
) %>% mutate(
  y = year(date),
  m = month(date),
  d = day(date)
)

write.table(
  lumped_hbv_df[, c(7:9, 2:5)],
  file = "D:/HBV/data/example_data.csv",
  col.names = T, row.names = F, append = F, sep = ",", quote = F
)

# ------------ HBV simulation -----------

snow_module <-
  SnowGlacier_HBV(model = 1,
                  inputData = as.matrix( lumped_hbv[ , c(2, 3)] ),
                  initCond = c(20, 2),
                  param = c(1.20, 1.00, 0.00, 2.5) )

soil_module <-
  Soil_HBV(model = 1,
           inputData = cbind(snow_module[ , "Total"], lumped_hbv[ , "PET(mm/d)"]),
           initCond = c(100, 1),
           param = c(200, 0.8, 1.15) )

routing_module <-
  Routing_HBV(model = 1,
              lake = F,
              inputData = as.matrix(soil_module[ , "Rech"]),
              initCond = c(0, 0, 0),
              param = c(0.9, 0.01, 0.001, 0.5, 0.01) )

tf_module <-
  round(
    UH(model = 1,
       Qg = routing_module[ , "Qg"],
       param = c(1.5) ),
    2)


library(ggplot2)
ggplot(data = data.frame(date = lumped_hbv[ , "Date"],
                         qsim = tf_module,
                         qobs = lumped_hbv[ , "qout(mm/d)"]),
       aes(x = date)) +
  geom_line(aes(y = qsim), col = "dodgerblue") +
  geom_line(aes(y = qobs), col = "red") +
  xlab(label = " ") + ylab(label = "q(mm/d)") +
  theme_minimal() +
  scale_x_date(date_breaks = "1 year") +
  scale_y_continuous(breaks = seq(0, 15, 2.5)) +
  theme(
    title = element_text(color = "black", size = 12, face = "bold"),
    axis.title.x = element_text(color = "black", size = 12, face = "bold"),
    axis.title.y = element_text(color = "black", size = 12, face = "bold"),
    legend.text = element_text(size = 11),
    axis.text = element_text(size = 11),
    axis.text.x = element_text(angle = 90) )
