#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    Mat img, gray, blur, canny_img, drawing;
    img = imread(argv[1]);
    cvtColor(img, gray, CV_BGR2GRAY);
    GaussianBlur(gray, blur, Size(3, 3), 0);

    int thresh = 100;
    Canny(blur, canny_img, thresh, thresh*2, 3);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    drawing = Mat::zeros(canny_img.size(), CV_8UC3);
    findContours(canny_img, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
    printf("%ld contours\n", contours.size());
    for (int i=0; i<contours.size(); i++)
    {
        drawContours(drawing, contours, i, Scalar(0, 0, 255), 2, 8, hierarchy, 0, Point());
    }
    imshow("image", img);
    imshow("contours", drawing);
    waitKey(0);

    return(0);
}