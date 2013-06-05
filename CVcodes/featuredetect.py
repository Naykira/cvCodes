import cv2
import numpy as np
import time
t=time.time()
imgname="Lenna"
codec=".png"
img = cv2.imread(imgname+codec)
img_harris = np.copy(img)
#img = cv2.resize(img, (img.shape[0]/2, img.shape[1]/2))
blur = cv2.GaussianBlur(img, (3, 3), 0)
gray = cv2.cvtColor(blur, cv2.cv.CV_BGR2GRAY)

Ix = cv2.Sobel(gray, cv2.CV_32F, 1, 0)
Iy = cv2.Sobel(gray, cv2.CV_32F, 0, 1)

Ix_Ix = np.multiply(Ix, Ix)
Iy_Iy = np.multiply(Iy, Iy)
Ix_Iy = np.multiply(Ix, Iy)

Ix_Ix_blur = cv2.GaussianBlur(Ix_Ix, (5, 5), 0)
Iy_Iy_blur = cv2.GaussianBlur(Iy_Iy, (5, 5), 0)
Ix_Iy_blur = cv2.GaussianBlur(Ix_Iy, (5, 5), 0)
print time.time()-t
thresh = 5000
harris_thresh = thresh*5000
alpha = 0.06
"""
for i in xrange (Ix.shape[1]):
	for j in xrange(Ix.shape[0]):
		#A = np.array([ [Ix_Ix_blur[i][j], Ix_Iy_blur[i][j]], 
		#	[Ix_Iy_blur[i][j], Iy_Iy_blur[i][j]] ])
		A = np.array([ [Ix_Ix_blur[j][i], Ix_Iy_blur[j][i]], 
			[Ix_Iy_blur[j][i], Iy_Iy_blur[j][i]] ])
		detA = (A[0][0]*A[1][1])-(A[0][1]*A[1][0])
		traceA = A[0][0]+A[1][1]

		harmonic_mean = detA/traceA
		#print harmonic_mean
		if(harmonic_mean > thresh):
			cv2.circle(img, (i,j), 1, (0, 0, 255), -1, 8)
#img = cv2.resize(img, (img.shape[0]*2, img.shape[1]*2))
"""
"""
Ix_Iy_blur_iter = np.nditer(Ix_Iy_blur)
Iy_Iy_blur_iter = np.nditer(Iy_Iy_blur)
Ix_Ix_blur_iter = np.nditer(Ix_Ix_blur)

while(not Ix_Iy_blur_iter.finished):
	try:
		A = np.array([[Ix_Ix_blur_iter.next(), Ix_Iy_blur_iter.next()], [Ix_Iy_blur_iter.value, Iy_Iy_blur_iter.next()]])
	except StopIteration:
		#print Ix_Ix_blur_iter.iterindex, Iy_Iy_blur_iter.iterindex, Ix_Iy_blur_iter.iterindex
		break
	detA = (A[0][0]*A[1][1])-(A[0][1]*A[1][0])
	traceA = A[0][0]+A[1][1]

	harmonic_mean = detA/traceA
	#print harmonic_mean
	if(harmonic_mean > thresh):
		i = Ix_Ix_blur_iter.iterindex/Ix.shape[0]
		j = Ix_Ix_blur_iter.iterindex - Ix.shape[0]*i
		cv2.circle(img, (j,i), 1, (0, 0, 255), -1, 8)
"""

detA = Ix_Ix_blur * Iy_Iy_blur - Ix_Iy_blur**2
traceA = Ix_Ix_blur + Iy_Iy_blur
harmonic_mean = detA / traceA
for j, i in np.argwhere(harmonic_mean > thresh):
    cv2.circle(img, (i,j), 1, (0, 0, 255), -1, 8)
harris_function = detA - (alpha*traceA*traceA)
for j,i in np.argwhere(harris_function > harris_thresh):
	cv2.circle(img_harris, (i,j), 1, (0, 0, 255), -1, 8)
print time.time()-t
cv2.imshow("img", img)
cv2.imshow("harris", img_harris)
#cv2.imwrite(imgname+"harris_corners.png", img_harris)
#cv2.imwrite(imgname+"szeliski_img.png", img)
cv2.waitKey(0)