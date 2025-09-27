# A class representing a student
class student:
  
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def get_age(self):
    	return self.age


f = student( "Bob" , 21 )

print("Nome: ",f.name,"\n")

print("Dopo: ",f.get_age(),"\n")

