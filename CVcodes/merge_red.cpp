	#include <opencv2/highgui/highgui.hpp>
	#include <stdio.h>
	using namespace std;
	using namespace cv;

	int main()
	{
		Mat img, g, fin_img;
		img = imread("Lenna.png",CV_LOAD_IMAGE_GRAYSCALE);
		vector<Mat> channels;
		g = Mat::zeros(Size(img.rows, img.cols), CV_8UC1);
		channels.push_back(g);
		channels.push_back(g);
		channels.push_back(img);
		fin_img = Mat::zeros(img.rows, img.cols, CV_8UC1);
		merge(channels, fin_img);
		imshow("img", fin_img);
		waitKey(0);
		return 0;
	}