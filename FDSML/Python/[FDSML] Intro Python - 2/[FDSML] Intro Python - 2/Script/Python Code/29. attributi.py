class counter:
    overall_totale = 0
        #class attribute
    def __init__(self):
        self.my_total = 0
        #data attribute

    def increment(self):
        counter.overall_totale = counter.overall_totale + 1
        self.my_total = self.my_total + 1
        
        


a = counter()
b = counter()

a.increment()

b.increment()
b.increment()

print("a.mytotal: ",a.my_total, "\n")

print("a.__class__.overall_totale: ", a.__class__.overall_totale, "\n")

print("b.mytotal: ",b.my_total, "\n")

print("b.__class__.overall_totale: ", b.__class__.overall_totale, "\n")

