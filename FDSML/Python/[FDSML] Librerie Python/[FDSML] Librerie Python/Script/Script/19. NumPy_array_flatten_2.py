import numpy as np

#Create 2d NumPy array
arr_2d = np.array([(1,2,3), (4,5,6)])

arr_1d = arr_2d.flatten()

#Print content of arr_1d
print ("arr_1d content: {}".format(arr_1d))

#Print arr_1d shape and type
print ("arr_1d shape: {}".format(arr_1d.shape))
print ("arr_1d type: {}".format(arr_1d.dtype))
