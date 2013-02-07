#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

int main()
{
	Mat img;
	img = imread("Lenna.png");
	imshow("image",img);
	waitKey(0);
	return 0;
}
