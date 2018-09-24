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
ax = plt.gca()

balance_subset = balance[:1000]
income_subset = income[:1000]
student_subset = student[:1000]

y_subset = y[:1000]

ax.scatter(balance_subset[y_subset == False], income_subset[y_subset == False], student_subset[y_subset == False], s=15, marker='o')

ax.scatter(balance_subset[y_subset == True], income_subset[y_subset == True], student_subset[y_subset == True], s=40, marker='+')

