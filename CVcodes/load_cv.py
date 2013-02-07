import cv2

# Read Image
img = cv2.imread("Lenna.png")
# img - Numpy Array

# Display Image
cv2.imshow("image", img)

cv2.waitKey(0)