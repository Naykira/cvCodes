from SimpleCV import *
from time import time
import numpy as np

i = Image("lenna")

a = i.getLineScan(x=40)

t = time()
mean = sum(a) / len(a)
print (time() - t)*1000

t = time()
sd = sqrt(sum((x-mean)**2 for x in a) / len(a))
print (time() - t)*1000

t = time()
l = np.array(a)
mean = np.mean(l)
print (time() - t)*1000

del l

t = time()
l = np.array(a)
mean = np.std(l)
print (time() - t)*1000