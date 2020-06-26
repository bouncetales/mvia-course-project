#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
    Mat img, gray;
    if( argc != 2 || !(img=imread(argv[1], 0)).data)
        return -1;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    // smooth it, otherwise a lot of false circles may be detected
    GaussianBlur( gray, gray, Size(9, 9), 2, 2 );
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT,
                 2, gray.rows/4, 200, 100 );
    for( size_t i = 0; i < circles.size(); i++ )
    {
int cir_x = circles[i][0];
int cir_y = circles[i][1];
int cir_r = circles[i][2];

line(img,Point(cir_x-5,cir_y),Point(cir_x+5,cir_y),Scalar(0,0,255),3,LINE_8,0);
line(img,Point(cir_x,cir_y-5),Point(cir_x,cir_y+5),Scalar(0,0,255),3,LINE_8,0);    
 // draw the circle outline
         circle( img, Point(cir_x,cir_y), cir_r, Scalar(0,255,0), 3, 8, 0 );

         

    }
    namedWindow( "circles", 0 );
    resizeWindow("circles",300,300);
    imshow( "circles", img );
    waitKey(0);
    return 0;
}
