#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

int returnMedian(int arr[])
{
	int i, j, temp;
	
	for(i = 1; i < 9; i++)
	{
		for(j = 0; j < 9 - i; j++)
		{
			if(arr[j] > arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
	
	return(arr[4]);
}

int main(int argc, char *argv[])
{
	Mat orig_img, img_gray, img_filter;
	
	orig_img = imread(argv[1]);
	
	cvtColor(orig_img, img_gray, CV_RGB2GRAY);
	
	img_gray.copyTo(img_filter);
	
	int i, j, temp[9];
	
	for(i = 1; i < img_filter.rows - 1; i++)
	{
		for(j = 1; j < img_filter.cols - 1; j++)
		{
			temp[0] = img_gray.at<uchar>(i-1, j-1);
			temp[1] = img_gray.at<uchar>(i-1, j);
			temp[2] = img_gray.at<uchar>(i-1, j+1);
			temp[3] = img_gray.at<uchar>(i, j-1);
			temp[4] = img_gray.at<uchar>(i, j);
			temp[5] = img_gray.at<uchar>(i, j+1);
			temp[6] = img_gray.at<uchar>(i+1, j-1);
			temp[7] = img_gray.at<uchar>(i+1, j);
			temp[8] = img_gray.at<uchar>(i+1, j+1);
			
			img_filter.at<uchar>(i, j) = returnMedian(temp);
		}
	}
	
	imshow("Noise", img_gray);
	imshow("Filtered", img_filter);
	
	waitKey(0);
}
