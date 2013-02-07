# Thresholding Image
from cv2 import *
from cv2.cv import *
import sys

print sys.argv

img = imread(sys.argv[1])
gray = cvtColor(img, CV_BGR2GRAY)

threshval = int(sys.argv[2])
maxval = int(sys.argv[3])

retval, thresh = threshold(gray, threshval, 
	                       maxval, THRESH_BINARY)
imshow("threshold", thresh);
waitKey(0)