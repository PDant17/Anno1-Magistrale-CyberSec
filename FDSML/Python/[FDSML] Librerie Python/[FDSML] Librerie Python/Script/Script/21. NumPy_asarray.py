import numpy as np

#Create matrix of all ones
A = np.matrix(np.ones((4,4)))

#Print content of A
print ("A content: {}".format(A))

#The change is made on the third line because the indexing starts at 0
np.asarray(A)[2] = 2

#Print content A after the change
print("A content after the change: {}".format(A))
