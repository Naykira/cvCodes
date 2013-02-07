from SimpleCV import *
import time

def load_image():
	img = Image("lenna")
	img.toGray().show()
	time.sleep(5)
	img.toHLS().show()
	time.sleep(5)
	img.toRGB().show()
	time.sleep(5)

load_image()