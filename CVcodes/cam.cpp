#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
using namespace cv;
using namespace std;
int main()
{
	VideoCapture cap = VideoCapture(0);
	Mat img;
	int k;
	if (!cap.isOpened())
	{
		printf("Unable to open camera\n");
		return -1;
	}
	cap >> img;
	imshow("image", img);
	waitKey(0);
	destroyWindow("image");
	while (1)
	{
		cap >> img;
		imshow("video", img);
		k = waitKey(30);
		if (k == 27)
		{
			break;
		}
	}
	VideoCapture vid = VideoCapture("MotoGP - Awesome Last Lap.wmv");
	vid >> img;
	imshow("image", img);
	waitKey(0);
	destroyWindow("image");
	while (1)
	{
		vid >> img;
		imshow("video", img);
		k = waitKey(30);
		if (k == 27)
		{
			break;
		}
	}
	return 0;
}