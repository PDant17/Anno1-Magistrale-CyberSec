""" The **kwargs will give you the ability to handle named or keyword arguments keyword that you have not defined in advance"""
# Simple function to loop through arguments 
def sample_function(**kwargs):
    for a in kwargs:
	    print(a, kwargs[a]) 

# Call the function
sample_function(name='John',age=27)
