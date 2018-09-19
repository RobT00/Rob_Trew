#
# Lab 0 Exercise 2:
#  Newton Raphson
import math


# find_root: function to find value 'x' such that f(x) == 0
#
# f  == function to find the root of.
#     must takes one float parameter and return one float.
#
# df == a function which evaluates the first derivative of f.
#
# x0 == starting point ('guess') for search for root.
#
# The function should return None if it hits a zero derivative
# or runs for more than 100 iterations.

def n_raphson_fn(x, df, f):
  return (x - (f/df))

def find_root(f, df, x0):
  i = 0
  x = x0
  while True:
    derivative = df(x)
    print (df(x))
#< check if derivative is 0, print a message and return if so >
    if (derivative == 0):
      print ("Derivative is ", derivative)
      return None
#    next_x = < compute using Newton-Raphson formula >
    next_x = n_raphson_fn(x, derivative, f(x))
    print("{} - {}".format(i, x))
#if < insert expression to compute absolute difference of x and next_x > < 0.0001:
    if (abs(x - next_x) < 0.0001):
      return x
#<update x>
    x = next_x
#<increment i>
    i+=1
#if (< replace with expression checking number of iterations >):
    if (i > 100):
      print("Hit max_iterations - abandoning search!")
      return None


# Some functions for testing

def f1(x):
    return(2 - x*x)

def d_f1(x):
    return(-2*x)

def f2(x):
    return (0.75 - 1 / (1 + math.exp(-abs(x))))
    # return((3 - math.exp(-x) / math.sqrt(abs(x))))

def d_f2(x):
    h = 0.1
    return (f2(x+h/2) - f2(x-h/2))/h

def f3(x):
    return(x*x + 4)

def d_f3(x):
    return(2*x)


if __name__ == '__main__':
    print("f1 (2 - x^2): " + str(find_root(f1, d_f1, 12)))
    print()

    print("f2 (0.75 - 1 / (1 + math.exp(-abs(x)))): " + str(find_root(f2, d_f2, 3)))
    print()

    print("f3 (x^2 + 4): " + str(find_root(f3, d_f3, 2)))
    print()
