#Accessing Pixel values (data)
import cv2

img = cv2.imread("Lenna.png")

rows, cols, layers = img.shape
for i in range(rows):
	for j in range(cols):
		b, g, r = img[i, j]
		print r, g, b