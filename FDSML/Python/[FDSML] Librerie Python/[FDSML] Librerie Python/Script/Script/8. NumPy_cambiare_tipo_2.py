import numpy as np

#Define simple 2d list in Python
list2 = [[0,1,2],[3,4,5],[6,7,8]]

#Convert integer list2 in NumPy array of float items
arr_2f = np.array(list2, dtype='float')

#Print content of arr_2f
print ("arr_2f content: {}".format(arr_2f))

#Print arr_2f shape and type
print ("arr_2f shape : {}".format(arr_2f.shape))
print ("arr_2f type: {}",format(arr_2f.dtype))
