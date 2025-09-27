import numpy as np

#Create 2d NumPy array
arr_2d = np.array([(1,2,3), (4,5,6)])

#Print content of arr_2d
print ("arr_2d content: {}".format(arr_2d))

#Print first row of arr_2d
print ("first row of arr_2d: {}".format(arr_2d[0]))

#Print second row of arr_2d
print ("second row of arr_2d: {}".format(arr_2d[1]))

#Print first column of arr_2d
print ("first column of arr_2d: {}".format(arr_2d[:,0]))

#Print second column of arr_2d
print ("second column of arr_2d: {}".format(arr_2d[:,1]))

#Print third column of arr_2d
print ("third column of arr_2d: {}".format(arr_2d[:,2]))

#Print first two elements of the second row of arr_2d
print ("first two elements of arr_2d: {}".format(arr_2d[1,:2]))
