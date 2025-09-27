import numpy as np

#Create two 2d NumPy array
arr_1 = np.array([1,2,3])
arr_2 = np.array([4,5,6])

#Print content of arr_1
print ("arr_1 content: {}".format(arr_1))

#Print arr_1 shape and type
print ("arr_1 shape: {}".format(arr_1.shape))
print ("arr_1 type: {}".format(arr_1.dtype))

#Print content of arr_2
print ("arr_2 content: {}".format(arr_2))

#Print arr_2 shape and type
print ("arr_2 shape: {}".format(arr_2.shape))
print ("arr_2 type: {}".format(arr_2.dtype))

happ = np.hstack((arr_1,arr_2))
print ("Horizontal Append: {}".format(happ))

vapp = np.vstack((arr_1,arr_2))
print ("Vertical Append: {}".format(vapp))
