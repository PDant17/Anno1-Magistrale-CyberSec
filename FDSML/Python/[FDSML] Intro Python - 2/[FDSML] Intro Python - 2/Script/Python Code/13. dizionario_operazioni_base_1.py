dict={'Name':'Jivin','Age':6,'Class':'First'}
print('length of dict: ', len(dict))
print('Equivalent string: ', str(dict))


#Create a new dictionary with keys from tuple
tuple=('name','age','sex')
dict= dict.fromkeys(tuple)
print('New Dictionary: ', str(dict))

dict['name']='Jivin'
dict['age']= 7
dict['sex']='M'
print('New Dictionary: ', str(dict))

dict= dict.fromkeys(tuple,10)
print('New Dictionary: ', str(dict))
