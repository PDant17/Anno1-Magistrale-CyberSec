""" The *args will provide all function parameters in the form of a tuple"""
# Simple function to loop through arguments 
def sample_function(*args):
    for a in args:
	    print(a) 

# Call the function
sample_function(1,2,3)
