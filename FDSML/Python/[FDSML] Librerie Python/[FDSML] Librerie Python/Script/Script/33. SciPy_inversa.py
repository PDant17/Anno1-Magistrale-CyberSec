from scipy import linalg
import numpy as np

#Define 2d NumPy array
arr_2d = np.array([ [4,5], [3,2] ])

#Print content of arr_2d
print ("arr_2d content: {}".format(arr_2d))

#Pass value to function inv()
inv = linalg.inv( arr_2d )

#Print content of inv
print ("inverse matrix : {}".format(inv))
