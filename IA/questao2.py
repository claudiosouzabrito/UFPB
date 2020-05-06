#!/usr/bin/env python
# coding: utf-8

# In[1]:


import pandas as pd
import numpy as np
import statistics as st
import matplotlib.pyplot as plt
import plotly.express as px
import seaborn as sns
df = pd.read_csv('questao2.csv', delimiter=",")
df


# In[2]:


df.isnull().sum()


# In[3]:


print(df.duplicated().value_counts())
df.drop_duplicates(inplace=True)
print(df)


# In[4]:


corr_matrix = df.corr().abs()
corr_matrix.style.background_gradient(cmap = 'coolwarm')


# In[5]:


sns.boxplot(data=df["temp"])
df["temp"].median()


# In[6]:


mediana = df["temp"].median()
for index, row in df.iterrows():
    if row['temp'] < 50:
        print(row['temp'])
        


# In[7]:


mediana = df["temp"].median()
df['temp'].replace(to_replace = 0.0, value = mediana, inplace=True)


# In[8]:


sns.boxplot(data=df["temp"])


# In[9]:


sns.boxplot(data=df["rain_1h"])


# In[10]:


mediana = df["rain_1h"].median()
for index, row in df.iterrows():
    if row['rain_1h'] > 8000:
        print(row['rain_1h'])


# In[11]:


mediana = df["rain_1h"].median()
df['rain_1h'].replace(to_replace = 9831.3, value = mediana, inplace=True)


# In[12]:


print(df['holiday'].value_counts())
print(df['weather_main'].value_counts())
print(df['weather_description'].value_counts())


# In[13]:


for i in df['holiday']:
    df['holiday'].replace(to_replace = 'None', value = 0, inplace=True)
    df['holiday'].replace(to_replace = 'Labor Day', value = 1, inplace=True)
    df['holiday'].replace(to_replace = 'Martin Luther King Jr Day', value = 2, inplace=True)
    df['holiday'].replace(to_replace = 'Christmas Day', value = 3, inplace=True)
    df['holiday'].replace(to_replace = 'Thanksgiving Day', value = 4, inplace=True)
    df['holiday'].replace(to_replace = 'New Years Day', value = 5, inplace=True)
    df['holiday'].replace(to_replace = 'Washingtons Birthday', value = 6, inplace=True)
    df['holiday'].replace(to_replace = 'Memorial Day', value = 7, inplace=True)
    df['holiday'].replace(to_replace = 'Independence Day', value = 8, inplace=True)
    df['holiday'].replace(to_replace = 'State Fair', value = 9, inplace=True)
    df['holiday'].replace(to_replace = 'Columbus Day', value = 10, inplace=True)
    df['holiday'].replace(to_replace = 'Veterans Day', value = 11, inplace=True)
    
 


# In[14]:


for i in df['weather_main']:
    df['weather_main'].replace(to_replace = 'Clouds', value = 0, inplace=True)
    df['weather_main'].replace(to_replace = 'Clear', value = 1, inplace=True)
    df['weather_main'].replace(to_replace = 'Mist', value = 2, inplace=True)
    df['weather_main'].replace(to_replace = 'Rain', value = 3, inplace=True)
    df['weather_main'].replace(to_replace = 'Snow', value = 4, inplace=True)
    df['weather_main'].replace(to_replace = 'Drizzle', value = 5, inplace=True)
    df['weather_main'].replace(to_replace = 'Haze', value = 6, inplace=True)
    df['weather_main'].replace(to_replace = 'Thunderstorm', value = 7, inplace=True)
    df['weather_main'].replace(to_replace = 'Fog', value = 8, inplace=True)
    df['weather_main'].replace(to_replace = 'Smoke', value = 9, inplace=True)
    df['weather_main'].replace(to_replace = 'Squall', value = 10, inplace=True)
    


# In[15]:



