from scipy import integrate

#Import square root function from math lib
from math import sqrt

# set  function f(x)
f = lambda x, y : 64 *x*y

# Lower limit of second integral
p = lambda x : 0

# Upper limit of first integral
q = lambda y : sqrt(1 - 2*y**2)

# Perform double integration
integration = integrate.dblquad(f , 0 , 2/4,  p, q)

#Print content of integration
print("integration: {}".format(integration))
