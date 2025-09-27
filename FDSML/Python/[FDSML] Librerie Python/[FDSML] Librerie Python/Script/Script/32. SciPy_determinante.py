from scipy import linalg
import numpy as np

#Define 2d NumPy array
arr_2d = np.array([ (4,5), (3,2) ])

#Print content of arr_2
print ("arr_2d content: {}".format(arr_2d))

#Pass values to det() function
det = linalg.det(arr_2d)

#Print content of det
print ("matrix determinant: {}".format(det))
