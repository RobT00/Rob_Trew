#Code for running 4C16 Lab 2 locally
import lab_2 as lb2
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

#t = np.arange(0, 1, 0.01)
#plt.plot(lb2.sigmoid(t))

df = pd.read_csv('Default.csv')

balance = df['balance'].values
income = df[df.columns[4]].values
student = df[df.columns[2]].values == 'Yes'

y = df[df.columns[1]].values == 'Yes'

fig_1 = plt.figure(figsize=(12, 5))
#ax = plt.gca()

balance_subset = balance[:1000]
income_subset = income[:1000]
student_subset = student[:1000]

y_subset = y[:1000]

#ax.scatter(balance_subset[y_subset == False], income_subset[y_subset == False], student_subset[y_subset == False], s=15, marker='o')

#ax.scatter(balance_subset[y_subset == True], income_subset[y_subset == True], student_subset[y_subset == True], s=40, marker='+')

n = balance.shape[0]
p = 2

X = np.zeros(shape=(n, p))
X[:,0] = 1;
X[:,1] = balance[:]
X[:,1] = X[:,1]/1000;

w = np.array([-10.63971053,   5.49188453]) 

pd = lb2.predict(w, X)

def accuracy(w, X, y, threshold):
#    return np.mean(y == lb2.predict_class(w, X, threshold))
    pred = lb2.predict_class(w, X, threshold)
    scr1 = 0
    n = X.shape[0]
    for i in range (0, n):
        if pred[i] == y[i]:
            scr1 += 1
    a1 = scr1/n
    y = y.reshape(y.shape[0], 1)
    scr2 = (y == pred)
    a2 = np.mean(scr2)
    if a1 != a2:
        print("Issue with accuracies")
        print("a1: ", a1)
        print("a2: ", a2)
    return a1

pc = lb2.predict_class(w, X, 0.5)
acc = accuracy(w, X, y, 0.5)
print(accuracy(w, X, y, 0.5))