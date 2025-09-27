import numpy as np

#Generate random number from normal distribution
normal_array = np.random.normal(5, 0.5, 10)

#Print content of normal_array
print ("normal_array content: {}".format(normal_array))

#Min
print("normal_array min: {}".format(np.min(normal_array)))

#Max
print("normal_array max: {}".format(np.max(normal_array)))