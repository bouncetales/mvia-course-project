#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>
#include<opencv2/core.hpp>
//#include <QMainWindow>
#include "imageviewer.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_open_clicked();

    void on_pushButton_open_video_clicked();

    void on_pushButton_open_camera_clicked();

    void on_video_circle_clicked();

    void on_camera_circle_clicked();

    void on_camera_circle1_clicked();

private:
    Ui::MainWindow *ui;
    ImageViewer iv;
    QImage image;
    cv::Mat frame;
    cv::Mat frame1;
    cv::Mat img,gray;
    bool loadFile(const QString &);
    bool loadVideo(const QString &);
    bool OpenCamera();
    bool loadVideocircle(const QString &);
    bool OpenCameracircle();
    bool OpenCameracircle1();
};

#endif // MAINWINDOW_H
