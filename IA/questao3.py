#!/usr/bin/env python
# coding: utf-8

# In[25]:



pip install sklearn


# In[11]:


import pandas as pd
import numpy as np
import statistics as st
import matplotlib.pyplot as plt
import plotly.express as px
import seaborn as sns
df = pd.read_csv('questao3.csv', delimiter=",")


df.isnull().sum()


# In[12]:


df.drop(['Column1','Column2','Column3','Column4'],axis=1, inplace=True)


# In[13]:


df.duplicated()
df.drop_duplicates(keep = False, inplace = True) 
df


# In[14]:


corr_matrix = df.corr().abs()
corr_matrix.style.background_gradient(cmap = 'coolwarm')


# In[15]:


# Select upper triangle of correlation matrix
upper = corr_matrix.where(np.triu(np.ones(corr_matrix.shape), k=1).astype(np.bool))

# Find features with correlation greater than 0.75
to_drop = [column for column in upper.columns if any(upper[column] > 0.75)]

# Drop features 
df.drop(to_drop, axis=1, inplace=True)


# In[16]:


corr_matrix = df.corr().abs()
corr_matrix.style.background_gradient(cmap = 'coolwarm')


# In[17]:


df


# In[18]:


print(df['status_type'].value_counts())
print(df['status_published'].value_counts())
print(df['num_reactions'].value_counts())
print(df['num_comments'].value_counts())
print(df['num_shares'].value_counts())
print(df['num_wows'].value_counts())
print(df['num_hahas'].value_counts())
print(df['num_sads'].value_counts())
print(df['num_angrys'].value_counts())


# In[19]:


for i in df['status_type']:
    df['status_type'].replace(to_replace = 'photo', value = 0, inplace=True)
    df['status_type'].replace(to_replace = 'video', value = 1, inplace=True)
    df['status_type'].replace(to_replace = 'status', value = 2, inplace=True)
    df['status_type'].replace(to_replace = 'link', value = 3, inplace=True)


# In[20]:


print(df['status_type'].value_counts())


# In[21]:


df.drop(['status_published'], axis=1, inplace=True)
print(df.duplicated().value_counts())
df.drop_duplicates(inplace=True)
print(df)


# In[22]:


df


# In[23]:


#NORMALIZACAO
col = ['status_type', 'num_reactions', 'num_comments', 'num_shares', 'num_wows', 'num_hahas', 'num_sads', 'num_angrys']
df_numeric = df[col]
# Normalize all of the numeric columns
df_normalized = (df_numeric - df_numeric.mean()) / df_numeric.std()
dfbu = df
df_normalized



# In[27]:


from sklearn.decomposition import PCA
pca = PCA(n_components=2)
principalComponents = pca.fit_transform(df_normalized)
principalDf = pd.DataFrame(data = principalComponents
             , columns = ['principal component 1', 'principal component 2'])
principalDf


# In[28]:


df = pd.concat([principalDf, df[['status_id']]], axis = 1)
df


# In[29]:


df.dropna(inplace=True)
df


# In[ ]:





# In[30]:


from sklearn.cluster import AgglomerativeClustering
import numpy as np
clustering = AgglomerativeClustering().fit(df)
AgglomerativeClustering(n_clusters=8, linkage = 'single')
clustering.labels_


# In[31]:


import matplotlib.pyplot as plt
plt.scatter(df.iloc[:,0], df.iloc[:,1], c=clustering.labels_, cmap='rainbow')


# In[32]:


clustering = AgglomerativeClustering().fit(df)
AgglomerativeClustering(n_clusters=8, linkage = 'complete')
clustering.labels_


# In[33]:


plt.scatter(df.iloc[:,0], df.iloc[:,1], c=clustering.labels_, cmap='rainbow')


# In[37]:


from sklearn.cluster import KMeans
kmeans = KMeans(n_clusters=2,random_state=2).fit(df)
kmeans.labels_


# In[38]:



kmeans.cluster_centers_


# In[39]:


plt.scatter(df.iloc[:, 0], df.iloc[:, 1], c=kmeans.predict(df), s=50, cmap='viridis')

centers = kmeans.cluster_centers_
plt.scatter(centers[:, 0], centers[:, 1], c='black', s=200, alpha=0.5);


# In[ ]:





# In[ ]:




