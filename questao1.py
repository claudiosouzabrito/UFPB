#!/usr/bin/env python
# coding: utf-8

# In[1]:


pip install pandas 


# In[ ]:





# In[ ]:





# In[2]:


pip install statistics


# In[3]:


pip install matplotlib


# In[4]:


pip install plotly


# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[5]:


from sklearn import cluster, neighbors, svm, metrics, preprocessing


# In[6]:


pip install sklearn


# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[ ]:





# In[7]:


pip install seaborn


# In[8]:


import pandas as pd
import numpy as np
import statistics as st
import matplotlib.pyplot as plt
import plotly.express as px
import seaborn as sns
df = pd.read_csv('questao1.csv', delimiter=",")
df


# In[9]:


df = pd.read_csv('questao1.csv', delimiter=",")
df
sns.boxplot(data=df["MM-centroid"])
df["MM-centroid"].median()


# In[ ]:





# In[10]:


df = pd.read_csv('questao1.csv', delimiter=",")
df
sns.boxplot(data=df["MM-rolloff"])
df["MM-rolloff"].median()


# In[11]:



df = pd.read_csv('questao1.csv', delimiter=",")
df
sns.boxplot(data=df["MM-rolloff"])
df["MM-rolloff"].median()


# In[12]:



df = pd.read_csv('questao1.csv', delimiter=",")
df
sns.boxplot(data=df["MM-flux"])
df["MM-flux"].median()


# In[13]:



df = pd.read_csv('questao1.csv', delimiter=",")
df
sns.boxplot(data=df["MM-flux"])
df["MM-flux"].median()


# In[14]:


df = pd.read_csv('questao1.csv', delimiter=",")
df
sns.boxplot(data=df["MM-mfcc_0"])
df["MM-mfcc_0"].median()


# In[15]:


df = pd.read_csv('questao1.csv', delimiter=",")
df
sns.boxplot(data=df["MM-mfcc_0"])
df["MM-mfcc_0"].median()


# In[16]:


df = pd.read_csv('questao1.csv', delimiter=",")
df

sns.boxplot(data=df["happy"])
df["happy"].median()


# In[17]:


df = pd.read_csv('questao1.csv', delimiter=",")
#NORMALIZACAO
df_numeric = df[df.columns]
# Normalize all of the numeric columns
df_normalized = (df_numeric - df_numeric.mean()) / df_numeric.std()


# In[18]:





def column(matrix, i):
    return [row[i] for row in matrix]


# In[19]:



import random
from numpy.random import permutation
import math

#METODO KNN
# Embaralha aleatoriamente df
random_indices = permutation(df.index)

# teste = 20% das amostras
test_cutoff = math.floor(len(df)/5)

test = df.loc[random_indices[1:test_cutoff]]

# treino = resto (80%) das amostras
train = df.loc[random_indices[test_cutoff:]]


# In[20]:


# colunas que vao servir para o treinamento
x_columns = ['BS1', 'BS2', 'BS3', 'HPA', 'HPB', 'LPA', 'LPB', 'MM-centroid',
       'MM-flux', 'MM-mfcc_0', 'MM-mfcc_1', 'MM-mfcc_10', 'MM-mfcc_11',
       'MM-mfcc_12', 'MM-mfcc_2', 'MM-mfcc_3', 'MM-mfcc_4', 'MM-mfcc_5',
       'MM-mfcc_6', 'MM-mfcc_7', 'MM-mfcc_8', 'MM-mfcc_9', 'MM-rolloff',
       'MS-centroid', 'MS-flux', 'MS-mfcc_1', 'MS-mfcc_10', 'MS-mfcc_11',
       'MS-mfcc_12', 'MS-mfcc_2', 'MS-mfcc_3', 'MS-mfcc_4', 'MS-mfcc_5',
       'MS-mfcc_6', 'MS-mfcc_7', 'MS-mfcc_8', 'MS-mfcc_9', 'MS-rolloff',
       'SM-centroid', 'SM-flux', 'SM-mfcc_0', 'SM-mfcc_1', 'SM-mfcc_10',
       'SM-mfcc_11', 'SM-mfcc_12', 'SM-mfcc_2', 'SM-mfcc_3', 'SM-mfcc_4',
       'SM-mfcc_5', 'SM-mfcc_6', 'SM-mfcc_7', 'SM-mfcc_8', 'SM-mfcc_9',
       'SM-rolloff', 'SS-centroid', 'SS-flux', 'SS-mfcc_0', 'SS-mfcc_1',
       'SS-mfcc_10', 'SS-mfcc_11', 'SS-mfcc_12', 'SS-mfcc_2', 'SS-mfcc_3',
       'SS-mfcc_4', 'SS-mfcc_5', 'SS-mfcc_6', 'SS-mfcc_7', 'SS-mfcc_8',
       'SS-mfcc_9', 'SS-rolloff', 'id']
