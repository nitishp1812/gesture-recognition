import numpy as np
import cv2
from sklearn.metrics import classification_report, confusion_matrix
from keras.models import load_model
from keras.callbacks import ModelCheckpoint
from keras import models, layers, optimizers

# used to train the model
def train(x_train, y_train, x_val, y_val):
    model_name = 'gesture-model.h5'

    model = models.Sequential()
    model.add(layers.Conv2D(32, (5, 5), strides=(2, 2), activation='relu', input_shape=(224, 224, 1)))
    model.add(layers.MaxPooling2D(pool_size=(2, 2)))
    model.add(layers.Conv2D(64, (3, 3), activation='relu'))
    model.add(layers.MaxPooling2D(pool_size=(2, 2)))
    model.add(layers.Conv2D(64, (3, 3), activation='relu'))
    model.add(layers.MaxPooling2D(pool_size=(2, 2)))
    model.add(layers.Flatten())
    model.add(layers.Dense(128, activation='relu'))
    model.add(layers.Dense(128, activation='relu'))
    model.add(layers.Dense(128, activation='relu'))
    model.add(layers.Dropout(0.25, seed=21))
    model.add(layers.Dense(36, activation='softmax'))

    model.compile(optimizer=optimizers.SGD(lr=1e-2), loss='categorical_crossentropy', metrics=['accuracy'])

    checkpoint = ModelCheckpoint(model_name, monitor='val_acc', verbose=1, save_best_only=True, mode='max')

    model.fit(x_train, y_train, epochs=35, batch_size=500,
            validation_data=(x_val, y_val), verbose=1, callbacks=[checkpoint])
    scores = model.evaluate(x_val, y_val, verbose=0)
    print(scores)

    model.save(model_name)

    print("saved model")

def test(x_test, y_test):
    model = load_model('gesture-model.h5')
    y_test = np.array([np.argmax(y) for y in y_test])
    y_pred = model.predict(x_test)
    y_pred = np.array([np.argmax(y) for y in y_pred])

    print(classification_report(y_test, y_pred))
    print(confusion_matrix(y_test, y_pred))
