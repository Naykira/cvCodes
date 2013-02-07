# Thresholding Image
from SimpleCV import *
import sys

img = Image(sys.argv[1])
threshval = int(sys.argv[2])

thresh = img.threshold(threshval)

thresh.show()