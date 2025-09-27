import numpy as np

#Create array with numpy.linspace() of 10 elements
arr = np.linspace(1.0, 5.0, num=10)

#Print content of arr
print ("arr content: {}".format(arr))

#Create array with numpy.linspace() of 5 with endpoint=False
arr_1 = np.linspace(1.0, 5.0, num=5, endpoint=False)

# Print content of arr_1
print ("arr_1 content: {}".format(arr_1))
