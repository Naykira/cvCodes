import cv2
import sys
import numpy as np

img = cv2.imread(sys.argv[1])
params = cv2.SimpleBlobDetector_Params()

params.minThreshold = 40
params.maxThreshold = 100
params.thresholdStep = 5
params.minArea = 100
params.minConvexity = 0.3
params.minInertiaRatio = 0.01
params.maxArea = 8000
params.maxConvexity = 10
params.filterByColor = False
params.filterByCircularity = False

blobDetector = cv2.SimpleBlobDetector(params)

keypoints = blobDetector.detect(img)
out = np.copy(img)
cv2.drawKeypoints(img, keypoints, out, (0, 0, 255))
for i in range(len(keypoints)):
    cv2.circle(img, (int(keypoints[i].pt[0]), int(keypoints[i].pt[1])), int(keypoints[i].size/2), (0, 0, 255), -1, 8, 0)

cv2.imshow("image", img)
cv2.imshow("blobs", out)
cv2.waitKey(0)
