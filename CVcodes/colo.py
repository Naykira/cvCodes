from SimpleCV import *
import cv2

i = Image("lenna") #HSV image
img = i.getNumpyCv2() #Get cv2 image (numpy array)
img = cv2.cvtColor(img, cv2.cv.CV_BGR2HSV)
cv2.imshow("image", img)
cv2.waitKey(0)
cv2.imwrite("getnumpycv2.png", img)
