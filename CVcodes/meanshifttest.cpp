#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

Mat img, res, element;

int main(int argc, char** argv)
{
   img = imread( argv[1] );
   pyrMeanShiftFiltering( img, res, 10, 35, 3);
   imwrite("output.png", res);
   imshow( "window", res );

   waitKey();

   return 0;
}