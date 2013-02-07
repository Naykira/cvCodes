import cv2

def dilate_image():
	img = cv2.imread("Lenna.png")
	size = 4
	kernel = cv2.getStructuringElement(cv2.MORPH_CROSS, (2*size+1, 2*size+1))
	fin_img = cv2.dilate(img, kernel)
	cv2.imshow("dialte",fin_img)
	cv2.waitKey(0)
	
def erode_image():
	img = cv2.imread("Lenna.png")
	size = 4
	kernel = cv2.getStructuringElement(cv2.MORPH_CROSS, (2*size+1, 2*size+1))
	fin_img = cv2.erode(img, kernel)
	cv2.imshow("dialte",fin_img)
	cv2.waitKey(0)
	
dilate_image()
erode_image()
