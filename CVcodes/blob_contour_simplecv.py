from SimpleCV import *
import sys
import time

img = Image(sys.argv[1])
blobs = img.findBlobs(threshval=50)

for blob in blobs:
    blob.draw()
    img.show()
    time.sleep(3)
print len(blobs)

