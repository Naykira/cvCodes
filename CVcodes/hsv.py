from cv2 import *
i=imread("Lenna.png")
imshow("image",i)
h=cvtColor(i, cv.CV_BGR2HSV)
imshow("hsv",h)
waitKey(0)
