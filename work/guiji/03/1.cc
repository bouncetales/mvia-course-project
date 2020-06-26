#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <iomanip>

using namespace cv;
using namespace std;


int main()
{
    float a,b,c,d,s;
    Mat src;
    src=imread("/home/zk/work/guiji/05/build/1.jpg");
    Mat TrackPic=cv::Mat::zeros(500,500,CV_8UC3);   
    vector<vector<Point>> contours;
    vector<Point>p;
/************************读取保存坐标文件并输出到vector容器中******************************/
    ifstream outfile;
    outfile.open("/home/zk/work/guiji/05/build/vector.txt");
    Point temp;
    double temp1=0,temp2=0;
    while(!outfile.eof())
    //for(int i=0;!outfile.eof();i++)
    {
        outfile>> temp1>>temp2;
        temp.x=temp1;
        temp.y=temp2;
        p.push_back(temp);
    }
    contours.push_back(p);
    for(int i = 0; i < contours.size(); i++)
    {
        cout<<contours[i]<<endl;
    }
    // outfile.close();
/************************读取保存坐标文件并输出到vector容器中******************************/


/******************************逼近拟合、画轮廓*****************************************/ 
    vector<vector<Point>> lines(contours.size());
    for(int i=0;i<contours.size();i++)
    {
        approxPolyDP(contours[i],lines[i],30,true);
        drawContours(TrackPic, lines, i, Scalar(0, 255, 255), 2, 8);  //绘制
/******************************逼近拟合、画轮廓*****************************************/ 


/**************************************形状判断*******************************************/               
        if(lines[i].size()==2)
        {
            vector<Point>m;
            vector<vector<Point>>::iterator it;
            vector<Point>::iterator it1;
            for(it=lines.begin();it!=lines.end();it++)
            {
                //cout<<*it<<endl;
                for(it1=(*it).begin();it1!=(*it).end();it1++)
                {
                    //vector<Point>m;
                    m.push_back(*it1);
                    //cout<<*it1<<endl;
                    //cout<<(*it1).x<<','<<(*it1).y<<endl;
                }
                //cout<<m[1].x<<endl;
                a=m[1].x;
                b=m[0].x;
                c=m[1].y;
                d=m[0].y;
                s=(c-d)/(a-b);
                if(-1<s && s<1)
                {   
                    cout<<"水平线"<<endl;
                }
                else
                {
                    cout<<"垂直线"<<endl;
                }                    
            cout<<"s:"<<s<<endl;
            cout<<"c-d:"<<c-d<<endl;
            cout<<"a-b:"<<a-b<<endl;
            cout<<"a:"<<a<<endl;
            cout<<"b:"<<b<<endl;
            cout<<"c:"<<c<<endl;
            cout<<"d:"<<d<<endl;
            }                     
        }
            else if(lines[i].size()==3)
            {
                cout<<"三角形"<<endl;
            }
            else if(lines[i].size()==4)
            {
                cout<<"四边形"<<endl;
            }
            else if(lines[i].size()==5)
            {
                cout<<"五边形"<<endl;
            }
            else if(lines[i].size()>5)
            {   
                Point2f center; float radius;
		        minEnclosingCircle(lines[i],center,radius);
		        circle(TrackPic,center,radius,Scalar(255),2);
                imshow("circle",TrackPic);
                cout<<"圆"<<endl;
            }
            else
            {
                cout<<"none"<<endl;
            }
        cout<<lines[i]<<endl;
/**************************************形状判断*******************************************/  
    }       namedWindow("1");
            imshow("1",src);    
            imshow("approx",TrackPic);
            waitKey(0);
            return 0;
}

