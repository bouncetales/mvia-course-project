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

//    printAct->setEnabled(true);
    iv.fitToWindowAct->setEnabled(true);
    iv.updateActions();

    if (!iv.fitToWindowAct->isChecked())
        iv.imageLabel->adjustSize();

    setWindowFilePath(fileName);
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

//    printAct->setEnabled(true);
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

    //    printAct->setEnabled(true);
        iv.fitToWindowAct->setEnabled(true);
        iv.updateActions();

        if (!iv.fitToWindowAct->isChecked())
            iv.imageLabel->adjustSize();

        setWindowFilePath(fileName);
        iv.update();
        char c = (char)waitKey(50);
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
        std::cout << "Opencv Camera failed!"<< std::endl;
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

//    printAct->setEnabled(true);
    iv.fitToWindowAct->setEnabled(true);
    iv.updateActions();

    if (!iv.fitToWindowAct->isChecked())
        iv.imageLabel->adjustSize();

   // setWindowFilePath(fileName);
    iv.show();


    while(1){
        video >> frame;
        if(iv.isHidden()){
           video.release();
           break;
        }
        ++frameNum;
        image = ASM::cvMatToQImage(frame);
    //! [2] //! [3]
        iv.imageLabel->setPixmap(QPixmap::fromImage(image));
    //! [3] //! [4]
        iv.scaleFactor = 1.0;

    //    printAct->setEnabled(true);
        iv.fitToWindowAct->setEnabled(true);
        iv.updateActions();

        if (!iv.fitToWindowAct->isChecked())
            iv.imageLabel->adjustSize();

        //setWindowFilePath(fileName);
        iv.update();
        char c = (char)waitKey(20);
    }
    return true;
}

bool MainWindow::loadVideocircle(const QString &fileName)
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
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        // smooth it, otherwise a lot of false circles may be detected
        GaussianBlur( gray, gray, Size(3,3), 2, 2 );
        vector<Vec3f> circles;
        HoughCircles(gray, circles, HOUGH_GRADIENT,
                     2, gray.rows/4, 15, 85 );
        for( size_t i = 0; i < circles.size(); i++ )
        {
            int cir_x = circles[i][0];
            int cir_y = circles[i][1];
            int cir_r = circles[i][2];

            line(frame,Point(cir_x-5,cir_y),Point(cir_x+5,cir_y),Scalar(0,0,255),3,LINE_8,0);
            line(frame,Point(cir_x,cir_y-5),Point(cir_x,cir_y+5),Scalar(0,0,255),3,LINE_8,0);
             // draw the circle outline
            circle( frame, Point(cir_x,cir_y), cir_r, Scalar(0,255,0), 3, 8, 0 );
        }
    ++frameNum;
    image = ASM::cvMatToQImage(frame);
//! [2] //! [3]
    iv.imageLabel->setPixmap(QPixmap::fromImage(image));
//! [3] //! [4]
    iv.scaleFactor = 1.0;

//    printAct->setEnabled(true);
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
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        // smooth it, otherwise a lot of false circles may be detected
        GaussianBlur( gray, gray, Size(3, 3), 2, 2 );
        vector<Vec3f> circles;
        HoughCircles(gray, circles, HOUGH_GRADIENT,
                     2, gray.rows/4, 15, 85 );
        for( size_t i = 0; i < circles.size(); i++ )
        {
            int cir_x = circles[i][0];
            int cir_y = circles[i][1];
            int cir_r = circles[i][2];

            line(frame,Point(cir_x-5,cir_y),Point(cir_x+5,cir_y),Scalar(0,0,255),3,LINE_8,0);
            line(frame,Point(cir_x,cir_y-5),Point(cir_x,cir_y+5),Scalar(0,0,255),3,LINE_8,0);
             // draw the circle outline
            circle( frame, Point(cir_x,cir_y), cir_r, Scalar(0,255,0), 3, 8, 0 );
        }

        ++frameNum;
        image = ASM::cvMatToQImage(frame);
    //! [2] //! [3]
        iv.imageLabel->setPixmap(QPixmap::fromImage(image));
    //! [3] //! [4]
        iv.scaleFactor = 1.0;

    //    printAct->setEnabled(true);
        iv.fitToWindowAct->setEnabled(true);
        iv.updateActions();

        if (!iv.fitToWindowAct->isChecked())
            iv.imageLabel->adjustSize();

        setWindowFilePath(fileName);
        iv.update();
        char c = (char)waitKey(100);
    }
    return true;
}
bool MainWindow::OpenCameracircle()
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
        std::cout << "Opencv Camera failed!"<< std::endl;
