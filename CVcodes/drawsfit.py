import cv2
import sys

detector = cv2.FeatureDetector_create("SIFT")
descriptor = cv2.DescriptorExtractor_create("SIFT")

img = cv2.imread(sys.argv[1])
skp = detector.detect(img)

nimg = cv2.drawKeypoints(img, skp)

cv2.imshow("image", img)
cv2.imshow("keypoints", nimg)

cv2.waitKey(0)

cv2.imwrite("siftkeypoints.jpg", nimg)