#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

int main(int argc, char *argv[])
{
	Mat orig_img, img_gray, img_blur, img_filter;
	
	orig_img = imread(argv[1]);
	
	cvtColor(orig_img, img_gray, CV_RGB2GRAY);
	
	GaussianBlur(img_gray, img_blur, Size(5,5), 0, 0);
	
	img_filter = 2*img_gray - img_blur;
	
	imshow("Gray", img_gray);
	imshow("Filtered", img_filter);
	
	waitKey(0);
}
