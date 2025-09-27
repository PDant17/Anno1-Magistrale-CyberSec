import pandas as pd

#Definition of serie of floats
serie_1 = pd.Series([1., 2., 3.])

#Print content of serie_1 with index
print ("serie_1:")
print (serie_1)

#Definition of serie of floats
serie_2 = pd.Series([1., 2., 3.], index=['a', 'b', 'c'])

#Print content of serie_2
print("serie_2:")
print(serie_2)