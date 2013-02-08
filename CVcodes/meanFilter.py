import cv2
import sys
import numpy as np

img = cv2.imread(sys.argv[1])
gray = cv2.cvtColor(img, cv2.cv.CV_BGR2GRAY)

mean_filter = np.ones((5, 5))/25.0

filtered_img_gray = cv2.filter2D(gray, -1, mean_filter)
filtered_img = cv2.filter2D(img, -1, mean_filter)
cv2.imshow("gray", gray)
cv2.imshow("filtered", filtered_img)
cv2.imshow("image", img)
cv2.imshow("filtered_gray", filtered_img_gray)

cv2.waitKey(0)