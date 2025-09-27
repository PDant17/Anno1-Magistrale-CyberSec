from matplotlib import pyplot as plt
from matplotlib import style
style.use('ggplot')

#Define first two vectors of points
x = [5,8,10]
y = [12,16,6]

#Define second two vectors of points
x2 = [6,9,11]
y2 = [6,15,7]

#Define first line with color green and label 'line one'
plt.plot(x,y,'g',label='line one', linewidth=5)

#Define second line with color celestial and label 'line two'
plt.plot(x2,y2,'c',label='line two',linewidth=5)

#Define of label for Title
plt.title('Epic Info')

#Define of label for y axis
plt.ylabel('Y axis')

#Define of label for x axis
plt.xlabel('X axis')

#Insert legend
plt.legend()

#Define grid with color specified by 'k'
plt.grid(True,color='k')
plt.show()
