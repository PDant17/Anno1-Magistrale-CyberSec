from scipy import linalg
import numpy as np

#Define 2d NumPy array
arr_2d = np.array([[5,4],[6,3]])

#Pass value into function eig()
eg_val, eg_vect = linalg.eig(arr_2d)

#Print content of eg_val
print("eigenvalues: {}".format(eg_val))

#Print content of eg_vect
print("eigenvectors: {}".format(eg_vect))
