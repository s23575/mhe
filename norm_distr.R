# Create a sequence of numbers between A and B incrementing by C.
x <- seq(0, 5, by = 1)

# Choose the mean as B and standard deviation as C.
y <- dnorm(x, mean = -16000, sd = 13162)

plot(x,y)
