#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace cv;
using namespace std;

int getDescriptors(vector<Point>& points, vector<Mat>& descriptors);
int findCost(vector<Mat>& descriptors1, vector<Mat>& descriptors2, vector<Point>& matches);
int drawMatches(vector<Point>& goodMatches1, vector<Point>& goodMatches2, Mat& img1, Mat& img2, Mat& newTemplate);

int main(int argc, char* argv[])
{
    Mat img, gray, canny_img, drawing, kernel;
    Mat img1, gray1, canny_img1;

    img = imread(argv[1]);
    img1 = imread(argv[2]);
    cvtColor(img, gray, CV_BGR2GRAY);
    cvtColor(img1, gray1, CV_BGR2GRAY);

    int size=2;
    kernel = getStructuringElement(MORPH_CROSS, Size(2*size+1, 2*size+1), Point(size, size));
    //dilate(gray, gray, kernel);
    Canny(gray, canny_img, 100, 200);
    Canny(gray1, canny_img1, 100, 200);

    vector<vector<Point> > contours, contours1;
    vector<Vec4i> hierarchy, hierarchy1;
    vector<Point> points, points1;

    drawing = Mat::zeros(canny_img.size(), CV_8UC3);
    findContours(canny_img, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
    findContours(canny_img1, contours1, hierarchy1, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));

    for (int i=0; i< contours.size(); i++)
    {
        drawContours(drawing, contours, i, Scalar(0, 0, 255), 2, 8, hierarchy, 0, Point());
        for(int j=0; j<contours[i].size(); j++)
        {
            //printf("(%d, %d), ",contours[i][j].x, contours[i][j].y);
            points.push_back(Point(contours[i][j].x, contours[i][j].y));
        }
        //printf("\n");
    }
    for (int i=0; i< contours1.size(); i++)
    {
        //drawContours(drawing, contours, i, Scalar(0, 0, 255), 2, 8, hierarchy, 0, Point());
        for(int j=0; j<contours1[i].size(); j++)
        {
            //printf("(%d, %d), ",contours[i][j].x, contours[i][j].y);
            points1.push_back(Point(contours1[i][j].x, contours1[i][j].y));
        }
        //printf("\n");
    }
    imshow("canny", canny_img);
    imshow("contours", drawing);
    waitKey(0);

    vector<Mat> descriptors, descriptors1;
    getDescriptors(points, descriptors);
    getDescriptors(points1, descriptors1);
    
    for (int i=0; i<descriptors.size(); i++)
    {
        imshow("descriptors",descriptors[i]);
        waitKey(5);
    }
    for (int i=0; i<descriptors1.size(); i++)
    {
        imshow("descriptors1",descriptors1[i]);
        waitKey(5);
    }
    
    vector<Point> match;
    vector<Point> matches1, matches2;
    findCost(descriptors, descriptors1, match);
    for (int i=0; i<match.size(); i++)
    {
        matches1.push_back(Point(points[match[i].x].x, points[match[i].x].y));
        matches2.push_back(Point(points1[match[i].y].x, points1[match[i].y].y));
        printf("(%d, %d)-> (%d, %d)\n", points[match[i].x].x, points[match[i].x].y, points1[match[i].y].x, points1[match[i].y].y);
    }
    Mat newTemplate;
    drawMatches(matches1, matches2, img, img1, newTemplate);
    imshow("Matches", newTemplate);
    waitKey(0);
    return(0);
}

