A = {2,1,3,4,5}
B = {4,5,6,7,8} 

#Binary operations
print(A.isdisjoint(B)) #True for non intersecting sets
print(A.issubset(B))
print(A.issuperset(B))

#Unary operations
print('Sorting: ', sorted(A)) #Return a new sorted list
print('Sum: ', sum(A)) #Return the sum of all items


print('length: ', len(A))
print('Min: ', min(A))
print('Max: ', max(A))
