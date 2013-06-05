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
    vector<Mat> imgs, grays;
    int i, j, k;
    for (i=1; i<argc; i++)
    {
        Mat img = imread(argv[i]);
        Mat gray;
        resize(img, img, Size(img.cols/2, img.rows/2));
        cvtColor(img, gray, CV_BGR2GRAY);
        grays.push_back(gray);
        img.release();
        gray.release();
        //imshow("image", gray);
        //waitKey(0);
    }
    vector<vector<KeyPoint> > keypoints;
    vector<Mat> descriptors;
    vector<KeyPoint> kps;
    SIFT sift;

    for(i=0; i<grays.size(); i++)
    {
        Mat descriptor;
        sift(grays[i], Mat(), kps, descriptor);
        keypoints.push_back(kps);
        descriptors.push_back(descriptor);
        descriptor.release();
        kps.clear();
    }
    
    FlannBasedMatcher matcher;
    vector<DMatch> matches, good_matches;
    double max_dist = 0, min_dist=1000;
    for(i=0; i<grays.size(); i++)
    {
        for(j=i+1; j<grays.size(); j++)
        {
            if (i != j)
            {
                matcher.match(descriptors[j], descriptors[i], matches);
                for(k = 0; k < matches.size(); k++)
                { 
                    double dist = matches[k].distance;
                    if( dist < min_dist ) min_dist = dist;
                    if( dist > max_dist ) max_dist = dist;
                }
                for (k=0; k < descriptors[i].rows; k++)
                {
                    if (matches[k].distance <= 3*min_dist)
                    {
                        good_matches.push_back(matches[k]);
                    }
                }
                printf("Image %d <=> Image %d -> good mathces %ld\n", i, j, good_matches.size());
                good_matches.clear();
                matches.clear();
                min_dist = 1000;
                max_dist = 0;
            }
        }
    }
    waitKey(0);
    return (0);
}