# colnas que devem ser adivinhadas
y_column = ["amazed", "happy", "relaxing", "sad", "quiet", "angry"]

from sklearn.neighbors import KNeighborsClassifier

knn = KNeighborsClassifier(n_neighbors=5)
# colocando o treino para funcionar
knn.fit(train[x_columns], train[y_column])
# adivinhando
predictions = knn.predict(test[x_columns])


# In[21]:



from sklearn.metrics import accuracy_score
from sklearn.metrics import confusion_matrix

# pegar as respostas para comparacao 
actual = test[y_column]
print("\n acuracia K-NN")
mse = (((predictions - actual) ** 2).sum()) / len(predictions)
print( 1 - mse)
predictions = np.around(predictions)
nactual = actual.to_numpy()
print("matriz de confusao amazed")
print(confusion_matrix(column(nactual, 0), column(predictions, 0)))
print("matriz de confusao happy")
print(confusion_matrix(column(nactual, 1), column(predictions, 1)))
print("matriz de confusao relaxing")
print(confusion_matrix(column(nactual, 2), column(predictions, 2)))
print("matriz de confusao sad")
print(confusion_matrix(column(nactual, 3), column(predictions, 3)))
print("matriz de confusao quiet")
print(confusion_matrix(column(nactual, 4), column(predictions, 4)))
print("matriz de confusao angry")
print(confusion_matrix(column(nactual, 5), column(predictions, 5)))


# In[22]:


#Importa biblioteca
#Importa outras bibliotecas necessárias como pandas, numpy...
from sklearn import tree
#Assume que você tem X (preditor) e Y (alvo) para dados de treino e x_test(predictor) dos dados de teste
# Cria o objeto tree
model = tree.DecisionTreeClassifier(criterion='gini') 
# Para classificação, aqui você pode mudar o algoritmo para gini ou para entropy (Ganho de informação). Por default é gini  
# model = tree.DecisionTreeRegressor() para regressão
# Treina o modelo usando os dados de treino e de teste confere o score
model.fit(train[x_columns], train[y_column])
model.score(train[x_columns], train[y_column])
#Prevê o resultado
predicted= model.predict(test[x_columns])
print("\n acuracia arvore de decisao")
mse = (((predicted - actual) ** 2).sum()) / len(predicted)
print( 1 - mse)
predicted = np.around(predicted)
nactual = actual.to_numpy()
print("matriz de confusao amazed")
print(confusion_matrix(column(nactual, 0), column(predicted, 0)))
print("matriz de confusao happy")
print(confusion_matrix(column(nactual, 1), column(predicted, 1)))
print("matriz de confusao relaxing")
print(confusion_matrix(column(nactual, 2), column(predicted, 2)))
print("matriz de confusao sad")
print(confusion_matrix(column(nactual, 3), column(predicted, 3)))
print("matriz de confusao quiet")
print(confusion_matrix(column(nactual, 4), column(predicted, 4)))
print("matriz de confusao angry")
print(confusion_matrix(column(nactual, 5), column(predicted, 5)))


# In[23]:


#AGORA CORRELACAO


# In[24]:


import numpy as np

# Create correlation matrix
corr_matrix = df.corr().abs()
corr_matrix.style.background_gradient(cmap = 'coolwarm')


# In[25]:


#DROPANDO COLUNAS COM ALTA CORRELACAO
# Select upper triangle of correlation matrix
upper = corr_matrix.where(np.triu(np.ones(corr_matrix.shape), k=1).astype(np.bool))

# Find features with correlation greater than 0.75
to_drop = [column for column in upper.columns if any(upper[column] > 0.75)]

# Drop features 
df.drop(to_drop, axis=1, inplace=True)


# In[26]:


corr_matrix = df.corr().abs()
corr_matrix.style.background_gradient(cmap = 'coolwarm')


# In[27]:


