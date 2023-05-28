import pandas as pd
from sklearn.model_selection import train_test_split
from keras.models import Sequential
from keras.layers import Dense

# Load dataset
url = "./letter-recognition.data"
names = ['letter', 'x-box', 'y-box', 'width', 'height', 'onpix', 'x-bar', 'y-bar', 'x2bar', 'y2bar', 'xybar', 'x2ybr', 'xy2br', 'x-ege', 'xegvy', 'y-ege', 'yegvx']
dataset = pd.read_csv(url, names=names)

dataset.shape

dataset.head()

# Split into input (X) and output (Y) variables
X = dataset.iloc[:,1:17].values.astype(float)
Y = dataset.iloc[:,0].values

from sklearn.preprocessing import LabelEncoder
label_encoder = LabelEncoder()
Y_encoded = label_encoder.fit_transform(Y)

# Split the dataset into training and testing sets
X_train, X_test, Y_train, Y_test = train_test_split(X, Y_encoded, test_size=0.20, random_state=42)

print("Train Shape : ", X_train.shape)
print("Test Shape : ", X_test.shape)
print("Actual Train output : ", Y_train.shape)
print("Actual Test output : ", Y_test.shape)

# Define model
model = Sequential()
model.add(Dense(128, activation='relu', input_dim=16))
model.add(Dense(64, activation='relu'))
model.add(Dense(26, activation='softmax'))

# Compile model
model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])

# Fit the model
model.fit(X_train, pd.get_dummies(Y_train), epochs=100, batch_size=32, verbose=1)

# Evaluate the model on the test set
scores = model.evaluate(X_test, pd.get_dummies(Y_test))
print("\n%s: %.2f%%" % (model.metrics_names[1], scores[1]*100))