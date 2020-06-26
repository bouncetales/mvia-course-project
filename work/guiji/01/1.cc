#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
 
#include <iostream>
#include <stdlib.h>
 
using namespace cv;
using namespace std;
 
bool selectObject = false;  //鼠标选择区域中间变量
bool drawRect = false;  //用于手动选择追踪区域中间变量
Rect selection;  //追踪的目标的区域
Point origin;  //手动画区域中间变量
 
void onMouse(int event, int x, int y, int flags, void *param)  //手动圈出追踪区域
{
	switch(event)
	{
	case CV_EVENT_MOUSEMOVE:
		if(selectObject)
		{
			selection.x = MIN(x,origin.x);
			selection.y = MIN(y,origin.y);
			selection.width = std::abs(x - origin.x);
			selection.height = std::abs(y - origin.y);
		}
		break;
 
	case CV_EVENT_LBUTTONDOWN:
		selectObject = true;
		origin = Point(x,y);
		selection = Rect(x,y,0,0);		
		break;
 
	case CV_EVENT_LBUTTONUP:
		selectObject = false;
		drawRect = true;
		break;
	}
}
 
int main()
{
	int histSize[1] = {256};  //直方图特征子区间bins数目
	float hranges[2] = {0,255};  //特征区间的取值范围，这里只有一个特征hue
	const float* ranges[1] = {hranges};
	int channels[1] = {0};  //通道数
	Mat dstHist, bPro, frame, hsv, hue, hsvSplit[3];  //目标直方图，反向背景图，每一帧图，hsv图，hue通道图，分离通道中间变量
 
	VideoCapture video;
	video.open(0);  //打开本地视频
 
	if(!video.isOpened())  //判视频是否打开
	{
		cout << "error" << endl;
		return -1;
	}
 
	//输出视频的相关信息
	long nTotalFrame = video.get(CV_CAP_PROP_FRAME_COUNT);
	cout << "总帧数："  <<nTotalFrame <<endl;
 
	int frameHeight = video.get(CV_CAP_PROP_FRAME_HEIGHT);
	int frameWidth = video.get(CV_CAP_PROP_FRAME_WIDTH);
 
	cout<< "帧像素高： " << frameHeight <<endl;
	cout<< "帧像素宽：" <<frameWidth <<endl;
 
	double FrameRate = video.get(CV_CAP_PROP_FPS);
	cout<< "帧率：" <<FrameRate <<endl;
 
	namedWindow("camshift",0);
	setMouseCallback("camshift",onMouse,NULL);  //鼠标回调
 
	video >> frame;  //读取一帧视频
	if(frame.empty())
	{
		cout << "empty";
		return -1;
	}
 
	while(!drawRect)  //画出要追踪目标的区域
	{
		imshow("camshift",frame);
		if(waitKey(1) == 'q')
			return 1;
	}
	
	setMouseCallback("camshift",NULL,NULL);  //鼠标停止回调
 
	cvtColor(frame,hsv,CV_BGR2HSV);  //RGB转HSV
	split(hsv,hsvSplit);  //hsv分离通道
	hue = hsvSplit[0];  //得到hue通道
	calcHist(&frame,1,channels,Mat(),dstHist,1,histSize,ranges);  //hue直方图
	normalize(dstHist,dstHist,0.0,1.0,NORM_MINMAX);  //直方图归一化
 
	long frameCount = 2;  //帧数中间变量
	while(1)
	{
		video >> frame;  //读一帧图像
		if(frame.empty())
			break;
 
		calcBackProject(&frame,1,channels,dstHist,bPro,ranges,255.0);  //反向概率图
		RotatedRect trackBox = CamShift(bPro,selection,TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER ,10, 1));  //camshift追踪，返回会旋转的矩形
 
		stringstream buf;
		buf << frameCount;
		string num = buf.str();
		putText(frame, num, Point(20, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 1);  //帧数显示在左上角
		ellipse(frame,trackBox,Scalar(0,0,255),3,CV_AA);  //将旋转矩形以椭圆的形式输出
		imshow("camshift",frame);  //显示图像
 
		frameCount++;  //帧数加1
 
		if(waitKey(1) == 'q')  //须有，否则视频不能读取
			break;
	}
	video.release();
	//system("pause");
	return 0;
}