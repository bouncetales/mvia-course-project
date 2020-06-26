/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *pushButton_exit;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *pushButton_open;
    QPushButton *pushButton_open_video;
    QPushButton *pushButton_open_camera;
    QPushButton *video_circle;
    QPushButton *camera_circle;
    QWidget *tab_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(745, 516);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 30, 141, 31));
        pushButton_exit = new QPushButton(centralWidget);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(580, 430, 99, 27));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(70, 110, 581, 301));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        pushButton_open = new QPushButton(tab);
        pushButton_open->setObjectName(QStringLiteral("pushButton_open"));
        pushButton_open->setGeometry(QRect(48, 50, 111, 61));
        pushButton_open_video = new QPushButton(tab);
        pushButton_open_video->setObjectName(QStringLiteral("pushButton_open_video"));
        pushButton_open_video->setGeometry(QRect(240, 50, 111, 61));
        pushButton_open_camera = new QPushButton(tab);
        pushButton_open_camera->setObjectName(QStringLiteral("pushButton_open_camera"));
        pushButton_open_camera->setGeometry(QRect(50, 120, 111, 61));
        video_circle = new QPushButton(tab);
        video_circle->setObjectName(QStringLiteral("video_circle"));
        video_circle->setGeometry(QRect(240, 120, 111, 61));
        camera_circle = new QPushButton(tab);
        camera_circle->setObjectName(QStringLiteral("camera_circle"));
        camera_circle->setGeometry(QRect(50, 190, 111, 61));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "MV PROJECT", Q_NULLPTR));
        pushButton_exit->setText(QApplication::translate("MainWindow", "exit", Q_NULLPTR));
        pushButton_open->setText(QApplication::translate("MainWindow", "open_image", Q_NULLPTR));
        pushButton_open_video->setText(QApplication::translate("MainWindow", "open_video", Q_NULLPTR));
        pushButton_open_camera->setText(QApplication::translate("MainWindow", "open_camera", Q_NULLPTR));
        video_circle->setText(QApplication::translate("MainWindow", "video_circle", Q_NULLPTR));
        camera_circle->setText(QApplication::translate("MainWindow", "camera_circle", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
