languages = set()

languages ={'Python','R','SAS','Julia'}

# Accessing set elements
print(type(languages), languages)
print(list(languages)[0])
print(list(languages)[0:3])

print(type(languages), languages)
# add an element
languages.add('C')
print(languages)
languages.update(['Java','SPSS']) # add multiple elements
print(languages)
# add list and set
languages.update(['Ruby','C++'],{'Data Science','AI'})
print(languages)
