import cv2
import cv2.cv as cv
from scipy.spatial import distance as Dis
from sklearn.cluster import DBSCAN
import numpy as np
import itertools
import sys
class SIFTTracker:
    def __init__(self, source=0, bb=None):
        self.mouse_p1 = None
        self.mouse_p2 = None
        self.mouse_drag = False
        self.bb = None
        self.img = None
        self.source = source
        self.detector = cv2.FeatureDetector_create(sys.argv[1])
        self.descriptor = cv2.DescriptorExtractor_create(sys.argv[1])

        self.flann_params = dict(algorithm=1, trees=4)
        
        if source:
            self.cam = cv2.VideoCapture(source)
        else:
            self.cam = cv2.VideoCapture(0)
        if not bb:
            _, self.img = self.cam.read()
            self.start()
        else:
            self.bb = bb
            _, self.img = self.cam.read()
            self.SIFT()

    def start(self):
        _, self.img = self.cam.read()
        cv2.imshow("img", self.img)
        cv.SetMouseCallback("img", self.__mouseHandler, None)
        if not self.bb:
            _, self.img = self.cam.read()
            cv2.imshow("img", self.img)
            cv2.waitKey(30)
        cv2.waitKey(0)

    def __mouseHandler(self, event, x, y, flags, params):
        _, self.img = self.cam.read()
        if event == cv.CV_EVENT_LBUTTONDOWN and not self.mouse_drag:
            self.mouse_p1 = (x, y)
            self.mouse_drag = True
        elif event == cv.CV_EVENT_MOUSEMOVE and self.mouse_drag:
            cv2.rectangle(self.img, self.mouse_p1, (x, y), (255, 0, 0), 1, 8, 0)
        elif event == cv.CV_EVENT_LBUTTONUP and self.mouse_drag:
            self.mouse_p2 = (x, y)
            self.mouse_drag=False
        cv2.imshow("img",self.img)
        cv2.waitKey(01)
        if self.mouse_p1 and self.mouse_p2:
            cv2.destroyWindow("img")
            xmax = max((self.mouse_p1[0],self.mouse_p2[0]))
            xmin = min((self.mouse_p1[0],self.mouse_p2[0]))
            ymax = max((self.mouse_p1[1],self.mouse_p2[1]))
            ymin = min((self.mouse_p1[1],self.mouse_p2[1]))
            self.bb = [xmin,ymin,xmax-xmin,ymax-ymin]
            self.SIFT()
            #cv2.destroyAllWindows()
            return None

    def SIFT(self):
        #temp = self.img[150:400,200:400]
        old_pts=None
        bb = self.bb
        temp = self.img[bb[1]:bb[1]+bb[3], bb[0]:bb[0]+bb[2]]
        self.tkp, self.td = self.getKeyPoints(temp)
        while True:
            _, img = self.cam.read()
            skp, tkp = self.matchKeyPoints(img, temp)
            print len(skp), "keypoints being matched"
            if len(skp) < 5:
                cv2.imshow("img",img)
                k=cv2.waitKey(30)
                self.img = img
                if (k==27):
                    break
                continue
            bb, new_center = self.__predictBB(bb, old_pts, skp)
            print new_center[0]
            self.bb = bb
            cv2.circle(img, (int(new_center[0][0]), int(new_center[0][1])), 5, (0,0,255), -1)
            cv2.rectangle(img, (bb[0], bb[1]), (bb[0]+bb[2], bb[1]+bb[3]), (255, 0, 0), 2)

            cv2.imshow("img",img)
            k=cv2.waitKey(30)
            self.img = img
            old_pts = skp
            if (k==27):
                break
        cv2.destroyAllWindows()
        return None

    def __predictBB(self, bb, old_pts, new_pts):
        pts = []
        for kp in new_pts:
            pts.append((kp.pt[0], kp.pt[1]))
        np_pts = np.asarray(pts)
        t, pts, new_center = cv2.kmeans(np.asarray(np_pts, dtype=np.float32), K=1, bestLabels=None,
                            criteria=(cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_MAX_ITER, 1, 10), attempts=1, 
                            flags=cv2.KMEANS_RANDOM_CENTERS)
        print new_center

        max_x = int(max(np_pts[:, 0]))
        min_x = int(min(np_pts[:, 0]))
        max_y = int(max(np_pts[:, 1]))
        min_y = int(min(np_pts[:, 1]))

        new_bb =  (min_x-5, min_y-5, max_x-min_x+5, max_y-min_y+5)
        print new_bb
        #new_center[0][0] += new_bb[0]
        #new_center[0][1] += new_bb[1]
        
        return new_bb, new_center

    def getKeyPoints(self, img):
        detector = self.detector
        descriptor = self.descriptor
        skp = detector.detect(img)
        skp, sd = descriptor.compute(img, skp)
        return skp, sd


    def matchKeyPoints(self, img, template, distance=100):
        detector = self.detector
        descriptor = self.descriptor
        dimg = np.copy(img)
        #dtemp = np.copy(template)
        skp = detector.detect(img)
        skp, sd = descriptor.compute(img, skp)

        #tkp = detector.detect(template)
        #tkp, td = descriptor.compute(template, tkp)
        tkp = self.tkp
        td = self.td
        print len(sd)

        matcher = cv2.BFMatcher(cv2.NORM_L2SQR)
        matches = matcher.match(sd, td)
        #flann = cv2.flann_Index(sd, self.flann_params)
        #idx, dist = flann.knnSearch(td, 1, params={})
        #del flann

        distances = [match.distance for match in matches]

        dist = dist[:,0]/2500.0
        dist = dist.reshape(-1,).tolist()
        idx = idx.reshape(-1).tolist()
        indices = range(len(dist))
        indices.sort(key=lambda i: dist[i])
        dist = [dist[i] for i in indices]
        idx = [idx[i] for i in indices]
        skp_final = []
        skp_final_labelled=[]
        data_cluster=[]
        #print skp
        for i, dis in itertools.izip(idx, dist):
            if dis < distance:
                skp_final.append(skp[i])
                data_cluster.append((skp[i].pt[0], skp[i].pt[1]))
        n_data = np.asarray(data_cluster)
        D = Dis.squareform(Dis.pdist(n_data))
        S = 1 - (D/np.max(D))
        area = self.bb[2]*self.bb[3]
        print area, "area"
        if area < 5626:
            eps_val = 0.3
        elif area >= 5625 and area < 10000:
            eps_val = 0.4
        elif area >= 10000 and area < 40000:
            eps_val = 0.5
        elif area >= 40000 and area < 90000:
            eps_val = 0.7
        else:
            eps_val = 0.8
        #eps_val = 0.4
        print eps_val, "eps_val"
        db = DBSCAN(eps=eps_val, min_samples=5).fit(S)
        core_samples = db.core_sample_indices_
        labels = db.labels_
        print len(set(labels))
        print set(labels)
        print len(labels)
        print len(skp_final)
        for label, i in zip(labels, range(len(labels))):
            if label==0:
                cv2.circle(dimg, (int(data_cluster[i][0]), int(data_cluster[i][1])), 3, (255, 0, 0), -1)
                skp_final_labelled.append(skp_final[i])
            else:
                cv2.circle(dimg, (int(data_cluster[i][0]), int(data_cluster[i][1])), 3, (0, 0, 255), -1)
        cv2.imshow("DBSCAN", dimg)
        """
        flann = cv2.flann_Index(td, self.flann_params)
        idx, dist = flann.knnSearch(sd, 1, params={})
        del flann
        """
        """
        dist = dist[:,0]/2500.0
        dist = dist.reshape(-1,).tolist()
        idx = idx.reshape(-1).tolist()
        indices = range(len(dist))
        indices.sort(key=lambda i: dist[i])
        dist = [dist[i] for i in indices]
        idx = [idx[i] for i in indices]
        data_cluster=[]
        tkp_final = []
        tkp_final_labelled = []
        for i, dis in itertools.izip(idx, dist):
            if dis < distance:
                tkp_final.append(tkp[i])
                data_cluster.append((tkp[i].pt[0], tkp[i].pt[1]))
        n_data = np.asarray(data_cluster)
        D = Dis.squareform(Dis.pdist(n_data))
        S = 1 - (D/np.max(D))

        db = DBSCAN(eps=2.4, min_samples=10).fit(S)
        core_samples = db.core_sample_indices_
        labels = db.labels_
        print len(set(labels))
        print set(labels)
        print len(labels)
        print len(tkp_final)
        for label, i in zip(labels, range(len(labels))):
            #print data_cluster[i]
            if label==0:
                cv2.circle(dtemp, (int(data_cluster[i][0]), int(data_cluster[i][1])), 3, (255, 0, 0), -1)
                tkp_final_labelled.append(tkp_final[i])
            else:
                cv2.circle(dtemp, (int(data_cluster[i][0]), int(data_cluster[i][1])), 3, (0, 0, 255), -1)
        #cv2.imshow("DBSCAN-temp", dtemp)
        #cv2.waitKey(0)
        """
        tkp_final_labelled = []
        return skp_final_labelled, tkp_final_labelled

#s=SIFTTracker(source="/home/jay/Python/SimpleCV/vid3.mp4")
#s=SIFTTracker(source="test.avi")
s=SIFTTracker()
