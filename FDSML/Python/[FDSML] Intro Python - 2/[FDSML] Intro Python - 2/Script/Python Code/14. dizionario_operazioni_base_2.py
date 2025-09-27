dict={'Name':'Jivin','Age':6,'Class':'First'}
#Retrieve a value for a given key
print('Value for Age: ', dict.get('Age'))
print('Value for Sex: ', dict.get('Sex'))

""" Since the key Sex does not exist, the second argument will be returned """
print('Value for Sex: ', dict.get('Sex', 'M'))
