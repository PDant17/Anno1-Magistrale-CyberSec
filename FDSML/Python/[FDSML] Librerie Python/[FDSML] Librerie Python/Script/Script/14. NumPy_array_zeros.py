import numpy as np

#Create 2d NumPy array af all zeros
arr_zeros = np.zeros(shape=(2,2),dtype=np.int8,order='C')

#Print content of arr_zeros
print ("arr_zeros content: {}".format(arr_zeros))

#Print arr_zeros shape and type
print ("arr_zeros shape: {}".format(arr_zeros.shape))
print ("arr_zeros type: {}".format(arr_zeros.dtype))

