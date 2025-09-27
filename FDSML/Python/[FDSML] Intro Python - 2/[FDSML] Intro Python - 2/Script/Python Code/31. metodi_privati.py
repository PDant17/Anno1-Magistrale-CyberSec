# A class representing a student
class student:
  
    def __init__(self, name, age):
        self.__doc__ = "A class representing a student"

        self.name = name
        self.age = age
        

    def __get_age(self):
        print("Metodo Privato")
    	
        return self.age