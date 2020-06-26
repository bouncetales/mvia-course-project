#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
    Mat frame;
    char c=0;
    VideoCapture capture(0);
    while(1)
    {
        capture >> frame;
        Mat midImage;
        cvtColor(frame,midImage,CV_BGR2GRAY);
        GaussianBlur(midImage,midImage,Size(9,9),2,2);

        vector<Vec3f>circles;
        vector<Point>pt;
        HoughCircles(midImage,circles,CV_HOUGH_GRADIENT,1.5,10,200,100,0,0);

        for(size_t i=0;i<circles.size();i++)
        {
            Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));

            int radius = cvRound(circles[i][2]);
            circle(frame,center,3,Scalar(0,255,0),-1,8,0);
            circle(frame,center,radius,Scalar(155,50,255),3,8,0);
            printf("x=%d,y=%d\n",cvRound(circles[i][0]),cvRound(circles[i][1]));
            pt.push_back(Point(cvRound(circles[i][0]),cvRound(circles[i][1])));
        }
        namedWindow("result");
        imshow("result",frame);
        c =cvWaitKey(30);
        if(c == 27)
        {
            break;
        }
    }
    return 0;
}

