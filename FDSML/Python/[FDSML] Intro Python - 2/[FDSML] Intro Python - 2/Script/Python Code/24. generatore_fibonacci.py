x=10 # Global Variable

# Simple Fibonacci generator
def fib(n):
    a, b = 0, 1
    
    for i in range(n):
        yield a
        a, b = b, a+b 

# main
print(list(fib(x)))
