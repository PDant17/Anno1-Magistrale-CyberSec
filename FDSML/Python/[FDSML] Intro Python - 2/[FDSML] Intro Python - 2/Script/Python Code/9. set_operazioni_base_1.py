languages ={'Python','R','SAS','Julia'}

# Return a shallow copy of a set
lang = languages.copy()
print('Languages : ', languages)
print('Lang : ', lang)

# Add an element in languages
languages.add('Java')
print('Languages : ', languages)
print('Lang : ', lang)
l=languages

# Add an element in l
l.add('C')
print('Languages : ', languages)
print('L : ', l)
