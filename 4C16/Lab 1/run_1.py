#Code for running 4C16 Lab 1
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
x=np.arange(-50, 50, 1)
y=(5*x**3 + 2*x**2 + 3*x + 4)
#x = my_data[0,:]
#y = my_data[1,:]
min_order=1
max_order=50
min_alpha=0.00
max_alpha=0.00
mse_ar = []
ord_ar = []
r_ar = []
r2_ar = []
y_ar = []
t_ar = []
alpha=np.arange(min_alpha, max_alpha, 0.001)
if len(alpha) == 0 or min_alpha == max_alpha:
  alpha=np.arange(min_alpha, 1)
max_r = None
min_mse = None
for order in range (min_order, max_order+1):
  design_matrix = ex_1.polynomial_design_matrix(x, order)
  for a in range (len(alpha)):
    theta = ex_1.linear_regression(design_matrix, y, alpha[a])
  #  print("Theta: ", theta)
    y2 = np.zeros(shape=(y.size))
    #y = c + mx
    #y = c + bx + ax2
    #y = d + cx + bx2 + ax3
    #print("y1: ", y1)
#    for i in range (0, x.shape[0]):
#      for j in range (0, theta.shape[0]):
#        if j == 0:
#          y2[i] = theta[j]
#        else:
#          y2[i]+=(x[i]**j)*(theta[j])
    for i in range (0, design_matrix.shape[0]):
      for j in range (0, design_matrix.shape[1]):
        y2[i] += design_matrix[i,j] * theta[j]
    print("Order: ", order)
  #  print("Alpha: ", alpha)
  #  mpl.pyplot.plot(x, y2)
  #  print ("y2: ", y2)
  #  mpl.pyplot.plot(x, y2)
    
    mse = ex_1.mean_squared_error(y, y2)
    t_r, r2 = ex_1.question_4(y, y2, design_matrix)
    print("Mean Squared Error: ", mse)
    print("R ratio: ", t_r)
#    if max_r is None or t_r > max_r:
#    if min_mse is None or mse < min_mse:
    min_mse = mse
    a_r = t_r
    max_r = r2
    min_aplha = alpha[a]
    min_ord = order
    min_y = y2
    min_theta = theta
#  if abs(theta[0]/theta[theta.shape[0]-1]) > 100: break
  r_ar.append(a_r)
  r2_ar.append(max_r)
  mse_ar.append(min_mse)
  ord_ar.append(order)
  y_ar.append(min_y)
  t_ar.append(theta)
  
#srt = sorted(zip(r2_ar, r_ar, ord_ar, mse_ar, y_ar, t_ar), reverse=True)
#r2_ar, r_ar, ord_ar, mse_ar, y_ar, t_ar = list(zip(*srt))
r2_ar = sorted(zip(r2_ar, ord_ar), reverse=True)
r_ar = sorted(zip(r_ar, ord_ar))
mse_ar = sorted(zip(mse_ar, ord_ar))
score = np.zeros(shape=(len(ord_ar), 2))
for i in range (len(ord_ar)): 
  score[i,0] = ex_1.find_optimal(np.asarray(r2_ar), np.asarray(r_ar), np.asarray(mse_ar), ord_ar[i])
  score[i,1] = ord_ar[i]
score = score[score[:,0].argsort()]
print("\n\nBest order: ", int(score[0,1]))
print("Mean Squared Error: ", score[0,0])
#print("Adjusted R^2: ", max_r)

mpl.pyplot.figure()
mpl.pyplot.scatter(x, y)
mpl.pyplot.plot(x, y_ar[0], 'r')
#mpl.pyplot.scatter(x, y_ar[1])
#mpl.pyplot.scatter(x, y_ar[2])
#mpl.pyplot.plot(x, y)
#mpl.pyplot.plot(x, y_ar[0])
mpl.pyplot.show()