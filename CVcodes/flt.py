import time
from SimpleCV import *
import numpy as np

img = Image("lenna")
t = time.time()
img.applyGaussianFilter()
print time.time() - t

t = time.time()
w,h = img.size()
dia = 400
dia = int(dia/((w/64.0+h/64.0)/2.0))
X, Y = np.meshgrid(np.arange(64), np.arange(64))
D = np.sqrt((X-32)**2+(Y-32)**2)
filt = 255.0*np.exp(-0.5*(D/dia)**2)
flt = Image(filt)
flt_re = flt.resize(w, h) 
newimg=img.applyDFTFilter(flt_re, grayscale=False)
print time.time() - t

t = time.time()
w, h = img.size()
dia = 400
X, Y = np.meshgrid(np.arange(w), np.arange(h))
D = np.sqrt((X-w/2)**2+(Y-h/2)**2)
filt = 255.0*np.exp(-0.5*(D/dia)**2)
flt = Image(filt)
newimg=img.applyDFTFilter(flt_re, grayscale=False)
print time.time() - t
