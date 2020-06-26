#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
    Mat frame,src;
    Mat TrackPic=cv::Mat::zeros(500,500,CV_8UC3);
    char c=0;
    VideoCapture capture(0);
    while(1)
    {
        capture >> frame;
        Mat midImage;
        cvtColor(frame,midImage,CV_BGR2GRAY);
        GaussianBlur(midImage,midImage,Size(9,9),2,2);
        //medianBlur(frame, midImage, 3);
        vector<Vec3f>circles;
        vector<vector<Point2d>>pt;
        vector<Point2d>pt1;
        
        /***************************************************
        std::ofstream outFile;
        outFile.open("1.txt");

        int i;
        for(i=0;i<pt.size();i++)
        {
            outFile << std::setprecision(10) << vector.at(i) << std::endl;
        }
        outFile.close();
/**************************************************************************/

        /***************************************************/
        HoughCircles(midImage,circles,CV_HOUGH_GRADIENT,1.5,10,200,100,0,0);

        for(size_t i=0;i<circles.size();i++)
        {
            Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));

            int radius = cvRound(circles[i][2]);
            circle(frame,center,3,Scalar(0,255,0),-1,8,0);
            circle(frame,center,radius,Scalar(155,50,255),3,8,0);
            line(TrackPic,Point(center.x,center.y),Point(center.x,center.y),Scalar(255, 255, 0), 2);
            
            //printf("x=%d,y=%d\n",cvRound(circles[i][0]),cvRound(circles[i][1]));
            pt1.push_back(Point2d(cvRound(circles[i][0]),cvRound(circles[i][1])));
            pt.push_back(pt1);
            //cout<<pt[i]<<"";
            cout<<pt1[i]<<"";
            /*******************************************************************
            // src=imread("1.jpg");
            // cvtColor(src,src,COLOR_BGR2GRAY);//图像灰度化
            // threshold(src,src,100,255,THRESH_BINARY_INV);
            // vector<vector<Point>>contours;
            // findContours(src,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
            // Scalar lineColor = Scalar(0, 255, 255);
            // Mat contoursMat = Mat::zeros(src.size(),CV_8UC3);
            // drawContours(contoursMat, contours, -1, lineColor, 2, 8);
            // imshow("contours", contoursMat);
            vector<vector<Point>> lines(pt.size());
            Mat dst = Mat::zeros(src.size(),CV_8UC3);
            for(int i=0;i<pt.size();i++)
            {
                approxPolyDP(pt[i],lines[i],10,true);
                drawContours(TrackPic, lines, i, Scalar(0, 255, 255), 2, 8);  //绘制
                // if(lines[i].size()==3)
                // {
                //     cout<<"三角形"<<endl;
                // }
                // else if(lines[i].size()==4)
                // {
                //     cout<<"四边形"<<endl;
                // }
                // else if(lines[i].size()==5)
                // {
                //     cout<<"五边形"<<endl;
                // }
                // else if(lines[i].size()>10)
                // {
                //     cout<<"圆"<<endl;
                // }
                // else
                // {
                //     cout<<"none"<<endl;
                // }
                
            }
          /*******************************************************************/
        }
        namedWindow("1");
        imshow("1",TrackPic);
        imwrite("1.jpg",TrackPic);
        namedWindow("result");
        imshow("result",frame);
        imshow("approx",TrackPic);
        c =cvWaitKey(30);
        if(c == 27)
        {
            break;
        }
    }
    destroyAllWindows();
	capture.release();
    return 0;
}
