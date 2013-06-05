#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

Mat drawBoundingBoxes (Mat canvasImage, vector<vector<Point> > contours);

int main(int argc, char* argv[])
{
    Mat frame;
    Mat back;
    Mat fGround;
    BackgroundSubtractorMOG2 bGround;
    //bGround.nmixtures = 3;
    //bGround.nShadowDetection = 0;
    //bGround.fTau = .5;

    VideoCapture cap;
    cap.open(argv[1]);
    if (!cap.isOpened())
    {
        cout << "Can't open video" << endl;
        return -1;
    }

    vector<vector<Point> > contours;
    namedWindow("video", CV_WINDOW_AUTOSIZE);

    while (true)
    {
        static int count = 1;
        cap >> frame;
        if (frame.empty())
            break;

        bGround.operator()(frame, fGround);
        bGround.getBackgroundImage(back);
        erode(fGround, fGround, Mat(), Point(-1,-1), 2, BORDER_DEFAULT);
        dilate(fGround, fGround, Mat(), Point(-1,-1), 10, BORDER_DEFAULT);

        if (count > 50)
        {
            findContours(fGround, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
            drawContours(frame, contours, -1, Scalar(239,255,0), 2);
            drawBoundingBoxes(frame, contours);
        }

        imshow("video", frame);

        if(waitKey(30) >= 0) 
            break;
        count++;
    }
    return 0;
}

Mat drawBoundingBoxes (Mat canvasImage, vector<vector<Point> > contours)
{
    vector<Rect> boundRect(contours.size());

    for (int i=0; i<contours.size(); i++)
    {
        boundRect[i] = boundingRect(contours[i]);
        rectangle(canvasImage, boundRect[i], Scalar(153,0,76), 2, 8, 0);
    }
    return canvasImage;
}