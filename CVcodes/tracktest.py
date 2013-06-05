from SimpleCV import *
 
#cam = VirtualCamera("/Users/mjm/Projects/python/simplecv/blobber/traffic.mov", "video")
cam = VirtualCamera("/home/jay/out-12.ogv","video")
#cam = Camera()
display = Display()
trackingsets = []
 
while display.isNotDone():
    if display.mouseLeft:
        break
 
    img = cam.getImage().scale(0.5)
 
    # first time round
    if not trackingsets:
        print "Find Blobs"
        blobs = img.findBlobs(threshval=-1, minsize=1000)
        if blobs is None:
            continue
        for blob in blobs:
            blob.draw(color=(255,0,0))
            bb = blob.boundingBox()
            print bb
            # bb = tuple(bb) # workaround
            img.dl().rectangle((bb[0],bb[1]),(bb[2],bb[3]),color=(255,0,0))
            ts = img.track("camshift",img=img, bb=bb, num_frames=5, nframes=20, lower=(100, 40, 40), upper=(180, 250, 250))
            print ts[-1].bb
            trackingsets.append(ts)
        print "Newly found sets: ", len(trackingsets)
    else:
        print "Tracking sets"
        new_trackingsets = []
        for ts in trackingsets:
            new_ts = img.track("camshift",ts=ts,lower=(100, 40, 40), upper=(180, 250, 250))
            vel = new_ts.pixelVelocity()[-1]
            velsqr = np.square(vel).sum()  # squared length
            print new_ts[-1].bb
            a = new_ts[-1].area
            # only use trackers that are not too small or big and those that are moving
            if (a>10000) and (a<100000) and (velsqr>25):
                new_trackingsets.append(new_ts)
        trackingsets = new_trackingsets
 
    print len(trackingsets)
 
    for ts in trackingsets:
        ts.drawBB()
        ts.drawPath()
 
    img.show()