int getDescriptors(vector<Point>& points, vector<Mat>& descriptors)
{
    int i, j;
    int x1, x2, y1, y2, r1, r2, r;
    double theta, theta1, theta2;
    int putr, puttheta;
    double logr;

    for (i=0; i<points.size(); i++)
    {
        x1 = points[i].x;
        y1 = points[i].y;
        r1 = sqrt(x1*x1+y1*y1);
        theta1 = atan2(y1,x1);
        Mat descriptor = Mat::ones(Size(12,5), CV_8U)*255;
        for(j=0; j<points.size(); j++)
        {
            if (i==j)
            {
                continue;
            }
            x2 = points[j].x;
            y2 = points[j].y;
            r2 = sqrt(x2*x2+y2*y2);
            theta2 = atan2(y2,x2);

            r = abs(r1-r2);
            //printf("%d %d\n", x1, y1);
            //printf("%f %f\n", theta1, theta2);
            theta = abs(theta1-theta2)*180/CV_PI;
            logr = log(r);
            //printf ("logr = %f\n", logr);

            if (logr < 0)
            {
                putr = 0;
            }
            else if (logr >= 0 && logr < 1)
            {
                putr = 1;
            }
            else if(logr >=1 && logr < 2)
            {
                putr = 2;
            }
            else if(logr >=2 && logr < 3)
            {
                putr = 3;
            }
            else
            {
                putr = 4;
            }

            puttheta = int(theta/15);
            //printf("%f %d\n", theta, puttheta);
            descriptor.at<uchar>(puttheta, putr) -= 1; 
        }
        descriptors.push_back(descriptor);
    }
    if (descriptors.size() > 0)
    {
        return 1;
    }
    return 0;
}

int findCost(vector<Mat>& descriptors1, vector<Mat>& descriptors2, vector<Point>& matches)
{
    int i,j, mi, mj;
    double cost=0, min_cost=0;
    //Mat sum_mat, mod_mat;
    Mat diff_mat = Mat(Size(12, 5), CV_32F);
    Mat sum_mat = Mat(Size(12, 5), CV_32F);
    Mat mod_mat = Mat(Size(12, 5), CV_32F);
    for (i=0; i<descriptors1.size();i++)
    {
        cost = 100;
        min_cost = 100;
        mi = 0;
        mj = 0;
        for(j=0; j<descriptors2.size(); j++)
        {
            diff_mat = descriptors1[i]-descriptors2[j];
            mod_mat = diff_mat.mul(diff_mat);
            sum_mat = descriptors1[i]+descriptors2[j];

            cost = sum(mod_mat)[0]/sum(sum_mat)[0]/2;
            //printf("%f\n", cost);
            if (cost < min_cost)
            {
                min_cost = cost;
                mi = i;
                mj = j;
            }
        }
        matches.push_back(Point(mi,mj));
    }
}

int drawMatches(vector<Point>& goodMatches1, vector<Point>& goodMatches2, Mat& img1, Mat& img2, Mat& newTemplate)
{
    int i, w, h, newr, newc;
    w = img1.cols;
    h = img1.rows;

    newr = img1.rows;

    if (img1.rows < img2.rows)
    {
        newr = img2.rows;
    }

    newc = img1.cols + img2.cols;
    newTemplate = Mat::zeros(newr, newc, CV_8UC3);

    Mat leftpart(newTemplate, Rect(0, 0, img1.cols, img1.rows));
    img1.copyTo(leftpart);

    Mat rightpart(newTemplate, Rect(img1.cols, 0, img2.cols, img2.rows));
    img2.copyTo(rightpart);

    for (i=0; i<goodMatches1.size(); i++)
    {
        //circle(img1, goodMatches1[i], 2, Scalar(255, 0, 0), -1, 8, 0);
        circle(newTemplate, goodMatches1[i], 5, Scalar(255, 0, 0), -1, 8, 0);
        //circle(img2, goodMatches2[i], 2, Scalar(255, 0, 0), -1, 8, 0);
        circle(newTemplate, Point(goodMatches2[i].x+img1.cols, goodMatches2[i].y), 5, Scalar(255, 0, 0), -1, 8, 0);
        //line(newTemplate, goodMatches1[i], Point(goodMatches2[i].x+img1.cols, goodMatches2[i].y), Scalar(0, 0, 255), 2, 8, 0);
    }
    return 1;
}