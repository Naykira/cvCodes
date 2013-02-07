from SimpleCV import *

def load_image():
	img = Image("Lenna.png")

	# convert BGR image to grayscale image
	gray = img.toGray()
	
	gray.show()

load_image()
