import cv2
import numpy as np
import sys

img = cv2.imread(sys.argv[1])
gray = cv2.cvtColor(img, cv2.cv.CV_BGR2GRAY)

sobel_filter_x = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]])
sobel_filter_y = np.transpose(sobel_filter_x)

img_filter_x = cv2.filter2D(gray, -1, sobel_filter_x)
img_filter_y = cv2.filter2D(gray, -1, sobel_filter_y)

cv2.imshow("X_derivative", img_filter_x)
cv2.imshow("Y_derivative", img_filter_y)
cv2.waitKey(0)