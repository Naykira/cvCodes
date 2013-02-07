#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    Mat img, threshimg;
    img = imread(argv[1]);
    inRange(img, Scalar(250, 10, 0), Scalar(255, 15, 0), threshimg);

    Moments mu;
    Point2f mc;
    mu = moments(threshimg);

    mc = Point2f(mu.m10/mu.m00, mu.m01/mu.m00);

    circle(img, Point(int(mc.x), int(mc.y)), 3, Scalar(0, 0, 255), -1, 8, 0);

    imshow("image", img);
    imshow("thresh", threshimg);

    waitKey(0);
    return(0);
}
