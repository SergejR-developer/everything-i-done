library(data.table)
library(ggplot2)

wage <- function(age) {
  (65 - age)
}

investments <- function(age) {
  .1 * (1 + .124/12) ^ (age * 12)
}

retirement <- function(retirementAge, age) {
  .1 * (1 + .124/12) ^ (retirementAge * 12) - .1 * (1 + .07/12) ^ (age * 12)
}

difference <- function(age) {
  wage(age) - investments(age)
}

root <- uniroot(difference, c(18, 65))$root
ceil_root <- ceiling(root)

age <- c(18:65)

df <- data.frame(age = age,
                 wage = sapply(age, wage),
                 investments = sapply(age, investments))

retirement_col <- sapply(ceil_root, retirement, age = ceil_root:65)

df$retirement <- c(rep(NA, nrow(df) - length(retirement_col)), retirement_col)

long_df <- df |> data.table() |> melt('age') |>  dplyr::filter(!is.na(value))

ggplot(long_df, mapping = aes(x = age, y = value, col = variable)) + 
  
  geom_line() +
  
  geom_vline(aes(xintercept = root)) +
  
  theme(axis.text.y = element_blank(),
        axis.ticks.y = element_blank())

print(root)