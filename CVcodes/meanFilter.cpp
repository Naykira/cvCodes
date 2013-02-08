#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

int main(int argc, char *argv[])
{
	Mat orig_img, img_gray, img_filter;
	
	orig_img = imread(argv[1]);
	
	cvtColor(orig_img, img_gray, CV_RGB2GRAY);
	
	Mat mean_filter(5, 5, CV_32F);
	
	int i, j;
	
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
		{
			mean_filter.at<float>(i, j) = 1.0/25.0;
		}
	}
	
	/*img_gray.copyTo(img_filter);
	
	for(i = 1; i < img_filter.rows - 1; i++)
	{
		for(j = 1; j < img_filter.cols - 1; j++)
		{
			img_filter.at<uchar>(i, j) = ( img_gray.at<uchar>(i-1, j-1) + img_gray.at<uchar>(i-1, j) + img_gray.at<uchar>(i-1, j+1)
									   + img_gray.at<uchar>(i, j-1) + img_gray.at<uchar>(i, j) + img_gray.at<uchar>(i, j+1)
									   + img_gray.at<uchar>(i+1, j-1) + img_gray.at<uchar>(i+1, j) + img_gray.at<uchar>(i+1, j+1) ) / 9;
		}
	}*/
	filter2D(img_gray, img_filter, -1, mean_filter);
	
	imshow("Gray", img_gray);
	imshow("Filtered", img_filter);
	
	waitKey(0);
}
