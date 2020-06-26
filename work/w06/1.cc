#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;
static void prewitte(Mat imageP)
{

        cvtColor(imageP,imageP,CV_RGB2GRAY);
        float prewittx[9] =
        {
                -1,0,1,
                -1,0,1,
                -1,0,1
        };
        float prewitty[9] =
        {
                1,1,1,
                0,0,0,
                -1,-1,-1
        };
        Mat px=Mat(3,3,CV_32F,prewittx);
        Mat py=Mat(3,3,CV_32F,prewitty);
        Mat dstx=Mat(imageP.size(),imageP.type(),imageP.channels());
        Mat dsty=Mat(imageP.size(),imageP.type(),imageP.channels());
        Mat dst=Mat(imageP.size(),imageP.type(),imageP.channels());
        filter2D(imageP,dstx,imageP.depth(),px);
        filter2D(imageP,dsty,imageP.depth(),py);
        float tempx,tempy,temp;
        for(int i=0;i<imageP.rows;i++)
        {
                for(int j=0;j<imageP.cols;j++)
                {
                        tempx=dstx.at<uchar>(i,j);
                        tempy=dsty.at<uchar>(i,j);
                        temp=sqrt(tempx*tempx+tempy*tempy);
                        dst.at<uchar>(i,j)=temp;
                }
        }
        namedWindow("prewitte",0);
	resizeWindow("prewitte",300,300);
        imshow("prewitte",dst);

}
int main()
{
            Mat  dst_org,dst1,dst2, dst3, dst4,sc3,sc4;
            Mat grad_x, grad_y,grad_x_abs, grad_y_abs,sc3_abs;
            Mat src = imread("1.jpg");
            namedWindow("org",0);
	    resizeWindow("org",300,300);
            imshow("org", src);

            cvtColor(src, dst2, COLOR_BGR2GRAY);
            blur(dst2, dst3, Size(3, 3));
            Sobel(dst3, grad_x, CV_16S, 1, 0, 3, 1, 1);
            Sobel(dst3, grad_y, CV_16S, 0,1, 3, 1, 1);
            convertScaleAbs( grad_x, grad_x_abs );
            convertScaleAbs( grad_y, grad_y_abs );
            addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5, 0, dst4);
            namedWindow("Sobel",0);
	    resizeWindow("Sobel",300,300);
            imshow("Sobel", dst4);

            prewitte(src);

            //GaussianBlur(src, dst_org, Size(3, 3), 0, 0, BORDER_DEFAULT);
            cvtColor(src, dst1, COLOR_RGB2GRAY);
            Laplacian(dst1, sc3, CV_16S, 3, 1, 0, BORDER_DEFAULT);
            convertScaleAbs(sc3, sc3_abs);
            namedWindow("laplace",0);
	    resizeWindow("laplace",300,300);
            imshow("laplace", sc3_abs);

            Canny(dst2,sc4,0,100,3);
            namedWindow("Canny",0);
       	    resizeWindow("Canny",300,300);
            imshow("Canny", sc4);

            waitKey(0);
            return 0;

}

