#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

#define THRESHOLD_HIGH 100
#define THRESHOLD_LOW 80
#define PI_BY_8 0.39286
#define PI_BY_4 0.78571
#define PI_BY_2 1.57142
#define PI 3.14285

using namespace cv;

int main(int argc, char *argv[])
{
	Mat orig_img, img_gray;
	
	orig_img = imread(argv[1]);
	
	cvtColor(orig_img, img_gray, CV_RGB2GRAY);
	
	Mat Ix, Iy;
	
	Sobel(img_gray, Ix, CV_32F, 1, 0);
	Sobel(img_gray, Iy, CV_32F, 0, 1);
	
	Mat magnitude(Ix.rows, Ix.cols, CV_32FC1);
	Mat direction(Ix.rows, Ix.cols, CV_8UC1);
	
	int i, j;
	
	float tan_inverse;
	
	for(i = 0; i < Ix.rows; i++)
	{
		for(j = 0; j < Ix.cols; j++)
		{
			magnitude.at<float>(i, j) = sqrt(Ix.at<float>(i, j)*Ix.at<float>(i, j) + Iy.at<float>(i, j)*Iy.at<float>(i, j));
			if(Ix.at<float>(i, j) != 0)
			{
				tan_inverse = atan(Iy.at<float>(i, j) / Ix.at<float>(i, j));
				
				if(tan_inverse > 3*PI_BY_8 || tan_inverse < -3*PI_BY_8)
				{
					direction.at<uchar>(i, j) = 2;
				}
				else if(tan_inverse > PI_BY_8)
				{
					direction.at<uchar>(i, j) = 1;
				}
				else if(tan_inverse < -PI_BY_8)
				{
					direction.at<uchar>(i, j) = 3;
				}
				else
				{
					direction.at<uchar>(i, j) = 0;
				}
			}
			else
			{
				direction.at<uchar>(i, j) = 2;
			}
		}
	}
	
	int neighbor_plus_x[4] = {0, 1, 1, 1};
	int neighbor_plus_y[4] = {1, -1, 0, 1};
	int neighbor_minus_x[4] = {0, -1, -1, -1};
	int neighbor_minus_y[4] = {-1, 1, 0, -1};
	
	int temp, index_x, index_y;
	
	for(i = 1; i < Ix.rows-1; i++)
	{
		for(j = 1; j < Ix.cols-1; j++)
		{
			temp = direction.at<uchar>(i, j);
					
			index_x = i + neighbor_plus_x[temp];
			index_y = j + neighbor_plus_y[temp];
			
			if(direction.at<uchar>(index_x, index_y) == temp && magnitude.at<float>(i, j) <= magnitude.at<float>(index_x, index_y))
			{
				magnitude.at<float>(i, j) = 0;
			}
			
			index_x = i + neighbor_minus_x[temp];
			index_y = j + neighbor_minus_y[temp];
			
			if(direction.at<uchar>(index_x, index_y) == temp && magnitude.at<float>(i, j) <= magnitude.at<float>(index_x, index_y))
			{
				magnitude.at<float>(i, j) = 0;
			}
		}
	}
	
	Mat edges(Ix.rows, Ix.cols, CV_8UC1);
	
	int u, v;
	
	for(i = 1; i < Ix.rows -1; i++)
	{
		for(j = 1; j < Ix.cols -1; j++)
		{
			if(magnitude.at<float>(i, j) > THRESHOLD_HIGH && edges.at<uchar>(i, j) != 255)
			{
				edges.at<uchar>(i, j) = 255;
				
				u = i;
				v = j;
				
				while(u != 0 && v != 0)
				{
					temp = direction.at<uchar>(u, v);
						
					index_x = u + neighbor_plus_x[temp];
					index_y = v + neighbor_plus_y[temp];
					
					int k, l, maximum_u, maximum_v;
					float maximum = 0;
			
					if(magnitude.at<float>(index_x, index_y) > maximum && edges.at<uchar>(index_x, index_y)!=255)
					{
						maximum_u = index_x;
						maximum_v = index_y;
						maximum = magnitude.at<float>(index_x, index_y);
					}
			
					index_x = u + neighbor_minus_x[temp];
					index_y = v + neighbor_minus_y[temp];
			
					if(magnitude.at<float>(index_x, index_y) > maximum && edges.at<uchar>(index_x, index_y)!=255)
					{
						maximum_u = index_x;
						maximum_v = index_y;
						maximum = magnitude.at<float>(index_x, index_y);
					}
					
					if(maximum > THRESHOLD_LOW)
					{
						edges.at<uchar>(maximum_u, maximum_v) = 255;
						u = maximum_u;
						v = maximum_v;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	
	imshow("Canny1", edges);
	
	waitKey(0);
}
