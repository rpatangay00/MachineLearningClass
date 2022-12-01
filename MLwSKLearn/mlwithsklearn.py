# -*- coding: utf-8 -*-
"""MLwithSKLearn.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/11AimAKL-GmjfBrMiwZKlfhdTWxGTQ-eV

**ML with SKLearn Assignment**

Rikita Patangay

Due Sunday 11/6

**Reading in the data**

First we have to read in the data and save Auto.csv into pandas dataframe.
"""

import pandas as pd

df = pd.read_csv('Auto.csv')

print(df.head())
print('\nDimensions of data frame:', df.shape)

"""df = df.drop(columns=['name','mpg'])
print(df.head())

**Data exploration**
"""

print('\nDescribe  mpg, weight, and year:\n', df.loc[:, ['mpg', 'weight', 'year']].describe())

print('\nRange of mpg:\t\t', df['mpg'].max() - df['mpg'].min())
print('Range of weight:\t', df['weight'].max() - df['weight'].min())
print('Range of year:\t\t', df['year'].max() - df['year'].min())

print('\nMean of mpg:\t', df['mpg'].mean())
print('Mean of weight:\t', df['weight'].mean())
print('Mean of year:\t', df['year'].mean())

"""**What data types do we see?**"""

df.dtypes

"""**Categorical data visualization**"""

df.cylinders = df.cylinders.astype('category').cat.codes
df = df.astype({"origin":'category'})
df.dtypes

"""NAs"""

df.isna().sum()

"""**Dropping the NAs**

There are 3 nas we will drop them from the data (Acceleration(1)Year(2))
"""

df = df.dropna()
print('\nDimensions of data frame:', df.shape)

import numpy as np
avg = df.mpg.mean()
df['mpg_high'] = np.where(df.mpg > avg, 1, 0)

"""**Modify the data into columns**

"""

df = df.drop(columns=['name','mpg'])
print(df.head())

"""**Graph Visualization**"""

import seaborn as sb

sb.catplot(x = 'mpg_high', kind = 'count', data = df)

"""**Horsepower vs. weight**"""

sb.relplot(x = 'horsepower', y = 'weight', data = df, hue = df.mpg_high)

"""**mpg_high vs. weight**"""

sb.boxplot(x = 'mpg_high', y = 'weight', data = df)

"""**Splitting train and test**"""

import sklearn
from sklearn.model_selection import train_test_split

X = df.iloc[:, 0:6]
y = df.iloc[:, 7]

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.2, random_state = 1234)

print('Train size:', X_train.shape)
print('Test size:', X_test.shape)

"""**Logistic Regression**

We will now perform logisic regression on the train data.
"""

from sklearn.linear_model import LogisticRegression

logReg = LogisticRegression(max_iter=10000)
LogisticReg = LogisticRegression(solver = 'lbfgs')
logReg.fit(X_train, y_train)
logReg.score(X_train, y_train)

"""**Predict**"""

predLR = logReg.predict(X_test)

"""**Evaluate**"""

from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score

accuracyLR = accuracy_score(y_test, predLR)
precisionLR = precision_score(y_test, predLR, average='micro')
recallLR = recall_score(y_test, predLR, average='micro')
f1LR = f1_score(y_test, predLR, average='micro')

print('Accuracy score: ', accuracyLR)
print('Precision score: ', precisionLR)
print('Recall score: ', recallLR)
print('f1 score: ', f1LR)

"""**Decision Tree**

Train a decision tree.
"""

from sklearn.tree import DecisionTreeClassifier

dTree = DecisionTreeClassifier()
dTree.fit(X_train, y_train)

"""**Make predictions**"""

predDT = dTree.predict(X_test)

"""**Evaluate**"""

accuracyDT = accuracy_score(y_test, predDT)
precisionDT = precision_score(y_test, predDT, average='micro')
recallDT = recall_score(y_test, predDT, average='micro')
f1DT = f1_score(y_test, predDT, average='micro')

print('Accuracy score: ', accuracyDT)
print('Precision score: ', precisionDT)
print('Recall score: ', recallDT)
print('f1 score: ', f1DT)

"""**Neural Network**

Make the data normal.
"""

from sklearn import preprocessing

scaler = preprocessing.StandardScaler().fit(X_train)

X_train_scaled = scaler.transform(X_train)
X_test_scaled = scaler.transform(X_test)

"""**Using Hidden layer**

Train the data with hidden Layer size (5,2).
"""

from sklearn.neural_network import MLPClassifier

nn1 = MLPClassifier(solver='lbfgs', hidden_layer_sizes=(5, 2), max_iter=500, random_state=1234)
nn1.fit(X_train_scaled, y_train)

"""**Predict**"""

predNN1 = nn1.predict(X_test_scaled)

"""**Output the result (Confusion Matrix)**"""

from sklearn.metrics import confusion_matrix

accuracyNN1 = accuracy_score(y_test, predNN1)
precisionNN1 = precision_score(y_test, predNN1,average='micro')
recallNN1 = recall_score(y_test, predNN1,average='micro')
f1NN1 = f1_score(y_test, predNN1,average='micro')

print('Accuracy score: ', accuracyNN1)
print('Precision score: ', precisionNN1)
print('Recall score: ', recallNN1)
print('f1 score: ', f1NN1)

confusion_matrix(y_test, predNN1)

"""**Using hidden layer**

Using hidden layer size (4.2), train neural network.
"""

nn2 = MLPClassifier(solver='lbfgs', hidden_layer_sizes=(4, 2), max_iter=1000, random_state=1234)
nn2.fit(X_train_scaled, y_train)

"""# **Predict**"""

predNN2 = nn2.predict(X_test_scaled)

"""# **Output the result**"""

accuracyNN2 = accuracy_score(y_test, predNN2)
precisionNN2 = precision_score(y_test, predNN2,average='micro')
recallNN2 = recall_score(y_test, predNN2,average='micro')
f1NN2 = f1_score(y_test, predNN2,average='micro')

print('accuracy score: ', accuracyNN2)
print('precision score: ', precisionNN2)
print('recall score: ', recallNN2)
print('f1 score: ', f1NN2)

confusion_matrix(y_test, predNN2)

"""# **Analysis**

From what I can see from this data, **Decision Tree** was put to a better use for this data. Decision Tree outperformed Logistic Regression and Neural Network in accuracy and precision. The algorithms had tied when it came to recall. Since neural networks are usually used for more complex sets of data the algorithm was not suitable foe these smaller set of data. 

I definitely much prefer **SKLearn** to R. I feel that SKLearn in a simpler way, and simpler syntax. I think this is because I have had more experience programming in Python. I really liked using Google Colab for this assignment. I am very familiar with Google apps and I think their interface is pretty straightforward and easy to learn. Before this class I had never heard of it, and I am glad that I have the knowlwdge on how to use it now.


"""