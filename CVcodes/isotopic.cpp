#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace cv;

int main(int argc, char *argv[])
{
	Mat orig_img, img_gray, img_filter_x, img_filter_y;
	
	orig_img = imread(argv[1]);
	
	cvtColor(orig_img, img_gray, CV_RGB2GRAY);
	
	Mat isotropic_filter_x(3, 3, CV_32FC1);
	Mat isotropic_filter_y(3, 3, CV_32FC1);
	
	isotropic_filter_x.at<float>(0, 0) = -1;
	isotropic_filter_x.at<float>(0, 1) = 0;
	isotropic_filter_x.at<float>(0, 2) = -1;
	isotropic_filter_x.at<float>(1, 0) = -sqrt(2);
	isotropic_filter_x.at<float>(1, 1) = 0;
	isotropic_filter_x.at<float>(1, 2) = sqrt(2);
	isotropic_filter_x.at<float>(2, 0) = -1;
	isotropic_filter_x.at<float>(2, 1) = 0;
	isotropic_filter_x.at<float>(2, 2) = 1;
	
	transpose(isotropic_filter_x, isotropic_filter_y);
	
	filter2D(img_gray, img_filter_x, -1, isotropic_filter_x);
	filter2D(img_gray, img_filter_y, -1, isotropic_filter_y);
	
	imshow("X_derivative", img_filter_x);
	imshow("Y_derivative", img_filter_y);
	
	waitKey(0);
}
