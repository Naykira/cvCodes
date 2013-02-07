import cv2
import sys

img = cv2.imread(sys.argv[1])
gray = cv2.cvtColor(img, cv2.cv.CV_BGR2GRAY)
blur = cv2.GaussianBlur(gray, (3, 3), 0)

thresh=100

canny_img = cv2.Canny(blur, threshold1=thresh, 
                    threshold2=thresh*2, apertureSize=3)

cv2.imshow("image", img)
cv2.imshow("canny", canny_img)

cv2.waitKey(0)