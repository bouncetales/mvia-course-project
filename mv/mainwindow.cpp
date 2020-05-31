#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "asmOpenCV.h"

#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion
#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>  // OpenCV window I/O
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage image = reader.read();
    if (image.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1.").arg(QDir::toNativeSeparators(fileName)));
        setWindowFilePath(QString());
        iv.imageLabel->setPixmap(QPixmap());
        iv.imageLabel->adjustSize();
        return false;
    }
//! [2] //! [3]
    iv.imageLabel->setPixmap(QPixmap::fromImage(image));
//! [3] //! [4]
    iv.scaleFactor = 1.0;

    //printAct->setEnabled(true);
    iv.fitToWindowAct->setEnabled(true);
    iv.updateActions();

    if (!iv.fitToWindowAct->isChecked())
        iv.imageLabel->adjustSize();

    setWindowFilePath(fileName);
    iv.show();
    return true;
}

bool MainWindow::loadVideo(const QString &fileName)
{
//    QImageReader reader(fileName);
//    reader.setAutoTransform(true);
//    const QImage image = reader.read();
    using namespace cv;
    using namespace std;
     VideoCapture video(fileName.toStdString());
     int frameNum = -1;
    if (!video.isOpened()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1.").arg(QDir::toNativeSeparators(fileName)));
        setWindowFilePath(QString());
        iv.imageLabel->setPixmap(QPixmap());
        iv.imageLabel->adjustSize();
        return false;
    }
    video >> frame;
    ++frameNum;
    image = ASM::cvMatToQImage(frame);
//! [2] //! [3]
    iv.imageLabel->setPixmap(QPixmap::fromImage(image));
//! [3] //! [4]
    iv.scaleFactor = 1.0;

    //printAct->setEnabled(true);
    iv.fitToWindowAct->setEnabled(true);
    iv.updateActions();

    if (!iv.fitToWindowAct->isChecked())
        iv.imageLabel->adjustSize();

    setWindowFilePath(fileName);
    iv.show();
    while(1){
        video >> frame;
        if (frame.empty())
                {
                    cout << " < < <  Game over!  > > > ";
                    break;
                }
        ++frameNum;
        image = ASM::cvMatToQImage(frame);
    //! [2] //! [3]
        iv.imageLabel->setPixmap(QPixmap::fromImage(image));
    //! [3] //! [4]
        iv.scaleFactor = 1.0;

        //printAct->setEnabled(true);
        iv.fitToWindowAct->setEnabled(true);
        iv.updateActions();

        if (!iv.fitToWindowAct->isChecked())
            iv.imageLabel->adjustSize();

        setWindowFilePath(fileName);
        iv.update();
        char c = (char)waitKey(20);
    }
    return true;
}

bool MainWindow::OpenCamera()
{
//    QImageReader reader(fileName);
//    reader.setAutoTransform(true);
//    const QImage image = reader.read();
    using namespace cv;
    using namespace std;
     VideoCapture video;
     int frameNum = -1;
    if (!video.open(0)) {
//        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
//                                 tr("Cannot load %1.").arg(QDir::toNativeSeparators(fileName)));
//        setWindowFilePath(QString());
        cout << "Open Camera failed!"<< endl;
//        iv.imageLabel->setPixmap(QPixmap());
//        iv.imageLabel->adjustSize();
        return false;
    }
    video >> frame;
    ++frameNum;
    image = ASM::cvMatToQImage(frame);
//! [2] //! [3]
    iv.imageLabel->setPixmap(QPixmap::fromImage(image));
//! [3] //! [4]
    iv.scaleFactor = 1.0;

    //printAct->setEnabled(true);
    iv.fitToWindowAct->setEnabled(true);
    iv.updateActions();

    if (!iv.fitToWindowAct->isChecked())
        iv.imageLabel->adjustSize();

//    setWindowFilePath(fileName);
    iv.show();
    while(1){
        video >> frame;
        if (iv.isHidden()){
            video.release();
            break;
        }
//                {
//                    cout << " < < <  Game over!  > > > ";
//                    break;
//                }
        ++frameNum;
        image = ASM::cvMatToQImage(frame);
    //! [2] //! [3]
        iv.imageLabel->setPixmap(QPixmap::fromImage(image));
    //! [3] //! [4]
        iv.scaleFactor = 1.0;

        //printAct->setEnabled(true);
        iv.fitToWindowAct->setEnabled(true);
        iv.updateActions();

        if (!iv.fitToWindowAct->isChecked())
            iv.imageLabel->adjustSize();

//        setWindowFilePath(fileName);
        iv.update();
        char c = (char)waitKey(20);
    }
    return true;
}