df.columns.difference(["amazed", "happy", "relaxing", "sad", "quiet", "angry"])
# Randomly shuffle the index of df.
random_indices = permutation(df.index)

# Set a cutoff for how many items we want in the test set (in this case 1/5 of the items)
test_cutoff = math.floor(len(df)/5)

# Generate the test set by taking the first 1/5 of the randomly shuffled indices.
test = df.loc[random_indices[1:test_cutoff]]

# Generate the train set with the rest of the data.
train = df.loc[random_indices[test_cutoff:]]


# In[28]:


# The columns that we will be making predictions with.
x_columns = ['BS1', 'BS2', 'BS3', 'HLR', 'HPA', 'LPA', 'LPB', 'MM-centroid',
       'MM-flux', 'MM-mfcc_0', 'MM-mfcc_10', 'MM-mfcc_11', 'MM-mfcc_12',
       'MM-mfcc_2', 'MM-mfcc_3', 'MM-mfcc_4', 'MM-mfcc_5', 'MM-mfcc_6',
       'MM-mfcc_7', 'MM-mfcc_8', 'MM-mfcc_9', 'MM-rolloff', 'MS-centroid',
       'MS-mfcc_1', 'MS-mfcc_2', 'MS-mfcc_3', 'MS-mfcc_7', 'MS-mfcc_8',
       'MS-mfcc_9', 'MS-rolloff', 'SM-centroid', 'SM-flux', 'SM-mfcc_0',
       'SM-mfcc_1', 'SM-mfcc_10', 'SM-mfcc_11', 'SM-mfcc_12', 'SM-mfcc_2',
       'SM-mfcc_3', 'SM-mfcc_4', 'SM-mfcc_5', 'SM-mfcc_6', 'SM-mfcc_7',
       'SM-mfcc_8', 'SM-mfcc_9', 'SM-rolloff', 'SS-centroid', 'SS-mfcc_0',
       'SS-mfcc_1', 'SS-mfcc_10', 'SS-mfcc_11', 'SS-mfcc_12', 'SS-mfcc_2',
       'SS-mfcc_3', 'SS-mfcc_4', 'SS-mfcc_5', 'SS-mfcc_6', 'SS-mfcc_7',
       'SS-mfcc_8', 'SS-mfcc_9', 'SS-rolloff', 'id']
# The column that we want to predict.
y_column = ["amazed", "happy", "relaxing", "sad", "quiet", "angry"]


# Create the knn model.
# Look at the five closest neighbors.
knn = KNeighborsClassifier(n_neighbors=5)
# Fit the model on the training data.
knn.fit(train[x_columns], train[y_column])
# Make point predictions on the test set using the fit model.
predictions = knn.predict(test[x_columns])
# Get the actual values for the test set.
from sklearn.metrics import accuracy_score

actual = test[y_column]
print("\nK-NN")
mse = (((predictions - actual) ** 2).sum()) / len(predictions)
print( 1 - mse)
predictions = np.around(predictions)
nactual = actual.to_numpy()
print("matriz de confusao amazed")
print(confusion_matrix(column(nactual, 0), column(predictions, 0)))
print("matriz de confusao happy")
print(confusion_matrix(column(nactual, 1), column(predictions, 1)))
print("matriz de confusao relaxing")
print(confusion_matrix(column(nactual, 2), column(predictions, 2)))
print("matriz de confusao sad")
print(confusion_matrix(column(nactual, 3), column(predictions, 3)))
print("matriz de confusao quiet")
print(confusion_matrix(column(nactual, 4), column(predictions, 4)))
print("matriz de confusao angry")
print(confusion_matrix(column(nactual, 5), column(predictions, 5)))


# In[29]:


model = tree.DecisionTreeClassifier(criterion='gini') 
# Para classificação, aqui você pode mudar o algoritmo para gini ou para entropy (Ganho de informação). Por default é gini  
# model = tree.DecisionTreeRegressor() para regressão
# Treina o modelo usando os dados de treino e de teste confere o score
model.fit(train[x_columns], train[y_column])
model.score(train[x_columns], train[y_column])
#Prevê o resultado
predicted= model.predict(test[x_columns])
print("\n acuracia arvore de decisao")
mse = (((predicted - actual) ** 2).sum()) / len(predicted)
print( 1 - mse)
predicted = np.around(predicted)
nactual = actual.to_numpy()
print("matriz de confusao amazed")
print(confusion_matrix(column(nactual, 0), column(predicted, 0)))
print("matriz de confusao happy")
print(confusion_matrix(column(nactual, 1), column(predicted, 1)))
print("matriz de confusao relaxing")
print(confusion_matrix(column(nactual, 2), column(predicted, 2)))
print("matriz de confusao sad")
print(confusion_matrix(column(nactual, 3), column(predicted, 3)))
print("matriz de confusao quiet")
print(confusion_matrix(column(nactual, 4), column(predicted, 4)))
print("matriz de confusao angry")
print(confusion_matrix(column(nactual, 5), column(predicted, 5)))



