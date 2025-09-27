import pandas as pd

#Define attributes of CSV file
COLUMNS = ['age','workclass', 'fnlwgt', 'education', 'education_num','marital', 'occupation', 'relationship', 'race', 'sex', 'capital_gain', 'capital_loss', 'hours_week', 'native_country', 'label']

#Define path of CSV file
PATH = "https://archive.ics.uci.edu/ml/machine-learning-databases/adult/adult.data"
df_train = pd.read_csv(PATH, skipinitialspace=True, names = COLUMNS, index_col=False)

#Print shape of df_train
print("df_train shape: {} ".format(df_train.shape))