//        iv.imageLabel->setPixmap(QPixmap());
//        iv.imageLabel->adjustSize();
        return false;
    }
    video >> frame;
//    cvtColor(frame, gray, COLOR_BGR2GRAY);
//    // smooth it, otherwise a lot of false circles may be detected
//    GaussianBlur( gray, gray, Size(9, 9), 2, 2 );
//    vector<Vec3f> circles;
//    HoughCircles(gray, circles, HOUGH_GRADIENT,
//                 2, gray.rows/4, 100, 50 );
//    for( size_t i = 0; i < circles.size(); i++ )
//    {
//        int cir_x = circles[i][0];
//        int cir_y = circles[i][1];
//        int cir_r = circles[i][2];

//        line(frame,Point(cir_x-5,cir_y),Point(cir_x+5,cir_y),Scalar(0,0,255),3,LINE_8,0);
//        line(frame,Point(cir_x,cir_y-5),Point(cir_x,cir_y+5),Scalar(0,0,255),3,LINE_8,0);
//         // draw the circle outline
//        circle( frame, Point(cir_x,cir_y), cir_r, Scalar(0,255,0), 3, 8, 0 );
//    }
    ++frameNum;
    image = ASM::cvMatToQImage(frame);
//! [2] //! [3]
    iv.imageLabel->setPixmap(QPixmap::fromImage(image));
//! [3] //! [4]
    iv.scaleFactor = 1.0;

//    printAct->setEnabled(true);
    iv.fitToWindowAct->setEnabled(true);
    iv.updateActions();

    if (!iv.fitToWindowAct->isChecked())
        iv.imageLabel->adjustSize();

   // setWindowFilePath(fileName);
    iv.show();
    int a=0,b=0;
    int x[a];
    int y[b];


    while(1){
        video >> frame;
        frame1=frame.clone();
        cvtColor(frame1, gray, COLOR_BGR2GRAY);
        // smooth it, otherwise a lot of false circles may be detected
      //  GaussianBlur( gray, gray, Size(3, 3), 2, 2 );
        vector<Vec3f> circles;
        HoughCircles(gray, circles, HOUGH_GRADIENT,
                     2, gray.rows/4, 30, 150 );
        for( size_t i = 0; i < circles.size(); i++ )
        {
            int cir_x = circles[i][0];
            int cir_y = circles[i][1];
//           int cir_r = circles[i][2];
            x[a]=cir_x;
            y[b]=cir_y;
//            line(frame,Point(cir_x-5,cir_y),Point(cir_x+5,cir_y),Scalar(0,0,255),3,LINE_8,0);
//            line(frame,Point(cir_x,cir_y-5),Point(cir_x,cir_y+5),Scalar(0,0,255),3,LINE_8,0);
//             // draw the circle outline
//            circle( frame, Point(cir_x,cir_y), cir_r, Scalar(0,255,0), 3, 8, 0 );

//            for(int g=0;g<=a;g++)
//            {
//                line(frame,Point(x[g]-5,y[g]),Point(x[g]+5,y[g]),Scalar(0,0,255),3,LINE_8,0);
//                line(frame,Point(x[g],y[g]-5),Point(x[g],y[g]+5),Scalar(0,0,255),3,LINE_8,0);
//                // draw the circle outline
//                circle( frame, Point(x[g],y[g]), cir_r, Scalar(0,255,0), 3, 8, 0 );
//            }
        }
        for(int g=0;g<=a;g++)
        {
            line(frame,Point(x[g]-5,y[g]),Point(x[g]+5,y[g]),Scalar(0,0,255),3,LINE_8,0);
            line(frame,Point(x[g],y[g]-5),Point(x[g],y[g]+5),Scalar(0,0,255),3,LINE_8,0);
//                 // draw the circle outline
//                circle( frame, Point(x[g],y[g]), cir_r, Scalar(0,255,0), 3, 8, 0 );
        }
        a++;
        b++;
        if(iv.isHidden()){
           video.release();
           break;
        }
        ++frameNum;
        image = ASM::cvMatToQImage(frame);
    //! [2] //! [3]
        iv.imageLabel->setPixmap(QPixmap::fromImage(image));
    //! [3] //! [4]
        iv.scaleFactor = 1.0;

    //    printAct->setEnabled(true);
        iv.fitToWindowAct->setEnabled(true);
        iv.updateActions();

        if (!iv.fitToWindowAct->isChecked())
            iv.imageLabel->adjustSize();

        //setWindowFilePath(fileName);
        iv.update();
        char c = (char)waitKey(20);
    }
    return true;
}


