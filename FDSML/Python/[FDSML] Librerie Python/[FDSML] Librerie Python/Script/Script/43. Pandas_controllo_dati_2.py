import numpy as np
import pandas as pd

#Create date using pandas.data_range()
dates_m = pd.date_range('20300101', periods=6, freq='M')

#Create a random sequence. The sequence has 4 columns and 6 rows
random = np.random.randn(6,4)

# Use dates_m as an index for the data frame
# # Each row will be given a "name" or an index, corresponding to a date.
df = pd.DataFrame(random, index=dates_m,columns=list('ABCD'))

#Print content of df
print("Data Frame:")
print(df)

#Use method describe()
print ("dataset clues:")
print(df.describe())
