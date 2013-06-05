import cv2
import numpy as np
import mftracker
import sys
import cv2.cv as cv
from SimpleCV import *
cas = cv2.CascadeClassifier("/home/jay/Git/SimpleCV/SimpleCV/Features/HaarCascades/face.xml")
cap = cv2.VideoCapture(0)

_, img = cap.read()
_, img = cap.read()
del cap
gray = cv2.cvtColor(img, cv2.cv.CV_BGR2GRAY)
rects = cas.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=3, minSize=(10, 10), flags = cv.CV_HAAR_SCALE_IMAGE)
#rects = cas.detectMultiScale(image=gray,scaleFactor=1.1,minNeighbours=3,flags=cv.CV_HAAR_SCALE_IMAGE,
#                            minSize=(10, 10))
print rects
if rects is None:
    print "No faces found."
    sys.exit(1)
for rect in rects:
    print rect
    cv2.rectangle(img, (rect[0], rect[1]), (rect[0]+rect[2], rect[1]+rect[3]), (255, 0, 0), 3)
cv2.imshow("faces", img)

mftracker.mftrack(0, rect.tolist())
"""
ts = []
cam = Camera()
img0 = cam.getImage()
display = Display()
bb = tuple(rect.tolist())
while display.isNotDone:
    img = cam.getImage()
    ts = img.track("camshift", ts, img0, bb)
    ts.drawBB()
    img.show()
"""
