# Example code
tuple =('a','b','c','d',1,2,3)
print('Length of Tuple: ', len(tuple),"\n")

tuple_concat = tuple + (7,8,9)
print('Concatenate tuples: ', tuple_concat,"\n")
print('Repetition: ', (1,'a',2,'b') * 3,"\n")
print('Membership check: ', 3 in (1,2,3),"\n")
print('Iteration: ',"\n")

for x in (1,2,3): print(x)


# Negative sign will retrieve item from right
print('slicing: ', tuple_concat[-2])
print('slicing range: ', tuple_concat[2:])
# Max and Min
print('Max of the tuple:', max((1,2,3,4,5,6,7,8,9,10)))
print('Min of the tuple:', min((1,2,3,4,5,6,7,8,9,10)))
