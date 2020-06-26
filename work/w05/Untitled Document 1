#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat srcimage,dstimage1,dstimage2,dstimage3,srcimage1,sc,dstimage4;
int g_nthreshold=40;
static void on_threshold(int, void *)//二值化
{
threshold(srcimage1, dstimage3, g_nthreshold+1, 255, CV_THRESH_BINARY);
imshow("自定义二值化",dstimage3);
}
int main(int arg,char* argv[])
{
 srcimage=imread("1.jpeg",1);
 srcimage1=imread("1.jpeg",0);
 if(!srcimage.data) {return false;}//如果没有图像输入返回错误
 adaptiveThreshold(srcimage1,sc,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,25,5);
 namedWindow("自适应二值化",CV_WINDOW_NORMAL);
 imshow("自适应二值化",sc);
 namedWindow("ORG",CV_WINDOW_NORMAL);//输出原图
 imshow("ORG",srcimage);
 namedWindow("自定义二值化",CV_WINDOW_NORMAL);
 createTrackbar("阈值:","自定义二值化",&g_nthreshold,255,on_threshold);//建立轨迹条
 on_threshold(g_nthreshold,0);
 waitKey(0);
 return 0;
}
