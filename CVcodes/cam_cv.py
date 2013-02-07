import cv2
def from_cam():
	cap = cv2.VideoCapture(0)
	val, img = cap.read()
	if val:
		cv2.imshow("camera", img)
		cv2.waitKey(0)
	else:
		print "Your camera is not working"

def from_file():
	cap = cv2.VideoCapture("MotoGP - Awesome Last Lap.wmv")
	val, img = cap.read()
	if val:
		cv2.imshow("video frame", img)
		cv2.waitKey(0)
	else:
		print "Can not read file"

def video_cam():
	cap = cv2.VideoCapture(0)
	val, img = cap.read()
	if not val:
		return None
	while True:
		val, img = cap.read()
		cv2.imshow("video", img)
		k = cv2.waitKey(30)
		if k == 27:
			break

def video_file():
	cap = cv2.VideoCapture("MotoGP - Awesome Last Lap.wmv")
	val, img = cap.read()
	if not val:
		return None
	while True:
		val, img = cap.read()
		cv2.imshow("video", img)
		k = cv2.waitKey(30)
		if k == 27:
			break
			
from_cam()
from_file()
video_cam()
video_file()