print(df['amazed'].value_counts())
print(df['happy'].value_counts())
print(df['relaxing'].value_counts())
print(df['sad'].value_counts())
print(df['quiet'].value_counts())
print(df['angry'].value_counts())


# In[ ]:





# In[30]:


df = pd.read_csv('questao1.csv', delimiter=",")
df
from sklearn.utils import resample
# Separate majority and minority classes
df_majority = df[df.quiet==0]
df_minority = df[df.quiet==1]
 
# Downsample majority class
df_majority_downsampled = resample(df_majority, 
                                 replace=False,    # sample without replacement
                                 n_samples=df['quiet'].value_counts()[1],     # to match minority class
                                 random_state=123) # reproducible results
 
# Combine minority class with downsampled majority class
df_downsampled = pd.concat([df_majority_downsampled, df_minority])
 
# Display new class counts
df_downsampled.quiet.value_counts()
# 1    49
# 0    49
# Name: balance, dtype: int64


# In[31]:


# Randomly shuffle the index of df_downsampled.
random_indices = permutation(df_downsampled.index)

# Set a cutoff for how many items we want in the test set (in this case 1/5 of the items)
test_cutoff = math.floor(len(df_downsampled)/5)

# Generate the test set by taking the first 1/5 of the randomly shuffled indices.
test = df_downsampled.loc[random_indices[1:test_cutoff]]

# Generate the train set with the rest of the data.
train = df_downsampled.loc[random_indices[test_cutoff:]]


# In[32]:


# The columns that we will be making predictions with.
x_columns = ['BS1', 'BS2', 'BS3', 'HLR', 'HPA', 'HPB', 'LPA', 'LPB', 'MM-centroid',
       'MM-flux', 'MM-mfcc_0', 'MM-mfcc_1', 'MM-mfcc_10', 'MM-mfcc_11',
       'MM-mfcc_12', 'MM-mfcc_2', 'MM-mfcc_3', 'MM-mfcc_4', 'MM-mfcc_5',
       'MM-mfcc_6', 'MM-mfcc_7', 'MM-mfcc_8', 'MM-mfcc_9', 'MM-rolloff',
       'MS-centroid', 'MS-flux', 'MS-mfcc_1', 'MS-mfcc_10', 'MS-mfcc_11',
       'MS-mfcc_12', 'MS-mfcc_2', 'MS-mfcc_3', 'MS-mfcc_4', 'MS-mfcc_5',
       'MS-mfcc_6', 'MS-mfcc_7', 'MS-mfcc_8', 'MS-mfcc_9', 'MS-rolloff',
       'SM-centroid', 'SM-flux', 'SM-mfcc_0', 'SM-mfcc_1', 'SM-mfcc_10',
       'SM-mfcc_11', 'SM-mfcc_12', 'SM-mfcc_2', 'SM-mfcc_3', 'SM-mfcc_4',
       'SM-mfcc_5', 'SM-mfcc_6', 'SM-mfcc_7', 'SM-mfcc_8', 'SM-mfcc_9',
       'SM-rolloff', 'SS-centroid', 'SS-flux', 'SS-mfcc_0', 'SS-mfcc_1',
       'SS-mfcc_10', 'SS-mfcc_11', 'SS-mfcc_12', 'SS-mfcc_2', 'SS-mfcc_3',
       'SS-mfcc_4', 'SS-mfcc_5', 'SS-mfcc_6', 'SS-mfcc_7', 'SS-mfcc_8',
       'SS-mfcc_9', 'SS-rolloff', 'id']
# The column that we want to predict.
y_column = ["amazed", "happy", "relaxing", "sad", "quiet", "angry"]


# Create the knn model.
# Look at the five closest neighbors.
knn = KNeighborsClassifier(n_neighbors=5)
# Fit the model on the training data.
knn.fit(train[x_columns], train[y_column])
# Make point predictions on the test set using the fit model.
predictions = knn.predict(test[x_columns])
# Get the actual values for the test set.
from sklearn.metrics import accuracy_score

