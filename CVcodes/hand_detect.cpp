#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

void handDetection();

using namespace cv;
int main()
{
   handDetection();
   return 0;
}

void handDetection() {
    VideoCapture capture(1);
 
    /* Rectangle marking ROI for the color patch we want to segment */
    Rect box( 640 / 2 - 75, 480 / 2 - 75, 150, 150 );
    Mat disc_kernel = getStructuringElement( MORPH_ELLIPSE, Size(9, 9));
 
    /* Parameters for calculating back projection histogram */
    int channels[] = {0, 1, 2};
    int hist_size[] = {45, 120, 255};
    float hranges[] = {0, 180};
    float sranges[] = {0, 255};
    float vranges[] = {0, 255};
    const float * ranges[] = { hranges, sranges, vranges };
 
    Mat frame, grayscale, hist, img_hsv, background, temp;
 
    /* Have a big image composed of 4 different images, for simpler viewing purposes */
    Size nsize( 640 / 1.4, 480 / 1.4 );
    Mat merged = Mat( nsize.height * 2, nsize.width * 2, CV_8UC3 );
 
    namedWindow( "" );
    createTrackbar( "hue", "", &hist_size[0], 180 );
    createTrackbar( "sat", "", &hist_size[1], 255 );
    createTrackbar( "val", "", &hist_size[1], 255 );
 
    Mat roi;
    Mat roi_hsv;
 
    char key;
 
    while( true ) {
        capture >> frame;
        flip( frame, frame, 1 );
 
        if( hist.rows != 0 )  {
            /* recalculate histogram again, since we allow interactive change on the HSV value using the trackbar */
            calcHist( &roi_hsv, 1, channels, Mat(), hist, 2, hist_size, ranges );
            normalize( hist, hist, 0, 255, NORM_MINMAX );
 
            /* calculate the back projection and then filter it using the disc kernel */
            cvtColor( frame, img_hsv, CV_BGR2HSV );
            MatND out;
            calcBackProject( &img_hsv, 1, channels, hist, out, ranges );
            filter2D( out, out, -1, disc_kernel);
 
            /* Create a 3 channels image */
            Mat thresh;
            Mat in[] = {out, out, out};
            merge( in, 3, thresh );
 
            /* these parts are just to copy the image into our bigger merged image for simpler viewing purposes */
            resize( frame, temp, nsize );
            temp.copyTo ( Mat(merged, Rect(0, 0, nsize.width, nsize.height) ) );
 
            resize( thresh, temp, nsize );
            temp.copyTo( Mat(merged, Rect(nsize.width, 0, nsize.width, nsize.height) ) );
 
            /* Bitwise and, to extract objects with similar color patch as the calculated histogram */
            thresh = frame & thresh;
 
            resize( thresh, temp, nsize );
            temp.copyTo( Mat(merged, Rect(0, nsize.height, nsize.width, nsize.height) ) );
 
            /* Find and draw the contours of the extracted object */
            vector<vector<Point> > contours;
            vector<Vec4i> hierarchy;
            vector<vector<Point> > poly;
            Canny( out, out, 200, 200 * 2, 3 );
            findContours( out, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
 
            int max_size = -1;
            int max_index = -1;
            int size;
 
            for( int i = 0; i < contours.size(); i++ ) {
                size = (int) contours[i].size();
                if( size > max_size ) {
                    max_index   = i;
                    max_size    = size;
                }
            }
 
            vector<vector<Point> > contours_poly( contours.size() );
            if( max_index > 0 )
                approxPolyDP( Mat(contours[max_index]), contours_poly[max_index], 3, true );
 
            Mat drawing = Mat::zeros( out.size(), CV_8UC3 );
            Scalar color = Scalar( 0, 0, 255 );
            drawContours( drawing, contours_poly, max_index, color, 1, 8);//, vector(), 0, Point() );
 
            resize( drawing, temp, nsize );
            temp.copyTo( Mat(merged, Rect(nsize.width, nsize.height, nsize.width, nsize.height) ) );
            imshow( "", merged );
 
        }
        else {
            rectangle( frame, box, Scalar(0, 0, 255) );
            imshow( "", frame );
        }
 
        key = waitKey(10);
 
        if( key == 27 )
            break;
        else if( key == 'c' ) {
            /* calculate the histogram for the small patch in marked by the red square */
            /* with this histogram we would extract all the object which has similar color */
 
            roi = Mat ( frame, box );
            cvtColor( roi, roi_hsv, CV_BGR2HSV );
            calcHist( &roi_hsv, 1, channels, Mat(), hist, 2, hist_size, ranges );
            normalize( hist, hist, 0, 255, NORM_MINMAX );
        }
    }
}
