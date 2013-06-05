import cv2
import numpy as np
import sys
img = cv2.imread('cricball.jpeg')
cap = cv2.VideoCapture(sys.argv[1])
while True:
    _, img = cap.read()
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
#ret,thresh = cv2.threshold(gray,0,255,cv2.THRESH_OTSU)
    thresh = cv2.inRange(gray, np.array([0, 30, 30]), np.array([20, 80, 80]))
    size = 3
    kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (2*size+1, 2*size+1))
    er = cv2.erode(thresh, kernel)
    di = cv2.dilate(er, kernel)

    cv2.imshow("iamge", img)
    cv2.imshow("thresh", thresh)
    cv2.imshow("erode", er)
    cv2.imshow("dialte", di)
    k=cv2.waitKey(0)
    if k==27:
        break