import cv2
import sys
import numpy as np

img = cv2.imread(sys.argv[1])
gray = cv2.cvtColor(img, cv2.cv.CV_BGR2GRAY)
blur = cv2.GaussianBlur(gray, (3, 3), 0)

thresh=100

canny_img = cv2.Canny(blur, threshold1=thresh, 
            threshold2=thresh*2, apertureSize=3)
contours, hierarchy = cv2.findContours(np.copy(canny_img), cv2.RETR_EXTERNAL, 
                    cv2.CHAIN_APPROX_NONE)
drawing = np.zeros(img.shape)
for i in range(len(contours)):
    cv2.drawContours(drawing, contours, i, (0, 0, 255), 1, 8, hierarchy=hierarchy)

cv2.imshow("image", img)
cv2.imshow("contours", drawing)

cv2.waitKey(0)