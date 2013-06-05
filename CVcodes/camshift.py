from SimpleCV import *
import time

def foo(image):
    return image.meanColor()

def camshift():
    cam = VirtualCamera("/home/jay/Python/SimpleCV/vid3.mp4","video")
    vs = VideoStream("ball.avi",18,False)
    img = cam.getImage()
    d = Display(img.size())
    bb1 = getBBFromUser(cam,d)
    bb2 = getBBFromUser(cam,d)
    fs1=[]
    fs2=[]
    while True:
        try:
            img1 = cam.getImage()
            fs1 = img1.track("camshift",fs1,img,bb1,num_frames=5, nframes=60)
            fs2 = img1.track("camshift",fs2,img,bb2,num_frames=5, nframes=60)
            fs1.draw(Color.ORANGE, rad=5, thickness=-1)
            fs2.draw(Color.ORANGE, rad=5, thickness=-1)
            fs1.drawBB()
            fs2.drawBB()
            fs1.drawPredicted(Color.BLUE, rad=5, thickness=-1)
            fs2.drawPredicted(Color.BLUE, rad=5, thickness=-1)
            fs1.drawCorrected(Color.RED, rad=5, thickness=-1)
            fs2.drawCorrected(Color.RED, rad=5, thickness=-1)
            img1.show()
            time.sleep(0.03)
            img1.save(vs)
            print fs1[-1].x, fs1[-1].y
            print fs1[-1].predict_pt
            print fs1[-1].state_pt
        except KeyboardInterrupt:
            print "Total number of frames tracked",
            print fs1.trackLength()
            print fs1.processTrack(foo)
            break

def getBBFromUser(cam, d):
    p1 = None
    p2 = None
    img = cam.getImage()
    while d.isNotDone():
        try:
            #img = cam.getImage()
            img.save(d)
            dwn = d.leftButtonDownPosition()
            up = d.leftButtonUpPosition()
            
            if dwn:
                p1 = dwn
            if up:
                p2 = up
                break

            time.sleep(0.05)
        except KeyboardInterrupt:
            break
    if not p1 or not p2:
        return None
    
    xmax = np.max((p1[0],p2[0]))
    xmin = np.min((p1[0],p2[0]))
    ymax = np.max((p1[1],p2[1]))
    ymin = np.min((p1[1],p2[1]))
    return (xmin,ymin,xmax-xmin,ymax-ymin)
    
camshift()
