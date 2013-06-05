from SimpleCV import *
import cv2

i = Image("lenna")
img = i.getNumpyCv2()
shiftimg = cv2.pyrMeanShiftFiltering(img, 10, 15, maxLevel=1)
img1 = Image(shiftimg, cv2image=True)
img1.show()
blobs = img1.findBlobs()
print blobs
b = blobs[-1]
b.draw()
img1.show()
cv2.imshow("image", shiftimg)
cv2.waitKey(0)