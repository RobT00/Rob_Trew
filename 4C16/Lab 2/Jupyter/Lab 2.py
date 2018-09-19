
# coding: utf-8

# In[ ]:


#
# This notebook is for the exploration of Logistic Regression -- it corresponds to Lecture Handout 2
#


# In[ ]:


# Autoload setup (you don't need to edit this cell); instructions to: 
#   i) enable autoreloading of modules
get_ipython().run_line_magic('load_ext', 'autoreload')
#  ii) import the module 'lab_1' (which will contain your functions) in an autoreloadable way 
get_ipython().run_line_magic('aimport', 'lab_2')
# iii) indicate that we want autoreloading to happen on every evaluation.
get_ipython().run_line_magic('autoreload', '1')


# In[ ]:


##############################################################
#
# 1: import
#
##############################################################

import pandas as pd
import numpy as np

import matplotlib as mpl
import matplotlib.pyplot as plt
plt.style.use('fivethirtyeight')
plt.rcParams['lines.linewidth'] = 1.7

import sklearn.linear_model as skl_lm
from sklearn.metrics import confusion_matrix, classification_report, precision_score

get_ipython().run_line_magic('matplotlib', 'inline')


# In[ ]:


##############################################################
#
# 2. loading the ISLR 'Default' dataset
#
##############################################################

# see https://cran.r-project.org/web/packages/ISLR/ISLR.pdf
#
# This data set contains information on ten thousand customers. 
#
# The aim here is to predict which customers will default on their credit card debt.
#
# The dataset contains 10000 observations on the following 4 variables.
#   * 'default': a No/Yes label indicating whether the customer defaulted on their debt
#   * 'student': a No/Yes label indicating whether the customer is a student
#   * 'balance': the average balance that the customer has remaining on their credit card after making
#                their monthly payment
#   * 'income' : income of customer

df = pd.read_csv('Default.csv')

# we are using here the pandas python package to read the CSV file.
# we can look at the first 10 observations

df.head(10)


# In[ ]:


##############################################################
#
# 3. visualise your data
#
##############################################################

# We need to visualise our data
# let's ignore the categorical features 'student' and the first column
# and focus on the 'balance' and 'income' features

balance = df['balance'].values
income = df['income'].values

# the outcome is of boolean type
y = df['default'].values == 'Yes'

# setting up the matplotlib figure
fig = plt.figure(figsize=(12,5))
ax = plt.gca()

# we are only going to plot a subset of the data
income_subset = income[0:1000];
balance_subset = balance[0:1000];
y_subset = y[0:1000];

# plotting balance vs income for the 'No Default' class
ax.scatter(balance_subset[y_subset == False], income_subset[y_subset == False], s=15, marker='o')

# plotting balance vs income for the 'Default' class
ax.scatter(balance_subset[y_subset == True],  income_subset[y_subset == True],  s=40, marker='+')

ax.set_ylim(ymin=0)
ax.set_ylabel('Income')
ax.set_xlim(xmin=-100)
ax.set_xlabel('Balance')
ax.legend(['No Default', 'Default'])

# after a quick look at the graph, it appears that 
# the most relevant feature is 'balance'


# In[ ]:


# Exercise 1: implement cross-entropy (in the lab_2 module)

w_test = np.array([0.1, 0.3])
X_test = np.array([[1,1], [1,0]])
y_test = np.array([0, 1])
print(lab_2.cross_entropy(w_test, X_test, y_test))

# Should print 0.778703757908 if your function is working.


# In[ ]:


# Exercise 2: implement gradient computation (in the lab_2 module)
w_test = np.array([0.1, 0.3])
X_test = np.array([[1,1], [1,0]])
y_test = np.array([0, 1])
print(lab_2.gradient(w_test, X_test, y_test))
# Expected result: [ 0.06183342  0.29934383]


# In[ ]:


# The gradient descent algorithm as explained in page 26
# the learning_rate refers to the greek letter 'eta'
# The method also returns the vector of loss function
def gradient_descent(w0, X, y, learning_rate, maxit):
    w = w0
    loss = [];
    for i in range(0, maxit):
        if (i % 83 == 0):
            loss_error = lab_2.cross_entropy(w, X, y)
            loss.append(loss_error)
      
        grad = lab_2.gradient(w,X,y);
        w = w - learning_rate * grad;        
        i = i + 1
        
    return w, loss
        


# In[ ]:


#
# Setting up the Model and Design Matrix
#

