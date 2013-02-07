import cv2
import cv2.cv as cv
from cv import *
import sys
import numpy as np

PI_BY_8 =  0.39286
PI_BY_4 =  0.78571
PI_BY_2 =  1.57142
PI =  3.14285

orig_img = cv2.imread(sys.argv[1])
gray = cv2.cvtColor(orig_img, cv2.cv.CV_BGR2GRAY)

Ix = cv2.Sobel(gray, cv2.CV_32F, 1, 0)
Iy = cv2.Sobel(gray, cv2.CV_32F, 0, 1)

magnitude = (Ix**2+Iy**2)**0.5
tan_inverse = np.arctan2(Iy, Ix)
direction = np.zeros(Ix.shape)

for i, j in np.argwhere(tan_inverse > 3*PI_BY_8):
    direction[i,j] = 2

for i, j in np.argwhere(tan_inverse < -3*PI_BY_8):
    direction[i,j] = 2

for i, j in np.argwhere(tan_inverse > PI_BY_8):
    direction[i,j] = 1

for i, j in np.argwhere(tan_inverse < -PI_BY_8):
    direction[i,j] = 3

r_np = np.arange(1, Ix.shape[0]-1)

i_np = np.empty((Ix.shape[0]-2, Ix.shape[1]-2))
j_np = np.empty((Ix.shape[0]-2, Ix.shape[1]-2))
for i in range(Ix.shape[0]-2):
    i_np[:,i] = r_np
    j_np[i,:] = r_np

temp = direction[1:-1,1:-1]

neighbor_plus_x = np.array([0, 1, 1, 1])
neighbor_plus_x_np = np.zeros(temp.shape)
neighbor_plus_x_np[0:4,0] = neighbor_plus_x
neighbor_plus_y = np.array([1, -1, 0, 1])
neighbor_minus_x = np.array([0, -1, -1, -1])
neighbor_minus_y = np.array([-1, 1, 0, -1])
print i_np.shape, neighbor_plus_x_np.shape, temp.shape
index_x = i_np + neighbor_plus_x_np[temp]