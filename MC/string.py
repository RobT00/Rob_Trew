# -*- coding: utf-8 -*-

def swap(x, y):
  t = x
  x = y
  y = t

def rev_it(a):
  a = list(a)
  i = 0
  n = len(a)-1
  for i in range(0, int(len(a)/2)):
    tmp = a[i]
    a[i] = a[n]
    a[n] = tmp
    n -= 1
  return ''.join(a)

def rev_rec(a):
  return ("" if a == "" else a[-1] + rev_rec(a[:-1]))
  
a = "racecaR"
print("Original: ", a)
print("Iterative: ", rev_it(a))
print("Original: ", a)
print("Recursive: ", rev_rec(a))
print("Original: ", a)