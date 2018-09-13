#Code for running 4C16 Lab 1
#F=open("data_1.txt", "r")
#print(F)
#
#print(F.readline())
#print("\n\n\n")
#print(F.readline())
#print("end")
#
#with open("data_1.txt", "r") as f:
#  data = f.readlines()
#  
#for line in data:
#  words = line.split()
#  print(words)

#import csv
#import numpy
#with open("data_1.csv", "r") as f:
#  spamreader = csv.reader(f, delimiter=',')
##  for row in spamreader:
##    print("| ".join(row))
#    
#print(spamreader.line_num)

import numpy as np
import ex_1
import matplotlib as mpl
my_data = np.genfromtxt("data_1.csv", delimiter=',')
#print(my_data)
#print()
#print(np.size(my_data,0))
#print(my_data[0,0])
#print()
#print(np.size(my_data,1))
#print(my_data[1,0])
#print("\n\n")
x = my_data[0,:]
y = my_data[1,:]

mpl.pyplot.plot(x, y)

design_matrix = ex_1.polynomial_design_matrix(x)

theta = (design_matrix, y)