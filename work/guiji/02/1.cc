#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

void main()
{
	Mat srcImg = imread("01.jpg");
	imshow("src", srcImg);
	Mat dstImg(srcImg.size(), CV_8UC3, Scalar::all(0));//纯黑图像

	cvtColor(srcImg, srcImg, CV_BGR2GRAY);
	threshold(srcImg, srcImg, 200, 255, CV_THRESH_BINARY_INV);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	findContours(srcImg, contours, hierarcy, 0, CV_CHAIN_APPROX_NONE);

	vector<vector<Point>> contours_poly(contours.size());//用于存放折线点集

	for (int i = 0; i<contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 15, true);
		drawContours(dstImg, contours_poly, i, Scalar(0, 255, 255), 2, 8);  //绘制
	}
	imshow("approx", dstImg);

	waitKey(0);
}