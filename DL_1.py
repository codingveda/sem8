import pandas as pd

column_names = ['CRIM', 'ZN', 'INDUS', 'CHAS', 'NOX', 'RM', 'AGE', 'DIS', 'RAD', 'TAX', 'PTRATIO', 'B', 'LSTAT', 'MEDV']
data = pd.read_csv('./housing.csv', header=None, delimiter=r"\s+", names=column_names)
data.head(5)

import tensorflow as tf
from tensorflow.keras.datasets import boston_housing
from sklearn import preprocessing

(train_x, train_y), (test_x, test_y) = boston_housing.load_data()

print("Train Shape : ", train_x.shape)
print("Test Shape : ", test_x.shape)
print("Actual Train output : ", train_y.shape)
print("Actual Test output : ", test_y.shape)

train_x = preprocessing.normalize(train_x)
test_x = preprocessing.normalize(test_x)

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import *

def HousePricePredictionModel():
    model = Sequential()
    model.add(Dense(128, activation="relu", input_shape=(train_x[0].shape)))
    model.add(Dense(64, activation="relu"))
    model.add(Dense(32, activation="relu"))
    model.add(Dense(1))
    model.compile(optimizer="rmsprop", loss="mse", metrics=["mse"])
    return model


import numpy as np
k = 4
num_val_samples = len(train_x)
num_epochs = 100
all_scores = []


model = HousePricePredictionModel()
history = model.fit(x=train_x, y=train_y, epochs=num_epochs, batch_size=1, verbose=1, validation_data=(test_x, test_y))


test_input = [[1.67955291e-02, 0.00000000e+00, 2.32502295e-02, 0.00000000e+00,
       7.45034979e-04, 7.33859454e-03, 7.28335919e-02, 3.62716426e-03,
       3.08290336e-02, 8.55505683e-01, 2.59477700e-02, 5.09835143e-01,
       1.89598557e-02]]
print("Actual Output : 20.1")
print("Predicted Output : ", model.predict(test_input))