void MainWindow::on_pushButton_EXIT_clicked()
{
   this->close();
}

void MainWindow::on_pushButton_OpenImage_clicked()
{
      QStringList mimeTypeFilters;
        foreach (const QByteArray &mimeTypeName, QImageReader::supportedMimeTypes())
            mimeTypeFilters.append(mimeTypeName);
        mimeTypeFilters.sort();
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        QFileDialog dialog(this, tr("Open File"),
                           picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
        dialog.setAcceptMode(QFileDialog::AcceptOpen);
        dialog.setMimeTypeFilters(mimeTypeFilters);
        dialog.selectMimeTypeFilter("image/jpeg");

        while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}

}

void MainWindow::on_pushButton_openvideo_clicked()
{
    QStringList mimeTypeFilters;
//      foreach (const QByteArray &mimeTypeName, QImageReader::supportedMimeTypes())
          mimeTypeFilters.append("video/avi");
      mimeTypeFilters.sort();
      const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
      QFileDialog dialog(this, tr("Open File"),
                         picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
      dialog.setAcceptMode(QFileDialog::AcceptOpen);
      dialog.setMimeTypeFilters(mimeTypeFilters);
      dialog.selectMimeTypeFilter("video/avi");

      while (dialog.exec() == QDialog::Accepted && !loadVideo(dialog.selectedFiles().first())) {}
}


void MainWindow::on_pushButton_opencamera_clicked()
{
    OpenCamera();
}

int MainWindow::on_pushButton_cameratrack_clicked()
{

    using namespace cv;
    using namespace std;
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
        vector<Vec3f>circles;
/*********************************霍夫变换检测圆,画出轮廓、中心点******************************/
        HoughCircles(midImage,circles,CV_HOUGH_GRADIENT,1.5,100,150,100,0,0);

        for(size_t i=0;i<circles.size();i++)
        {
            Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            circle(frame,center,3,Scalar(0,255,0),-1,8,0);
            circle(frame,center,radius,Scalar(155,50,255),3,8,0);
            printf("x=%d,y=%d\n",cvRound(circles[i][0]),cvRound(circles[i][1]));
            line(TrackPic,Point(center.x,center.y),Point(center.x,center.y),Scalar(255, 255, 0), 2);
/*********************************霍夫变换检测圆,画出轮廓、中心点******************************/

/*************************************存、画轨迹点*********************************************/
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
/*************************************存、画轨迹点*********************************************/
        }
        // namedWindow("1");
        // imshow("1",TrackPic);
        // imwrite("1.jpg",TrackPic);
        namedWindow("result");
        imshow("result",frame);
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

int MainWindow::on_pushButton_approx_clicked()
{
    using namespace cv;
    using namespace std;
    Mat src;
    src=imread("1.jpg");
    float a,b,c,d,s;
    Mat TrackPic=cv::Mat::zeros(500,500,CV_8UC3);
    vector<vector<Point>> contours;
    vector<Point>p;
/************************读取保存坐标文件并输出到vector容器中******************************/
    ifstream outfile;
    outfile.open("vector.txt");
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
    // for(int i = 0; i < contours.size(); i++)
    // {
    //     cout<<contours[i]<<endl;
    // }
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
            cout<<s<<endl;
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
            else if(lines[i].size()>10)
            {
                cout<<"圆"<<endl;
            }
            else
            {
                cout<<"none"<<endl;
            }
        cout<<lines[i]<<endl;
/**************************************形状判断*******************************************/
    }
    namedWindow("1");
    imshow("1",src);
    imshow("approx",TrackPic);
    waitKey(0);
    return 0;
}
