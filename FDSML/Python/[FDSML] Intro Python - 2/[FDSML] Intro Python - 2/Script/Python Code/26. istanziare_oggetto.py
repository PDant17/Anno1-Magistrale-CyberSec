# A class representing a student
class student:
  
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def get_age(self):
    	return self.age


b = student( "Bob" , 21 )
print(b.get_age())

