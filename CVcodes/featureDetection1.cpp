#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

int main(int argc, char *argv[])
{
	Mat orig_img, img_blur, img_gray;
	
	orig_img = imread(argv[1]);
	
	GaussianBlur(orig_img, img_blur, Size(3,3), 0, 0, BORDER_DEFAULT);
	
	cvtColor(img_blur, img_gray, CV_RGB2GRAY);
	
	Mat Ix, Iy;
	
	Sobel(img_gray, Ix, CV_32F, 1, 0, 3, 1, 0, BORDER_DEFAULT);
	Sobel(img_gray, Iy, CV_32F, 0, 1, 3, 1, 0, BORDER_DEFAULT);
	
	Mat Ix_Ix, Iy_Iy, Ix_Iy;
	
	Ix_Ix = Ix.mul(Ix);
	Iy_Iy = Iy.mul(Iy);
	Ix_Iy = Ix.mul(Iy);
	
	Mat Ix_Ix_blur, Iy_Iy_blur, Ix_Iy_blur;
	
	GaussianBlur(Ix_Ix, Ix_Ix_blur, Size(5,5), 0, 0, BORDER_DEFAULT);
	GaussianBlur(Iy_Iy, Iy_Iy_blur, Size(5,5), 0, 0, BORDER_DEFAULT);
	GaussianBlur(Ix_Iy, Ix_Iy_blur, Size(5,5), 0, 0, BORDER_DEFAULT);
	
	int i, j;
	
	Mat szeliski_features, harris_features, tomasi_features, triggs_features;
	
	orig_img.copyTo(szeliski_features);
	orig_img.copyTo(harris_features);
	orig_img.copyTo(tomasi_features);
	orig_img.copyTo(triggs_features);
	
	float szeliski_threshold, harris_threshold, tomasi_threshold, triggs_threshold;
	
	szeliski_threshold = atoi(argv[2]);
	harris_threshold = szeliski_threshold * 5000;
	tomasi_threshold = szeliski_threshold * 1.25;
	triggs_threshold = szeliski_threshold;
	
	float detA, traceA, harmonic_mean, alpha = 0.06, harris_function, triggs_function;
	
	for(i = 0; i < Ix.rows; i++)
	{
		for(j = 0; j < Ix.cols; j++)
		{
			Mat A(2, 2, CV_32F);
			
			A.at<float>(0, 0) = Ix_Ix_blur.at<float>(i, j);
			A.at<float>(0, 1) = Ix_Iy_blur.at<float>(i, j);
			A.at<float>(1, 0) = Ix_Iy_blur.at<float>(i, j);
			A.at<float>(1, 1) = Iy_Iy_blur.at<float>(i, j);
			
			detA = (A.at<float>(0, 0) * A.at<float>(1, 1)) - (A.at<float>(0, 1) * A.at<float>(1, 0));
			traceA = A.at<float>(0, 0) + A.at<float>(1, 1);
			
			harmonic_mean = detA / traceA;
			if(harmonic_mean > szeliski_threshold)
			{
				circle(szeliski_features, Point(j, i), 2,  Scalar(0, 0, 255), -1, 8);
			}
			
			harris_function = detA - (alpha * traceA * traceA);
			if(harris_function > harris_threshold)
			{
				circle(harris_features, Point(j, i), 2,  Scalar(0, 0, 255), -1, 8);
			}
			
			Mat lambda(2, 1, CV_32F);
			
			eigen(A, lambda);
			
			if(lambda.at<float>(0, 1) > tomasi_threshold)
			{
				circle(tomasi_features, Point(j, i), 2,  Scalar(0, 0, 255), -1, 8);
			}
			
			triggs_function = lambda.at<float>(0, 1) - (alpha * lambda.at<float>(0, 0));
			if(triggs_function > triggs_threshold)
			{
				circle(triggs_features, Point(j, i), 2,  Scalar(0, 0, 255), -1, 8);
			}
		}
	}
	
	namedWindow("Szeliski Features", CV_WINDOW_AUTOSIZE);
	namedWindow("Harris Features", CV_WINDOW_AUTOSIZE);
	namedWindow("Tomasi Features", CV_WINDOW_AUTOSIZE);
	namedWindow("Triggs Features", CV_WINDOW_AUTOSIZE);
	
	imshow("Szeliski Features", szeliski_features);
	imshow("Harris Features", harris_features);
	imshow("Tomasi Features", tomasi_features);
	imshow("Triggs Features", triggs_features);
	
	waitKey(0);
	
	return 0;
}
