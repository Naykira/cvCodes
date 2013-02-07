from SimpleCV import *
import time

def from_cam():
	cam = Camera()
	img = cam.getImage()
	img.show()
	time.sleep(2)

def from_file():
	cam = VirtualCamera("MotoGP - Awesome Last Lap.wmv", "video")
	img = cam.getImage()
	img.show()
	time.sleep(2)

def video_cam():
	cam = Camera()
	while True:
		try:
			img = cam.getImage()
			img.show()
			time.sleep(0.3)
		except KeyboardInterrupt:
			break

def video_file():
	cam = VirtualCamera("MotoGP - Awesome Last Lap.wmv", "video")
	while True:
		try:
			img = cam.getImage()
			img.show()
			time.sleep(0.3)
		except KeyboardInterrupt:
			break
	del cam

from_cam()
from_file()
#video_cam()
#video_file()