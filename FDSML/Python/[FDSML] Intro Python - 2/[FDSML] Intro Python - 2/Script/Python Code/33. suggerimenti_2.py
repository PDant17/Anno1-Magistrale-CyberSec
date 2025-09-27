# Below code will open a file 
fName='vechicles.txt'

try: 
   
    with open(fName, 'r') as f:
        print(f.readline())

except IOError as e:
   print('IO Error')
   
finally:
   print('File has been closed')