# in this lab we will look at the following model:
# y = [ w0 + w1 * balance > 0]
#
# and ignore the 'income' feature

n = balance.shape[0]
p = 2

X = np.zeros(shape=(n, p))

# the first feature is 1 (with associated weight w0)
X[:,0] = 1;

# the second feature is the balance values (with associated weight w1)
X[:,1] = balance[:]

# Gradient Descent algorithms are quite sensitive to initial conditions
# and it is often beneficial to rescale the features
# to improve the performance. 
# in our case we note that balance ranges from 0 to about 2500.
# this is much larger in magnitude to the first feature which is simply 1.
# Thus we (arbitrarily) rescale by factor of 1/1000

X[:,1] = X[:,1]/1000;


# In[ ]:


# in the following we are studying the convergence for 3 different learning rates

w0 = [0, 0];
w, loss = gradient_descent(w0, X, y, learning_rate=50, maxit=10000);
print(w)
fig, ax = plt.subplots(1,1, figsize=(12,6))
ax.plot(loss)

w0 = [0, 0];
w, loss = gradient_descent(w0, X, y, learning_rate=30, maxit=10000);
print(w)
fig, ax = plt.subplots(1,1, figsize=(12,6))
ax.plot(loss)

w0 = [0, 0];
w, loss = gradient_descent(w0, X, y, learning_rate=1, maxit=10000);
print(w)
fig, ax = plt.subplots(1,1, figsize=(12,6))
ax.plot(loss)

# Question 3
# What is the best learning rate value out of 50, 30 and 1 ?
# This cell might take a while to evaluate!


# In[ ]:


# A good way to check that if you reached convergence is to check if the gradient is null (or at least very small):
lab_2.gradient(w, X, y)


# In[ ]:


#
# In logistic Regression, we set a parametric model for the likelihood 
# we denote logit = x'w and parametrise the likelihood as
# p(y_i|logit) = 1/(1 + exp(-logit))
#
# We want to verify that this is a correct approximation for our problem
#
# The following function makes an empirical measurement of p(y_i|logit)
# by recording in the dataset the proportion of default=True for 
# a particular logit value (within some small threshold T).
def get_empirical_probability(logit, logits_train, y, T=1):
    
    valid = ((logits_train <= logit + T) * (logits_train >= logit - T));    
    n_defaults = sum(valid[y==True]);
    n_nodefaults = sum(valid[y==False]);
    empirical_proba = n_defaults / (n_defaults + n_nodefaults);
    return empirical_proba
    


# In[ ]:


# testing set
# we predict the probability of default for 100 values of balance

n_test = 100
X_test = np.zeros(shape=(n_test,2))
X_test[0:n_test,0] = 1;
X_test[0:n_test,1] = np.linspace(X[:,1].min(), X[:,1].max(), num=n_test)

p_test = lab_2.predict(w, X_test)

# we compute the logit values and their corresponding empirical probabilities of default
logits_test = lab_2.logit(w, X_test)
logits_train = lab_2.logit(w, X)
p_empirical = [get_empirical_probability(logit, logits_train, y) for logit in logits_test ];

# plot the graphs
fig, ax = plt.subplots(1,1, figsize=(12,6))

ax.scatter(X[y==False,1], y[y==False], alpha= 0.2)
ax.scatter(X[y==True,1], y[y==True], alpha= 0.2)
ax.plot(X_test[:,1], p_test, color='black')
ax.plot(X_test[:,1], p_empirical, ':', color='gray')

ax.set_ylabel('Probability of default');
ax.set_xlabel('Balance');
ax.set_yticks([0, 0.25, 0.5, 0.75, 1.]);
ax.legend(['logistic model for probability of default',
           'empirically measured probability of default', 
           'No Default', 'Default'],  prop={'size': 16})


# In[ ]:


# At this point, we still don't have a classifier. 
# All we need is to set a threshold on the predicted probabilities
# Write a function 'predict_class' in the module to give
# the predicted class for observations X and weights w.

# Use that function here to assess the accuracy of the classifier
# for different thresholds.

# Accuracy = percentage correctly classified.
def accuracy(w, X, y, threshold):
    return np.mean(y == lab_2.predict_class(w, X, threshold))

w = np.array([-10.63971053,   5.49188453])   # These are good weights!
print(accuracy(w, X, y, 0.25))
print(accuracy(w, X, y, 0.5))
print(accuracy(w, X, y, 0.75))
print(accuracy(w, X, y, 0.95))

# Update your module function 'question_5' to report the accuracy for a threshold of 0.5.

