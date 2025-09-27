from scipy import integrate

# Take f(x) function as f
f = lambda x : x**2

#Single integration with a = 0 & b = 1
integration = integrate.quad(f, 0 , 1)

#Print content of integration
print("integration:{}".format(integration))
