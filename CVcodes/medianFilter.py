import cv2
import numpy as np
import sys

def medianFilter():
    img = cv2.imread("Lenna.png")
    gray = cv2.cvtColor(img, cv2.cv.CV_BGR2GRAY)
    img_filter = np.copy(gray)
    for i in range(1, img_filter.shape[0]-1):
        for j in range(1, img_filter.shape[1]-1):
            img_filter[i,j] = np.median(img_filter[i-1:i+2, j-1:j+2])

    cv2.imshow("Noise", gray)
    cv2.imshow("filtered", img_filter)
    cv2.waitKey(0)

medianFilter()

# As an exercise, try to implement media Filter on a colored image, 
# instead of gray image.
