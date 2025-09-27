from matplotlib import pyplot as plt

x = [5,8,10]
y = [12,16,6]


#Use plot() function with two vector defined above
plt.plot(x,y)

#Definition of label for Title
plt.title('Epic Info')

#Definition of label for y axis
plt.ylabel('Y axis')

#Definition of label for x axis
plt.xlabel('X axis')

#Showing what we plotted
plt.show()
