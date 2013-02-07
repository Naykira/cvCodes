#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

int gray_image();

int main()
{
	Mat img, gray;
	img = imread("Lenna.png");

	//Convert BGR image to Grayscale image
	cvtColor(img, gray, CV_BGR2GRAY);

	imshow("image",img);
	imshow("gray image", gray);
	waitKey(0);

	destroyAllWindows();

	gray_image();

	return 0;
}

int gray_image()
{
	Mat img;

	// Read image as grayscale image
	img = imread("Lenna.png", 
		        CV_LOAD_IMAGE_GRAYSCALE);

	imshow("image", img);
	waitKey(0);
	return 0;
}