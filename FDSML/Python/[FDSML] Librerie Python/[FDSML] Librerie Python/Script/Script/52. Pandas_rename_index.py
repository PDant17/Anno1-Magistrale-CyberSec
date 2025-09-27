import numpy as np
import pandas as pd

#Define first Data Frame
df1 = pd.DataFrame({'name': ['John', 'Smith','Paul'],'Age': ['25', '30', '50']},index=[0, 1, 2])

#Define second Data Frame
#Print content of df1
print("Data Frame 1:")
print(df1)
df2 = pd.DataFrame({'name': ['Adam', 'Smith' ],'Age': ['26', '11']},index=[3, 4])

#Print content of df2
print("Data Frame 2:")
print(df2)
df_concat = pd.concat([df1,df2])

#Print content of df_concat
print("Data Frame concat:")
print(df_concat)

#Rename Data Frame
df_concat_rename = df_concat.rename(columns={"name": "Surname", "Age": "Age_ppl"})

#Print content of df_concat_remane
print("Data Frame after remane: ")
print(df_concat_rename)
