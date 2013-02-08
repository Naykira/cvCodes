import cv2
import numpy as np
import sys

img = cv2.imread(sys.argv[1])
gray = cv2.cvtColor(img, cv2.cv.CV_BGR2GRAY)

blur = cv2.GaussianBlur(gray, (5, 5), 0)
img_filter = 2*gray - blur

cv2.imshow("gray", gray)
cv2.imshow("filter", img_filter)
cv2.waitKey(0)