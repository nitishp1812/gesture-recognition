from glob import glob

import numpy as np
import cv2
from sklearn.model_selection import train_test_split

def load_images():
    images = glob("images/*/*.jpeg")
    images.sort()

    x = list()
    y = list()

    for i in range(36):
        label = i
        num_imgs = 0
        if i == 29:
            num_imgs = 65
        else:
            num_imgs = 70
        for j in range(num_imgs):
            index = (i * 70) + j
            if i > 29:
                index -=  5
            img = np.array(cv2.imread(images[index]), dtype=np.uint8)
            x.append(process_image(img))
            y.append(label)

    x = np.array(x)
    y = np.array(y)
    z = np.zeros((y.size, y.max() + 1))
    z[np.arange(y.size), y] = 1
    y = z
    x = np.reshape(x, (x.shape[0], x.shape[1], x.shape[2], 1))

    x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2, shuffle=True)
    x_train, x_val, y_train, y_val = train_test_split(x_train, y_train, test_size=0.25, shuffle=True)

    print("loaded all images")
    
    return x_train, x_val, x_test, y_train, y_val, y_test

def process_image(img):
    hsv_img = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    skin_img = cv2.inRange(hsv_img, (0, 30, 60), (20, 150, 255))
    dilated_img = cv2.dilate(skin_img, cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3), (1, 1)), iterations=2,)
    blurred_img = cv2.GaussianBlur(dilated_img, (5, 5), 100)
    processed_img = np.array(cv2.resize(blurred_img, (224, 224)))
    return processed_img
