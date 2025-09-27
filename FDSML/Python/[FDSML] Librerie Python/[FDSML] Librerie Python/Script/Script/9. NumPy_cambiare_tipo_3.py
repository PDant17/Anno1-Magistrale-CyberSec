import numpy as np

#Define simple 2d list in Python
list2 = [[0,1,2],[3,4,5],[6,7,8]]

#Convert list2 in NumPy array 2d
arr_2 = np.array(list2)
arr_2f = np.array(list2, dtype='float')

#Change arr_2f items to integer type through use of astype() function
arr_2i=arr_2f.astype('int')

#Print content of arr_2i
print ("arr_2i content: {}".format(arr_2i))

#Print arr_2i shape and type
print ("arr_2i shape : {}".format(arr_2i.shape))
print ("arr_2i type: {}",format(arr_2i.dtype))
