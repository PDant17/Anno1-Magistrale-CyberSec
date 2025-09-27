# A class representing a student
class student:
  
    def __init__(self, name, age):
        self.__doc__ = "A class representing a student"

        self.name = name
        self.age = age
        

    def get_age(self):
    	return self.age
    
    


f = student( "Bob Smith" , 21 )

print("Documentazione: ",f.__doc__,"\n")

print("Classe: ",f.__class__,"\n")

