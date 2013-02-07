// Thresholding Image
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
using namespace cv;
using namespace std;
int main(int argc, char* argv[])
{
	Mat img, gray, thresh;
	img = imread(argv[1]);
	cvtColor(img, gray, CV_BGR2GRAY);

	int threshval, maxval;
	threshval = atoi(argv[2]);
	maxval = atoi(argv[3]);

	threshold(gray, thresh, 
	  threshval, maxval, THRESH_BINARY);

	imshow("threshold", thresh);
	waitKey(0);

	return 0;
}
