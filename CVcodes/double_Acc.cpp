#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;
int main(int argc, char *argv[])
{
    Mat img, double_img;
    img = imread("Lenna.png");

    img.convertTo(double_img, CV_64FC3);
    printf("%d %d\n", img.cols, img.rows);
    printf("%d %d %d\n", img.at<Vec3b>(0, 0)[0], img.at<Vec3b>(0, 0)[1], img.at<Vec3b>(0, 0)[2]);
    //printf("%d %d %d\n", img.at<uchar>(0, 0)[0], img.at<uchar>(0, 0)[1], img.at<uchar>(0, 0)[2]);

    printf("%f %f %f\n", double_img.at<Vec3d>(0, 0)[0], double_img.at<Vec3d>(0, 0)[1], double_img.at<Vec3d>(0, 0)[2]);

    return 0;
}