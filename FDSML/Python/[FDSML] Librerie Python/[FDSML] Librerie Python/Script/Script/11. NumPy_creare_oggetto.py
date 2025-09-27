import numpy as np

#Create an object array to hold numbers as well as strings
arr_obj = np.array([1, 'a'], dtype='object')

#Print content of arr_obj
print("arr_obj content: {}".format(arr_obj))

#Print arr_obj shape and type
print("arr_obj shape: {}".format(arr_obj.shape))
print("arr_obj type: {}".format(arr_obj.dtype))
