#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    Mat img, gray, blur, canny_img;
    img = imread(argv[1]);
    cvtColor(img, gray, CV_BGR2GRAY);
    GaussianBlur(gray, blur, Size(3, 3), 0);

    int thresh = 100;
    Canny(blur, canny_img, thresh, thresh*2, 3);

    imshow("image", img);
    imshow("Canny", canny_img);

    waitKey(0);
    return 0;
}