#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

int main()
{
	// Declare data variable
	Mat img;

	// Read Image
	img = imread("Lenna.png");

	// Display Image
	imshow("image",img);

	waitKey(0);
	// input parameter - int - msec
	// Returns int
	return 0;
}
