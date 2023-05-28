import numpy as np
import pandas as pd
import tensorflow as tf
from tensorflow.keras.preprocessing.text import Tokenizer
from tensorflow.keras.preprocessing.sequence import pad_sequences
from sklearn.model_selection import train_test_split

df = pd.read_csv('./Train.csv')
df.shape
df.columns

text = df['text'].values
label = df['label'].values

train_text, test_text, train_label, test_label = train_test_split(text, label, test_size=0.2, random_state=42)

tokenizer = Tokenizer(num_words=10000, oov_token='<OOV>')
tokenizer.fit_on_texts(train_text)
train_sequences = tokenizer.texts_to_sequences(train_text)
test_sequences = tokenizer.texts_to_sequences(test_text)

maxlen=200
train_padded = pad_sequences(train_sequences, maxlen=maxlen, truncating='post', padding='post')
test_padded = pad_sequences(test_sequences, maxlen=maxlen, truncating='post', padding='post')

model = tf.keras.Sequential([
    tf.keras.layers.Embedding(input_dim=10000, output_dim=16, input_length=maxlen),
    tf.keras.layers.Flatten(),
    tf.keras.layers.Dense(32, activation='relu'),
    tf.keras.layers.Dropout(0.5),
    tf.keras.layers.Dense(1, activation='sigmoid')
])
model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])

model.fit(train_padded, train_label, epochs=20, validation_data=(test_padded, test_label))

predictions = model.predict(test_padded)

predictions = (predictions > 0.5).astype(int)

from sklearn.metrics import accuracy_score
accuracy = accuracy_score(test_label, predictions)
print("Accuracy = ", accuracy)