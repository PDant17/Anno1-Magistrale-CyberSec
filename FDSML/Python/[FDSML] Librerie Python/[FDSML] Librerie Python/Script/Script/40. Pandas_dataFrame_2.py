import numpy as np
import pandas as pd

#Define 2d NumPy array
arr_2d = [(1,2),(3,4)]

#Convert 2d Numpy array to pandas Data frame
df_arr_2d = pd.DataFrame(arr_2d)

#Convert pandas Data frame to 2d Numpy array
arr = np.array(df_arr_2d)

#Print content of arr
print("Numpy array:")
print(arr)

#Define dictionary dic
dic = {'Name': ["John", "Smith"], 'Age': [30, 40]}

#Convert dictionary to pandas Data Frame
df_dic= pd.DataFrame(dic)

#Print content of df_dic
print("Data Frame with dictionary:")
print(df_dic)
