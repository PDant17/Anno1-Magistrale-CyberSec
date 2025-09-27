languages = set()

languages ={'Python','R','SAS','Julia'}

print(type(languages), languages)
# remove an element
languages.remove('AI')
print(languages)

""" as opposed to remove, discard will not throw an error when discarding the already removed element AI """
languages.discard('AI')
print(languages)

# pop will remove a random item from set
print('Removed:', (languages.pop()), 'from', languages)
