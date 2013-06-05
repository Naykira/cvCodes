#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
using namespace cv;
using namespace std;

int main()
{
    VideoCapture cap1 = VideoCapture(1);
    VideoCapture cap2 = VideoCapture(2);

    int k;
    Mat img1, img2;
    while (1)
    {
        cap1 >> img1;
        cap2 >> img2;

        //flip(img2, img2,0);
        //flip(img2, img2, 1);

        imshow("cam 1", img1);
        imshow("cam 2", img2);
        imwrite("l1.jpg", img1);
        imwrite("r1.jpg", img2);
        k = waitKey(20);

        if(k==27)
        {
            break;
        }
    }
    return 0;
}