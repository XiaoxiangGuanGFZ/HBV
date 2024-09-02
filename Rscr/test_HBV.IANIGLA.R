
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
