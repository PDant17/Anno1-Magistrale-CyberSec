import numpy as np

#Define simple list in Python
list = [0,1,2,3,4]

#Convert list in NumPy array
arr = np.array(list)

#Add 4 to all the arr items
arr = arr + 4

#Subtract 2 to all the items in arr
arr = arr - 2

#Print arr after subtraction operation
print ("arr content after subtraction operation (-2): {}".format(arr))

#Multiply 4 to all the arr items
arr = arr * 4

#Print arr after multiplication operation
print ("arr content after multiplication operation (*4): {}".format(arr))

#Divide by 2 all the arr items
arr = arr / 2

#Print arr after division operation
print ("arr content after division operation (/2): {}".format(arr))
