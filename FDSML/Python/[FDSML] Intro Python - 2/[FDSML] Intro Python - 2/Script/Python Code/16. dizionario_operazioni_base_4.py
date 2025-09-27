dict={'Name':'Jivin','Age':6,'Class':'First'}

""" if key does not exists, then the arguments will be added to dict and returned"""
print('Value for Age: ', dict.setdefault('Age', None))
print('Value for Sex: ', dict.setdefault('Sex', 'M'))

# Concatenate dictionaries
dict={'Name':'Jivin','Age':6}
dict2={'Sex':'M'}
dict.update(dict2)
print('Concatenated dicts: ', dict)
