import numpy as np

#Different type
arr1 = np.array([1.1,2.0,3.2])

#Define simple 2d list in Python
list2 = [[5,6,7],[8,9,10]]

#Print arr1 shape and type
print ("arr1 shape : {}".format(arr1.shape))
print ("arr1 type: {}",format(arr1.dtype))

#Convert list 2d in NumPy array
arr_2 = np.array(list2)

#Print content of arr_2
print ("arr_2 content: {}".format(arr_2))

#Print arr_2 shape and type
print ("arr_2 shape: {}".format(arr_2.shape))
print ("arr_2 type: {}".format(arr_2.dtype))
