from matplotlib import pyplot as plt
from matplotlib import style
style.use('ggplot')

#Define first two vectors of points
x = [5,8,10]
y = [12,16,6]

#Define second two vectors of points
x2 = [6,9,11]
y2 = [6,15,7]

#Plot first scatter
plt.scatter(x, y, color='r')

#Plot second scatter
plt.scatter(x2, y2, color='g')

#Definition of label for Title
plt.title('Epic Info')

#Definition of label for y axis
plt.ylabel('Y axis')

#Definition of label for x axis
plt.xlabel('X axis')
plt.show()