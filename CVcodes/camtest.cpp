#include<opencv2/highgui/highgui.hpp>
using namespace cv;

int main()
{
	VideoCapture cap = VideoCapture(0);
	Mat img;
	int k;
	while (1)
	{
		cap >> img;
		imshow("cam",img);
		k = waitKey(20);
		if(k==27)
		{
			break;
		}
	}
	return 0;
}
