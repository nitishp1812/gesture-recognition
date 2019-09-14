import os

import numpy as np
import cv2
from keras.models import load_model

from train import train, test
from preprocess import load_images, process_image

def get_label(pred_index):
    if pred_index <= 9:
        return chr(pred_index + 48)
    else:
        return chr(pred_index + 87)

if not(os.path.exists('./gesture-model.h5')):
    print("Training new model")

    x_train, x_val, x_test, y_train, y_val, y_test = load_images()

    train(x_train=x_train, y_train=y_train, x_val=x_val, y_val=y_val)
    test(x_test=x_test, y_test=y_test)

model = load_model('gesture-model.h5')
predicted_text = ""
cap = cv2.VideoCapture(0)
left_margin = 100

while True:
    ret, frame = cap.read()
    frame = cv2.flip(frame, 1)
    cv2.rectangle(frame, (350, 150), (600, 400), (0, 255, 0))

    hand_frame = frame[150:400, 350:600]
    processed = process_image(hand_frame)
    processed = np.reshape(processed, (1, processed.shape[0], processed.shape[1], 1))

    text_area = np.zeros((480, 480, 3), dtype=np.uint8)
    
    predicted = model.predict(processed)
    predicted_label = get_label(np.argmax(predicted))

    predicted_text = predicted_label

    cv2.putText(text_area, predicted_text, (4, 100), cv2.FONT_HERSHEY_COMPLEX, 2, (255, 255, 255))

    frame = np.hstack((frame, text_area))

    cv2.imshow('Gesture Recognition', frame)

    if cv2.waitKey(50) == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