bool MainWindow::OpenCameracircle1()
{

    using namespace cv;
    using namespace std;
    VideoCapture video;
    int frameNum = -1;
    if (!video.open(0)) {

        std::cout << "Opencv Camera failed!"<< std::endl;

        return false;
    }
    video >> frame;

    ++frameNum;
    image = ASM::cvMatToQImage(frame);
//! [2] //! [3]
    iv.imageLabel->setPixmap(QPixmap::fromImage(image));
//! [3] //! [4]
    iv.scaleFactor = 1.0;

//    printAct->setEnabled(true);
    iv.fitToWindowAct->setEnabled(true);
    iv.updateActions();

    if (!iv.fitToWindowAct->isChecked())
        iv.imageLabel->adjustSize();

   // setWindowFilePath(fileName);
    iv.show();

    while(1){
        video >> frame;
        frame1=frame.clone();
        cvtColor(frame1, gray, COLOR_BGR2GRAY);
        // smooth it, otherwise a lot of false circles may be detected
        GaussianBlur( gray, gray, Size(9, 9), 2, 2 );
        vector<Vec3f> circles;
        HoughCircles(gray, circles, HOUGH_GRADIENT,
                     2, gray.rows/4, 50, 150 );
        for( size_t i = 0; i < circles.size(); i++ )
        {
            int cir_x = circles[i][0];
            int cir_y = circles[i][1];
            int cir_r = circles[i][2];

            line(frame,Point(cir_x-5,cir_y),Point(cir_x+5,cir_y),Scalar(0,0,255),3,LINE_8,0);
            line(frame,Point(cir_x,cir_y-5),Point(cir_x,cir_y+5),Scalar(0,0,255),3,LINE_8,0);
             // draw the circle outline
            circle( frame, Point(cir_x,cir_y), cir_r, Scalar(0,255,0), 3, 8, 0 );

        }


        if(iv.isHidden()){
           video.release();
           break;
        }
        ++frameNum;
        image = ASM::cvMatToQImage(frame);
    //! [2] //! [3]
        iv.imageLabel->setPixmap(QPixmap::fromImage(image));
    //! [3] //! [4]
        iv.scaleFactor = 1.0;

    //    printAct->setEnabled(true);
        iv.fitToWindowAct->setEnabled(true);
        iv.updateActions();

        if (!iv.fitToWindowAct->isChecked())
            iv.imageLabel->adjustSize();

        //setWindowFilePath(fileName);
        iv.update();
        char c = (char)waitKey(20);
    }
    return true;
}


void MainWindow::on_pushButton_exit_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_open_clicked()
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
        iv.show();
}

void MainWindow::on_pushButton_open_video_clicked()
{
    QStringList mimeTypeFilters;
//    foreach (const QByteArray &mimeTypeName, QImageReader::supportedMimeTypes())

    mimeTypeFilters.append("video/avi");
    mimeTypeFilters.sort();
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QFileDialog dialog(this, tr("Open File"),
                       picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("video/avi");


    while (dialog.exec() == QDialog::Accepted && !loadVideo(dialog.selectedFiles().first())) {}
        iv.show();
}

void MainWindow::on_pushButton_open_camera_clicked()
{
    OpenCamera();
}

void MainWindow::on_video_circle_clicked()
{
    QStringList mimeTypeFilters;
//    foreach (const QByteArray &mimeTypeName, QImageReader::supportedMimeTypes())

    mimeTypeFilters.append("video/avi");
    mimeTypeFilters.sort();
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QFileDialog dialog(this, tr("Open File"),
                       picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("video/avi");

    while (dialog.exec() == QDialog::Accepted && !loadVideocircle(
               dialog.selectedFiles().first())) {}
        iv.show();
}

void MainWindow::on_camera_circle_clicked()
{
    OpenCameracircle();
}

void MainWindow::on_camera_circle1_clicked()
{
    OpenCameracircle1();
}
