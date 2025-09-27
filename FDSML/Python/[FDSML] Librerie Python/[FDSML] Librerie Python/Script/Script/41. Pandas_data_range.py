import pandas as pd

#Create date using pandas.data_range()
dates_d = pd.date_range('20300101', periods=6, freq='D')

#Print content of dates_d
print('Day:', dates_d)
