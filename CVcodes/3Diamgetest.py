from SimpleCV import *
import cv2
import cv2.cv as cv
import time
"""
cam1 = Camera(1)
cam2 = Camera(2)

l = cam1.getImage()
r = cam2.getImage()

s = StereoImage(l, r)
state= {"minDisparity":0}
Q=cv.Load("/home/jay/Q_mat.yml")

while True:
    l = cam1.getImage()
    r = cam2.getImage()
    s = StereoImage(l, r)
    img = s.get3DImage(Q)
    img.show()

    cv2.imshow("depth", s.Image3D)
    k=cv2.waitKey(30)
    if k ==27:
        break


img.save("stereo3d.jpg")
l.save("stereol.jpg")
r.save("stereor.jpg")
print "SGBM"
img = s.get3DImage(Q, "SGBM")
img.show()
cv2.imshow("depth", s.Image3D)

cv2.waitKey(0)
"""
Q=cv.Load("/home/jay/Q_mat.yml")
s = StereoCamera()
s.get3DImage(1, 2, Q).show()
s.get3DImage(1, 2, Q).show()
s.get3DImage(1, 2, Q).show()
