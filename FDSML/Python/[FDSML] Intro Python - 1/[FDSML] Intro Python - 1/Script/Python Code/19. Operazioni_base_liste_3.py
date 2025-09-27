# Example code 
print("Count number of 1: ", [1,1,2,3,4,5].count(1)) 

list_1 = [ 'Statistics','Programming',2015,2017,2018] 
list_2 =['a','b',1,2,3,4,5,6,7] 

list_1.extend(list_2, "\n")

print("Extended: ", list_1, "\n") 

print("Index for : ", list_1.index("Programming"), "\n") 

print(list_1, "\n") 

print("pop last item in list: ", list_1.pop(), "\n") 

print("pop the item with index 2: ", list_1.pop(2), "\n")