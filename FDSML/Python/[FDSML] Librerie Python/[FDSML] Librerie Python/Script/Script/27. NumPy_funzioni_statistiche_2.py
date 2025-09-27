import numpy as np

#Generate random number from normal distribution
normal_array = np.random.normal(5, 0.5, 10)
#Mean
print("normal_array mean: {}".format(np.mean(normal_array)))

#Median
print("normal_array median: {}".format(np.median(normal_array)))

#Standard deviation
print("normal_array standard deviation: {}".format(np.std(normal_array)))
