# Lab 1: Linear Regression (corresponding to lecture handout 1)
import numpy as np

# This function computes the polynomial of order 'order' corresponding to a least-squares fit
# to the data (x, y), where 'y' contains the observed values and 'x' contains the x-ordinate
# of each observed value.
#
# The normal equation is sloved in the function 'linear regression'.
def LS_poly(x, y, order, eps = 0):
    # First build the polynomial design matrix (relies only x-ordinates, not observed values)
    X = polynomial_design_matrix(x, order);
    # Then find the polynomial using this matrix and the values 'y'.
    w = linear_regression(X, y, eps=eps);
    return w

# Computes the polynomial design matrix.
#
# For a vector 'x', this contains all powers up to 'order'
# of each element of 'x'.  This kind of matrix is also called
# a Vandermonde matrix.
#
# The numpy array 'x' contains the x-ordinates (x-axis
# values) which we are analyzing.
def polynomial_design_matrix(x, order=1):
    # Create a matrix of zeros, with 'length-of-x' rows and 'order+1' cols
    X = np.zeros(shape=(x.size,order+1))

    # EXERCISE 1: fill the body of this function.
    # See slide 23 of the lecture 1 handout.
    # The exponentiation (power) operator in Python is '**'.
    # Assign to the element (row,col) of a numpy matrix with: M[r,c] = <expression>

    # Hint:
    # Outer loop: iterating over columns; each column gets a higher power
    # for p in range(0, order+1):
    # Inner loop: iterating over rows: each row corresponds to an element of 'x'
    # for i in range(x.size):
    # Element (i,p) of X should be the ith element of 'x' to the power p:
    #X[i,p] = <something>
    
    for p in range (0, order+1):
        for i in range (0, x.size):
            X[i,p] = 1*(x[i]**p)
#            if i < 3:
#              print ("i: ", i)
#              print ("x[i]: ", x[i])
#              print ("p: ", p)
#              print ("X[i,p]: ", X[i,p])
#    print(X)
    return X


# Given values 'y' and the polynomial design matrix for the x-ordinates of those
# values in 'X', find the polynomial having the best fit:
#
# theta = ((X'X + I)^(-1))*X'y
#
# This uses numpy to solve the normal equation (see slide 16 of handout 1)
def linear_regression(X, y, eps=0):
#    order = X.shape[1] - 1;
#    print ("X.shape[1]: ", X.shape[1])
#    print ("Order: ", order)
    M = np.dot(X.transpose(), X)
#    print ("M: ", M)
    # EXERCISE 2: implement Tikhonov regularisation.
    # See lecture handout 1, slide 35.
    # print("Eps: " + str(eps))
    #
    # <add 'eps' times the identity matrix to M>
    # Hints:
    # There is a function 'identity' in numpy to generate an identity matrix
    # The 'identity' function takes an integer parameter: the size of the (square) identity matrix
    # The shape of a numpy matrix 'A' is accessed with 'A.shape' (no parentheses); this is a tuple
    # The number of rows in a matrix 'A' is then 'A.shape[0]' (or 'len(A)')
    # You can add matrices with '+' -- so you will update 'M' with 'M = M + <amount> * <identity>'
    # Note that the amount of regularization is denoted 'alpha' in the slides but here it's 'eps'.
#    print("Eps: " + str(eps))
    I = np.identity(M.shape[0])
#    print("I: ", I)
    M = M + (eps*I)
#    print("M + (eps*I): ", M)
#    print("inv(M): ", np.linalg.inv(M))
    theta = np.dot(np.linalg.inv(M), np.dot(X.transpose(), y))
    return theta;

# EXERCISE 3: implement computation of mean squared error between two vectors
def mean_squared_error(y1, y2):
    # You can use '-' to compute the elementwise difference of numpy vectors (i.e. y1 - y2).
    # You can use '**' for elementwise exponentiation of a numpy vector.
    # You can use the numpy function 'mean' to compute the mean of a vector.
#    mse = (np.mean(y1) - np.mean(y2))**2
#    mse = (1/len(y1))*sum((y1-y2)**2)
#    mse = np.mean((y1-y2)**2)
#    mse = sum((y1- y2)**2)
    mse = np.mean((y1-y2)**2)
    return mse # replace this with your answer.

# EXERCISE 4: return the number of the best order for the supplied
# data (see the notebook).
def question_4(y, yh, X):
    SSR = sum((y-yh)**2)
    SST = sum((y-np.mean(y))**2)
    r_sq = 1 - (float(SSR))/SST
    a_r_sq = 1 - (1-r_sq)*(len(y)-1)/(len(y)-X.shape[1]-1)
    print ("R^2: ", r_sq)
    print ("A_R^2: ", a_r_sq)
    return abs(r_sq - a_r_sq), r_sq   # replace '0' with your answer.
#Answer is 3


####
def find_optimal(r2, adj_r2, mse, order):
  #score = (position in r2 + pos in adj_r2 + pos in mse + order(+1)) / terms (i.e.4) # May not need division
  #r2 score corresponding to order
  for i in range (r2.shape[0]):
    if (r2[i,1]) == order:
      r2_pos = i
      break
  #adj r2 score corresponding to order
  for i in range (adj_r2.shape[0]):
    if (adj_r2[i,1] == order):
      adj_r2_pos = i
      break
  #mse score corresponding to order
  for i in range (mse.shape[0]):
    if (mse[i, 1]) == order:
      mse_pos = i
      break
  score = (r2_pos + adj_r2_pos + 2*mse_pos + (order+1)**2)
  return score