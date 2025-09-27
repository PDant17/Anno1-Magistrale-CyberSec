from scipy.special import comb

#Find combinations of 5, 2 values using comb(N, k)
com = comb(5, 2, exact = False, repetition=True)

#Print content of com
print("combination value: {}".format(com))
