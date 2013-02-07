import cv2

def load_image():
    img = cv2.imread("Lenna.png")

    # convert BGR image to grayscale image
    gray = cv2.cvtColor(img, cv2.cv.CV_BGR2GRAY)

    cv2.imshow("image", gray)
    cv2.waitKey(0)
    
def load_gray():

	# Read image as grayscale image
    img = cv2.imread("Lenna.png", 
    	            cv2.CV_LOAD_IMAGE_GRAYSCALE)

    cv2.imshow("image", img)
    cv2.waitKey(0)
    
load_image()
load_gray()
