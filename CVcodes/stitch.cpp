#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/nonfree/nonfree.hpp>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    Mat img1, img2, g1, g2;
    vector<KeyPoint> keypoints_roi, keypoints_img;  /* keypoints found using SIFT */
    Mat descriptor_roi, descriptor_img;             /* Descriptors for SIFT */
    FlannBasedMatcher matcher;                      /* FLANN based matcher to match keypoints */
    vector<DMatch> matches, good_matches;
    SIFT sift;
    int i, dist=80;
    
    img1 = imread(argv[2]);
    img2 = imread(argv[1]);
    resize(img1, img1, Size(img1.cols/2, img1.rows/2));
    resize(img2, img2, Size(img2.cols/2, img2.rows/2));
    cvtColor(img1, g1, CV_BGR2GRAY);
    cvtColor(img2, g2, CV_BGR2GRAY);

    sift(g1, Mat(), keypoints_roi, descriptor_roi);      /* get keypoints of ROI image */
    sift(g2, Mat(), keypoints_img, descriptor_img);         /* get keypoints of the image */
    
    imshow("d1", descriptor_roi);
    imshow("d2", descriptor_img);
    matcher.match(descriptor_roi, descriptor_img, matches);

    double max_dist = 0; double min_dist = 1000;

    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < descriptor_roi.rows; i++ )
    { 
        double dist = matches[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }

    printf("-- Max dist : %f \n", max_dist );
    printf("-- Min dist : %f \n", min_dist );

    for (i=0; i < descriptor_roi.rows; i++)
    {
        if (matches[i].distance < 3*min_dist)
        {
            good_matches.push_back(matches[i]);
        }
    }
    printf("%ld number of good matches\n", good_matches.size());
    /* Draw matched keypoints */
    Mat img_matches;
    drawMatches(img1, keypoints_roi, img2, keypoints_img, 
                good_matches, img_matches, Scalar::all(-1), 
                Scalar::all(-1), vector<char>(), 
                DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    imshow("matches", img_matches);
    vector<Point2f> keypoints1, keypoints2; 
    for (i=0; i<good_matches.size(); i++)
    {
        keypoints1.push_back(keypoints_img[good_matches[i].trainIdx].pt);
    }
    for (i=0; i<good_matches.size(); i++)
    {
        keypoints2.push_back(keypoints_roi[good_matches[i].queryIdx].pt);
    }

    for(i=0; i<keypoints1.size(); i++)
    {
        printf("%lf %lf %lf %lf\n", keypoints1[i].x, keypoints1[i].y, keypoints2[i].x, keypoints2[i].y);
    }
    printf("%ld %ld\n", keypoints1.size(), keypoints2.size());
    Mat H = findHomography( keypoints1, keypoints2, CV_LMEDS );
    for(int j=0; j<H.cols; j++)
    {
        for(int k=0; k<H.rows; k++)
        {
            printf("%lf\t", H.at<double>(k,j));
        }
        printf("\n");
    }
    
    int mRows = img2.rows;
    if (img1.rows> img2.rows)
    {
        mRows = img1.rows;
    }
    
    Mat result;

    warpPerspective(img2,result,H,Size(img2.cols+img1.cols,mRows));
    imshow("Resilt1",result);
    Mat half(result,Rect(0,0,img1.cols,img1.rows));
    img1.copyTo(half);
    resize(result, result, Size(result.cols*2, result.rows*2));
    imshow( "Result", result );
    imshow("image1", img1);
    imshow("image2", img2);

    waitKey(0);

    return(0);

}