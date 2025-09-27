import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
from matplotlib import style
style.use('ggplot')

#Define Data Frame
df2 = pd.DataFrame(np.random.rand(10,4), columns=['a', 'b', 'c', 'd'])

#Plot Data Frame
df2.plot(kind='bar')
plt.show()
