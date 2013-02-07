#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

int erode_image();
int dilate_image();

int main()
{	
	erode_image();
	dilate_image();	
	return 0;
}
	
int erode_image()
{
	Mat img, kernel, fin_img;
	img = imread("Lenna.png");
	int size=4;
	kernel = getStructuringElement(MORPH_CROSS, Size(2*size+1, 2*size+1), Point(size, size));
	erode(img, fin_img, kernel);
	imshow("erosion", fin_img);
	waitKey(0);
	return 1;
}

int dilate_image()
{
	Mat img, kernel, fin_img;
	img = imread("Lenna.png");
	int size=4;
	kernel = getStructuringElement(MORPH_CROSS, Size(2*size+1, 2*size+1), Point(size, size));
	dilate(img, fin_img, kernel);
	imshow("dilate", fin_img);
	waitKey(0);
	return 1;
}
