tuple_1 = ()
tuple_2 = (1,) 
tuple_3 =('a','b','c','d',1,2,3)


# Accessing items in tuple
print('3rd item of Tuple: ', tuple_3[2],"\n")
print('First 2 items of Tuple: ', tuple_3[0:2],"\n")


# Deleting tuple
print('Same tuple : ', tuple_3,"\n")
del tuple_3
print(tuple_3,"\n") # Will throw an error message
