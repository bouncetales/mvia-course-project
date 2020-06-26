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