for i in df['weather_description']:
    df['weather_description'].replace(to_replace = 'sky is clear', value = 0, inplace=True)
    df['weather_description'].replace(to_replace = 'mist', value = 1, inplace=True)
    df['weather_description'].replace(to_replace = 'overcast clouds', value = 2, inplace=True)
    df['weather_description'].replace(to_replace = 'broken clouds', value = 3, inplace=True)
    df['weather_description'].replace(to_replace = 'scattered clouds', value = 4, inplace=True)
    df['weather_description'].replace(to_replace = 'light rain', value = 5, inplace=True)
    df['weather_description'].replace(to_replace = 'few clouds', value = 6, inplace=True)
    df['weather_description'].replace(to_replace = 'light snow', value = 7, inplace=True)
    df['weather_description'].replace(to_replace = 'Sky is Clear', value = 8, inplace=True)
    df['weather_description'].replace(to_replace = 'moderate rain', value = 9, inplace=True)
    df['weather_description'].replace(to_replace = 'haze', value = 10, inplace=True)
    df['weather_description'].replace(to_replace = 'light intensity drizzle', value = 11, inplace=True)
    df['weather_description'].replace(to_replace = 'fog', value = 12, inplace=True)
    df['weather_description'].replace(to_replace = 'proximity thunderstorm', value = 13, inplace=True)
    df['weather_description'].replace(to_replace = 'drizzle', value = 14, inplace=True)
    df['weather_description'].replace(to_replace = 'heavy snow', value = 15, inplace=True)
    df['weather_description'].replace(to_replace = 'heavy intensity rain', value = 16, inplace=True)
    df['weather_description'].replace(to_replace = 'snow', value = 17, inplace=True)
    df['weather_description'].replace(to_replace = 'proximity shower rain', value = 18, inplace=True)
    df['weather_description'].replace(to_replace = 'thunderstorm', value = 19, inplace=True)
    df['weather_description'].replace(to_replace = 'heavy intensity drizzle', value = 20, inplace=True)
    df['weather_description'].replace(to_replace = 'thunderstorm with heavy rain', value = 21, inplace=True)
    df['weather_description'].replace(to_replace = 'thunderstorm with light rain', value = 22, inplace=True)
    df['weather_description'].replace(to_replace = 'proximity thunderstorm with rain', value = 23, inplace=True)
    df['weather_description'].replace(to_replace = 'thunderstorm with rain', value = 24, inplace=True)
    df['weather_description'].replace(to_replace = 'smoke', value = 25, inplace=True)
    df['weather_description'].replace(to_replace = 'very heavy rain', value = 26, inplace=True)
    df['weather_description'].replace(to_replace = 'thunderstorm with light drizzle', value = 27, inplace=True)
    df['weather_description'].replace(to_replace = 'proximity thunderstorm with drizzle', value = 28, inplace=True)
    df['weather_description'].replace(to_replace = 'light intensity shower rain', value = 29, inplace=True)
    df['weather_description'].replace(to_replace = 'light shower snow', value = 30, inplace=True)
    df['weather_description'].replace(to_replace = 'light rain and snow', value = 31, inplace=True)
    df['weather_description'].replace(to_replace = 'shower drizzle', value = 32, inplace=True)
    df['weather_description'].replace(to_replace = 'SQUALLS', value = 33, inplace=True)
    df['weather_description'].replace(to_replace = 'sleet', value = 34, inplace=True)
    df['weather_description'].replace(to_replace = 'freezing rain', value = 35, inplace=True)
    df['weather_description'].replace(to_replace = 'thunderstorm with drizzle', value = 36, inplace=True)
    df['weather_description'].replace(to_replace = 'shower snow', value = 37, inplace=True)


# In[16]:


print(df['holiday'].value_counts())
print(df['weather_main'].value_counts())
print(df['weather_description'].value_counts())


# In[17]:




#NORMALIZACAO
col = ['temp', 'rain_1h', 'snow_1h', 'clouds_all', 'weather_description', 'weather_main', 'holiday','traffic_volume' ]
df_numeric = df[col]
# Normalize all of the numeric columns
df_normalized = (df_numeric - df_numeric.mean()) / df_numeric.std()
dfbu = df
df = df_normalized


# In[26]:


from sklearn.model_selection import train_test_split 
from sklearn.linear_model import LinearRegression
from sklearn import metrics
X = df[['temp', 'rain_1h', 'snow_1h', 'clouds_all', 'weather_description', 'weather_main', 'holiday']].values
y = df['traffic_volume'].values
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=0)
regressor = LinearRegression()  
regressor.fit(X_train, y_train)


# In[19]:


y_pred = regressor.predict(X_test)
mse = (((y_pred - y_test) ** 2).sum()) / len(y_pred)
mse


# In[27]:


from sklearn.preprocessing import PolynomialFeatures
X_ = PolynomialFeatures(degree=2, include_bias=False).fit_transform(X)
X_train, X_test, y_train, y_test = train_test_split(X_, y, test_size=0.3, random_state=0)
model = LinearRegression()
model.fit(X_train, y_train)


# In[21]:



y_pred = model.predict(X_test)
mse = (((y_pred - y_test) ** 2).sum()) / len(y_pred)
mse


# In[23]:


from sklearn.model_selection import KFold
kf = KFold(n_splits = 10, shuffle = True, random_state = 2)
for result in kf.split(df):
    train = df.iloc[result[0]]
    test =  df.iloc[result[1]]
    X_train = train[['temp', 'rain_1h', 'snow_1h', 'clouds_all', 'weather_description', 'weather_main', 'holiday']].values
    y_train = train['traffic_volume'].values
    X_test = test[['temp', 'rain_1h', 'snow_1h', 'clouds_all', 'weather_description', 'weather_main', 'holiday']].values
    y_test = test['traffic_volume'].values
    regressor = LinearRegression()  
    regressor.fit(X_train, y_train)
    y_pred = regressor.predict(X_test)
    mse = (((y_pred - y_test) ** 2).sum()) / len(y_pred)
    print(mse)


# In[24]:


kf = KFold(n_splits = 10, shuffle = True, random_state = 2)
for result in kf.split(df):
    train = df.iloc[result[0]]
    test =  df.iloc[result[1]]
    X_train = train[['temp', 'rain_1h', 'snow_1h', 'clouds_all', 'weather_description', 'weather_main', 'holiday']].values
    y_train = train['traffic_volume'].values
    X_test = test[['temp', 'rain_1h', 'snow_1h', 'clouds_all', 'weather_description', 'weather_main', 'holiday']].values
    y_test = test['traffic_volume'].values
    X_train_ = PolynomialFeatures(degree=2, include_bias=False).fit_transform(X_train)
    X_test_ = PolynomialFeatures(degree=2, include_bias=False).fit_transform(X_test)
    regressor = LinearRegression()  
    regressor.fit(X_train_, y_train)
    y_pred = regressor.predict(X_test_)
    mse = (((y_pred - y_test) ** 2).sum()) / len(y_pred)
    print(mse)


# In[ ]:





# In[ ]:




