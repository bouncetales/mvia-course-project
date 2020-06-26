#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
    Mat frame,src;
    Mat TrackPic=cv::Mat::zeros(500,600,CV_8UC3);
    char c=0;
    VideoCapture capture(0);
    remove("vector.txt");
    while(1)
    {
        capture >> frame;
        Mat midImage;
        cvtColor(frame,midImage,CV_BGR2GRAY);
        GaussianBlur(midImage,midImage,Size(9,9),2,2);
        //medianBlur(frame, midImage, 3);
        vector<Vec3f>circles;
        // vector<vector<Point2d>>pt;
        // vector<Point2d>pt1;
/*********************************霍夫变换检测圆,画出轮廓、中心点******************************/
        HoughCircles(midImage,circles,CV_HOUGH_GRADIENT,2.0,200,150,100,5,0);

        for(size_t i=0;i<circles.size();i++)
        {
            Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));

            int radius = cvRound(circles[i][2]);
            circle(frame,center,3,Scalar(0,255,0),-1,8,0);
            circle(frame,center,radius,Scalar(155,50,255),3,8,0);
            line(TrackPic,Point(center.x,center.y),Point(center.x,center.y),Scalar(255, 255, 0), 2);
            printf("x=%d,y=%d\n",cvRound(circles[i][0]),cvRound(circles[i][1]));
/**************************************************************************************/

/*************************************存轨迹点******************************************/
            std::ofstream fout;
            fout.open("vector.txt",ios::app);
            for (int l = 0; l < circles.size(); ++l)
            {
                fout << center.x<<' '<< center.y<< endl;
            }
            fout.close();
        namedWindow("1");
        imshow("1",TrackPic);
        imwrite("1.jpg",TrackPic);
        }

        namedWindow("result");
        imshow("result",frame);
       // imshow("approx",TrackPic);
        c =cvWaitKey(30);
        if(c == 27)
        {
            break;
        }
    }
    //destroyAllWindows();
	capture.release();
    return 0;
}