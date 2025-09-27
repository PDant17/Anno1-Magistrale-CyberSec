import numpy as np

#Create 2d NumPy array
arr_2d = np.array([(1,2,3), (4,5,6)])

arr_2dr = arr_2d.reshape(3,2)

#Print content of arr_2dr
print ("arr_2dr content: {}".format(arr_2dr))

#Print arr_2dr shape and type
print ("arr_2dr shape: {}".format(arr_2dr.shape))
print ("arr_2dr type: {}".format(arr_2dr.dtype))