actual = test[y_column]
print("\nK-NN")
mse = (((predictions - actual) ** 2).sum()) / len(predictions)
print( 1 - mse)
predictions = np.around(predictions)
nactual = actual.to_numpy()
print("matriz de confusao amazed")
print(confusion_matrix(column(nactual, 0), column(predictions, 0)))
print("matriz de confusao happy")
print(confusion_matrix(column(nactual, 1), column(predictions, 1)))
print("matriz de confusao relaxing")
print(confusion_matrix(column(nactual, 2), column(predictions, 2)))
print("matriz de confusao sad")
print(confusion_matrix(column(nactual, 3), column(predictions, 3)))
print("matriz de confusao quiet")
print(confusion_matrix(column(nactual, 4), column(predictions, 4)))
print("matriz de confusao angry")
print(confusion_matrix(column(nactual, 5), column(predictions, 5)))


# In[33]:


model = tree.DecisionTreeClassifier(criterion='gini') 
# Para classificação, aqui você pode mudar o algoritmo para gini ou para entropy (Ganho de informação). Por default é gini  
# model = tree.DecisionTreeRegressor() para regressão
# Treina o modelo usando os dados de treino e de teste confere o score
model.fit(train[x_columns], train[y_column])
model.score(train[x_columns], train[y_column])
#Prevê o resultado
predicted= model.predict(test[x_columns])
print("\n acuracia arvore de decisao")
mse = (((predicted - actual) ** 2).sum()) / len(predicted)
print( 1 - mse)
predicted = np.around(predicted)
nactual = actual.to_numpy()
print("matriz de confusao amazed")
print(confusion_matrix(column(nactual, 0), column(predicted, 0)))
print("matriz de confusao happy")
print(confusion_matrix(column(nactual, 1), column(predicted, 1)))
print("matriz de confusao relaxing")
print(confusion_matrix(column(nactual, 2), column(predicted, 2)))
print("matriz de confusao sad")
print(confusion_matrix(column(nactual, 3), column(predicted, 3)))
print("matriz de confusao quiet")
print(confusion_matrix(column(nactual, 4), column(predicted, 4)))
print("matriz de confusao angry")
print(confusion_matrix(column(nactual, 5), column(predicted, 5)))


# In[34]:


print(df_downsampled['amazed'].value_counts())
print(df_downsampled['happy'].value_counts())
print(df_downsampled['relaxing'].value_counts())
print(df_downsampled['sad'].value_counts())
print(df_downsampled['quiet'].value_counts())
print(df_downsampled['angry'].value_counts())


# In[35]:


df_majority = df_downsampled[df_downsampled.happy==0]
df_minority = df_downsampled[df_downsampled.happy==1]
 
# Downsample majority class
df_majority_downsampled = resample(df_majority, 
                                 replace=False,    # sample without replacement
                                 n_samples=df_downsampled['happy'].value_counts()[1],     # to match minority class
                                 random_state=123) # reproducible results
 
# Combine minority class with downsampled majority class
df_downsampled = pd.concat([df_majority_downsampled, df_minority])
 
# Display new class counts
print(df_downsampled['amazed'].value_counts())
print(df_downsampled['happy'].value_counts())
print(df_downsampled['relaxing'].value_counts())
print(df_downsampled['sad'].value_counts())
print(df_downsampled['quiet'].value_counts())
print(df_downsampled['angry'].value_counts())


# In[36]:


random_indices = permutation(df_downsampled.index)

# Set a cutoff for how many items we want in the test set (in this case 1/5 of the items)
test_cutoff = math.floor(len(df_downsampled)/5)

# Generate the test set by taking the first 1/5 of the randomly shuffled indices.
test = df_downsampled.loc[random_indices[1:test_cutoff]]

# Generate the train set with the rest of the data.
train = df_downsampled.loc[random_indices[test_cutoff:]]


# In[37]:


