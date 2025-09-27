import numpy as np

#Create 2d NumPy array af all ones
arr_ones = np.ones(shape=(2,2),dtype=np.int8,order='C')

#Print content of arr_ones
print ("arr_ones content: {}".format(arr_ones))

#Print arr_ones shape and type
print ("arr_ones shape: {}".format(arr_ones.shape))
print ("arr_ones type: {}".format(arr_ones.dtype))
