import cv2
from scipy.ndimage import gaussian_filter
import numpy as np
import time
from SimpleCV import *

img = cv2.imread("Lenna.png")
t=time.time()
newimg = np.zeros(img.shape)
newimg[:,:,0] = gaussian_filter(img[:,:,0], 5)
newimg[:,:,1] = gaussian_filter(img[:,:,1], 5)
newimg[:,:,2] = gaussian_filter(img[:,:,2], 5)
newimg = newimg.astype(np.uint8)
print time.time() - t
cv2.imshow("image", img)
cv2.imshow("gaussian", newimg)
cv2.waitKey(0)


i = Image("Lenna.png")
t=time.time()
im = i.applyGaussianFilter(300)
print time.time() - t
im.show()
time.sleep(4)
