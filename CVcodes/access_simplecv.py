#Accessing Pixel values (data)
from SimpleCV import *

img = Image("Lenna.png")
rows = img.height
cols = img.width

for i in range(rows):
	for j in range(cols):
		r, g, b = img[i, j]
		print r, g, b