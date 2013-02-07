// Accessing Pixel values (data)
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

int main()
{
	Mat img;
	int rows, cols;

	img = imread("Lenna.png");
	rows = img.rows;
	cols = img.cols;
	printf("%d %d\n", rows, cols);
	int i,j,r,g,b;
	
	unsigned char *input = (unsigned char*)(img.data);
 	for(int i = 0;i < rows ;i++)
 	{
		for(int j = 0;j < cols ;j++)
		{
             b = input[img.step * j + i ] ;
             g = input[img.step * j + i + 1];
             r = input[img.step * j + i + 2];
             printf("%d %d - %d %d %d \n", i, j, b, g, r);
         }
     }	
	return 0;
}