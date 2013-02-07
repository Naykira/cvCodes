#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/features2d/features2d.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    Mat img, out;
    vector< vector <Point> > contours;
    vector< vector <Point> > approxContours;
    img = imread(argv[1]);

    SimpleBlobDetector::Params params;
    
    //params.minDistBetweenBlobs = 50.0f;
    params.minThreshold = 40;
    params.maxThreshold = 100;
    params.thresholdStep = 5;

    params.minArea = 100; 
    params.minConvexity = 0.3;
    params.minInertiaRatio = 0.01;

    params.maxArea = 8000;
    params.maxConvexity = 10;

    params.filterByColor = false;
    params.filterByCircularity = false;

    SimpleBlobDetector blob_detector(params);
    blob_detector.create("SimpleBlob");

    vector<KeyPoint> keypoints;
    blob_detector.detect(img, keypoints);

    drawKeypoints(img, keypoints, out, Scalar(0,255,0), DrawMatchesFlags::DEFAULT);

    for (int i=0; i<keypoints.size(); i++)
    {
        float X=keypoints[i].pt.x; 
        float Y=keypoints[i].pt.y;

        circle(img, Point(int(X), int(Y)), keypoints[i].size/2, Scalar(0, 0, 255), -1, 8, 0);
    }

    imshow("image", img);
    imshow("blobs", out);
    waitKey(0);

    return(0);
}

