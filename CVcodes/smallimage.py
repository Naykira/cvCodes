from SimpleCV import *
import numpy as np
import time
i = Image("lenna")
img = i.resize(60, 60)
#img = Image("filename")
w, h = img.size()

nw, nh = 10*w, 10*h
t = time.time()
nimg = Image((nw, nh))
for i in xrange(w):
    for j in xrange(h):
        for k in xrange(i*10, (i+1)*10):
            for l in xrange(j*10, (j+1)*10):
                nimg[k, l] = img[i, j]
print (time.time() - t)*1000
t = time.time()
p = np.zeros((nw, nh, 3), dtype=np.uint8)
for i in xrange(w):
    for j in xrange(h):
        p[i*10:(i+1)*10, j*10:(j+1)*10] = img[i, j]*np.ones((10, 10, 3))
nimg = Image(p)
print (time.time() - t)*1000

p = np.ones((nw, nh, 3), dtype=np.uint8)
for i in xrange(w):
    for j in xrange(h):
        p[i*10:(i+1)*10, j*10:(j+1)*10] *= img[i, j]
nimg = Image(p)
print (time.time() - t)*1000
nimg.save("np1.png")
t = time.time()
p = np.ones((nw, nh, 3), dtype=np.uint8)
c = img.getNumpy()
for i in xrange(h):
    r = (a*np.ones((10,3), np.uint8) for a in c[:, i, :])
    j=0
    while True:
        try:
            a = r.next()
            for k in xrange(i*10, (i+1)*10):
                p[j*10:(j+1)*10,k,:] = a   
            j+=1
        except StopIteration:
            break
nimg = Image(p)
print (time.time()-t)*1000

t = time.time()
p = np.ones((nw, nh, 3), dtype=np.uint8)
c = img.getNumpy()
for i in xrange(h):
    r = (a*np.ones((10,3), np.uint8) for a in c[:, i, :])
    j=0
    while True:
        try:
            a = r.next()
            b = np.dstack((a, a))
            o = np.dstack((b, b))
            for k in xrange(3):
                o = np.dstack((o, b))
            p[j*10:(j+1)*10,i*10:(i+1)*10,:] = np.swapaxes(o, 1, 2)
            j+=1
        except StopIteration:
            break
nimg = Image(p)
print (time.time()-t)*1000

nimg.show()
nimg.save("gen1.png")