# The columns that we will be making predictions with.
x_columns = ['BS1', 'BS2', 'BS3', 'HLR', 'HPA', 'HPB', 'LPA', 'LPB', 'MM-centroid',
       'MM-flux', 'MM-mfcc_0', 'MM-mfcc_1', 'MM-mfcc_10', 'MM-mfcc_11',
       'MM-mfcc_12', 'MM-mfcc_2', 'MM-mfcc_3', 'MM-mfcc_4', 'MM-mfcc_5',
       'MM-mfcc_6', 'MM-mfcc_7', 'MM-mfcc_8', 'MM-mfcc_9', 'MM-rolloff',
       'MS-centroid', 'MS-flux', 'MS-mfcc_1', 'MS-mfcc_10', 'MS-mfcc_11',
       'MS-mfcc_12', 'MS-mfcc_2', 'MS-mfcc_3', 'MS-mfcc_4', 'MS-mfcc_5',
       'MS-mfcc_6', 'MS-mfcc_7', 'MS-mfcc_8', 'MS-mfcc_9', 'MS-rolloff',
       'SM-centroid', 'SM-flux', 'SM-mfcc_0', 'SM-mfcc_1', 'SM-mfcc_10',
       'SM-mfcc_11', 'SM-mfcc_12', 'SM-mfcc_2', 'SM-mfcc_3', 'SM-mfcc_4',
       'SM-mfcc_5', 'SM-mfcc_6', 'SM-mfcc_7', 'SM-mfcc_8', 'SM-mfcc_9',
       'SM-rolloff', 'SS-centroid', 'SS-flux', 'SS-mfcc_0', 'SS-mfcc_1',
       'SS-mfcc_10', 'SS-mfcc_11', 'SS-mfcc_12', 'SS-mfcc_2', 'SS-mfcc_3',
       'SS-mfcc_4', 'SS-mfcc_5', 'SS-mfcc_6', 'SS-mfcc_7', 'SS-mfcc_8',
       'SS-mfcc_9', 'SS-rolloff', 'id']
# The column that we want to predict.
y_column = ["amazed", "happy", "relaxing", "sad", "quiet", "angry"]


# Create the knn model.
# Look at the five closest neighbors.
knn = KNeighborsClassifier(n_neighbors=5)
# Fit the model on the training data.
knn.fit(train[x_columns], train[y_column])
# Make point predictions on the test set using the fit model.
predictions = knn.predict(test[x_columns])
# Get the actual values for the test set.
from sklearn.metrics import accuracy_score

actual = test[y_column]
print("\nK-NN")
mse = (((predictions - actual) ** 2).sum()) / len(predictions)
print( 1 - mse)
predictions = np.around(predictions)
nactual = actual.to_numpy()
print("matriz de confusao amazed")
print(confusion_matrix(column(nactual, 0), column(predictions, 0)))
print("matriz de confusao happy")
print(confusion_matrix(column(nactual, 1), column(predictions, 1)))
print("matriz de confusao relaxing")
print(confusion_matrix(column(nactual, 2), column(predictions, 2)))
print("matriz de confusao sad")
print(confusion_matrix(column(nactual, 3), column(predictions, 3)))
print("matriz de confusao quiet")
print(confusion_matrix(column(nactual, 4), column(predictions, 4)))
print("matriz de confusao angry")
print(confusion_matrix(column(nactual, 5), column(predictions, 5)))


# In[38]:


model = tree.DecisionTreeClassifier(criterion='gini') 
# Para classificação, aqui você pode mudar o algoritmo para gini ou para entropy (Ganho de informação). Por default é gini  
# model = tree.DecisionTreeRegressor() para regressão
# Treina o modelo usando os dados de treino e de teste confere o score
model.fit(train[x_columns], train[y_column])
model.score(train[x_columns], train[y_column])
#Prevê o resultado
predicted= model.predict(test[x_columns])
print("\n acuracia arvore de decisao")
mse = (((predicted - actual) ** 2).sum()) / len(predicted)
print( 1 - mse)
predicted = np.around(predicted)
nactual = actual.to_numpy()
print("matriz de confusao amazed")
print(confusion_matrix(column(nactual, 0), column(predicted, 0)))
print("matriz de confusao happy")
print(confusion_matrix(column(nactual, 1), column(predicted, 1)))
print("matriz de confusao relaxing")
print(confusion_matrix(column(nactual, 2), column(predicted, 2)))
print("matriz de confusao sad")
print(confusion_matrix(column(nactual, 3), column(predicted, 3)))
print("matriz de confusao quiet")
print(confusion_matrix(column(nactual, 4), column(predicted, 4)))
print("matriz de confusao angry")
print(confusion_matrix(column(nactual, 5), column(predicted, 5)))


# In[ ]:





# In[ ]:




