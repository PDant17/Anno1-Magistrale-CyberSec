import numpy as np

#Define simple list in Python
list = [0,1,2,3,4]

#Convert list in NumPy array
arr = np.array(list)

#Print content of arr
print ("arr content: {}".format(arr))

#Add 4 to all the arr items
arr = arr + 4

#Print arr after sum operation
print ("arr content after add operation (+4): {}".format(arr))
