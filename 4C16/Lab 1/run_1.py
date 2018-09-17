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

min_order=1
max_order=3
min_alpha=0.0
max_alpha=1.0
alpha=np.arange(min_alpha, max_alpha, 0.001)
max_r = None
mpl.pyplot.scatter(x, y)
for order in range (min_order, max_order+1):
  design_matrix = ex_1.polynomial_design_matrix(x, order)
  for a in range (len(alpha)):
    theta = ex_1.linear_regression(design_matrix, y, alpha[a])
  #  print("Theta: ", theta)
    y2 = np.zeros(shape=(y.size))
    #y2 = x * (theta[1] + theta[0])
    #y1 = theta[0] + theta[1]*x
    #y = mx + c
    #y = ax2 + bx + c
    #y = ax3 + bx2 + cx + d
    #OR
    #y = c + mx
    #y = c + bx + ax2
    #y = d + cx + bx2 + ax3
    #print("y1: ", y1)
    for i in range (0, x.shape[0]):
      for j in range (0, theta.shape[0]):
        if j == 0:
          y2[i] = theta[j]
        else:
          y2[i]+=(x[i]**j)*(theta[j])
    print("Order: ", order)
  #  print("Alpha: ", alpha)
  #  mpl.pyplot.plot(x, y2)
  #  print ("y2: ", y2)
  #  mpl.pyplot.plot(x, y2)
    
    mse = ex_1.mean_squared_error(y, y2)
    t_r = ex_1.question_4(y, y2, design_matrix)
#    print("Mean Squared Error: ", mse)
    if max_r is None or t_r > max_r:
      min_mse = mse
      max_r = t_r
      min_aplha = alpha[a]
      min_ord = order
      min_y = y2
      min_theta = theta

print("\n\nBest order: ", min_ord)
print("Mean Squared Error: ", min_mse)
print("Adjusted R^2: ", max_r)
mpl.pyplot.plot(x, min_y)