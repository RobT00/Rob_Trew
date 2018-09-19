import numpy as np
def gen_data():
  # Numpy array, ranging from 0--25 in steps of 0.1:
  x = np.arange(0, 25, 0.1);
  # y as a function of x:
  y = np.sin(x)
  return (x, y)