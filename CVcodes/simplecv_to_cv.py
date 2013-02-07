# OpenCV image(cv2 - numpy.ndarray) to 
# SimpleCV image(SimpleCV.ImageClass.Image)
# and vice versa

from SimpleCV import *
import cv2

def simplecv_to_cv2():
	img = Image("Lenna.png")

	cv2_img = img.getNumpyCv2()
	cv2_img_gray = img.getGrayNumpyCv2()

	cv2.imshow("img", cv2_img)
	cv2.imshow("cv_img_gray", cv2_img_gray)

	cv2.waitKey(0)
	cv2.destroyAllWindows()

def cv2_to_simplecv():
	img = cv2.imread("Lenna.png")

	simplecv_img = Image(img)
	simplecv_img.show()
	time.sleep(5)

	simplecv_img = Image(img, cv2image=True)
	simplecv_img.show()
	time.sleep(5)

simplecv_to_cv2()
cv2_to_simplecv()
