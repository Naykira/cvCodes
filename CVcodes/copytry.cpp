#include "opencv2/core/core.hpp"
#include "stdio.h"
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
int main()
{
    Mat img1, img2;
    img1 = imread("Lenna.png");
    img2 = img1(Rect(10, 20, 200, 200));

    imshow("copy", img2);
    waitKey(0);
}