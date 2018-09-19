
# coding: utf-8

# In[1]:


import numpy as np
import matplotlib.pyplot as plt
import importlib
get_ipython().run_line_magic('matplotlib', 'inline')


# In[2]:


import my_jupyter


# In[3]:


importlib.reload(my_jupyter)

d = my_jupyter.gen_data()

plt.figure(figsize=(18, 6), facecolor='w', edgecolor='b')
plt.plot(d[0], d[1])

