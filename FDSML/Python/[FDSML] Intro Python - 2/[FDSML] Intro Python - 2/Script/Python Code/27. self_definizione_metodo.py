# A class representing a student
class student:
  
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def get_age(self):
    	return self.age
    
    #New
    def set_age(self, num):
        self.age = num


b = student( "Bob" , 21 )
print("Prima: ",b.get_age(),"\n")

b.set_age(3)

print("Dopo: ",b.get_age(),"\n")

