#!/usr/bin/env R

library(ggplot2)

#options(device="png")

cycles <- read.csv("cycles.txt", sep="")

ggplot(cycles, aes(x=cycles, colour=method)) + geom_density() + facet_grid(compiler~.) + theme_bw() + scale_x_continuous(limits=c(0, 12500)) + xlab("clock cycles ellapsed, n=10000")
ggsave("timings.png")

sink(file = "summaries.txt")

print("icc new")
summary(cycles[cycles$compiler == "icc" & cycles$method == "new",])
print("icc method")
summary(cycles[cycles$compiler == "icc" & cycles$method == "malloc",])

t.test(cycles[cycles$compiler == "icc" & cycles$method == "new", "cycles"],
	   cycles[cycles$compiler == "icc" & cycles$method == "malloc", "cycles"])
