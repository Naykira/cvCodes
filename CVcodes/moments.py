import cv2
import sys
import numpy as np

img = cv2.imread(sys.argv[1])
threshimg = cv2.inRange(img, np.array([250, 10, 0]), np.array([255, 15, 0]))
mu = cv2.moments(threshimg)
mc = (mu["m10"]/mu["m00"], mu["m01"]/mu["m00"])

cv2.circle(img, (int(mc[0]), int(mc[1])), 3, (0, 0, 255), -1, 8, 0)

cv2.imshow("image", img)
cv2.imshow("thresh", threshimg)

cv2.waitKey(0)