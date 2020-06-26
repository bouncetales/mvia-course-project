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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
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
    QPushButton *pushButton_EXIT;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *pushButton_OpenImage;
    QPushButton *pushButton_openvideo;
    QPushButton *pushButton_opencamera;
    QWidget *tab_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(634, 369);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_EXIT = new QPushButton(centralWidget);
        pushButton_EXIT->setObjectName(QStringLiteral("pushButton_EXIT"));
        pushButton_EXIT->setGeometry(QRect(510, 270, 91, 31));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 601, 271));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        pushButton_OpenImage = new QPushButton(tab);
        pushButton_OpenImage->setObjectName(QStringLiteral("pushButton_OpenImage"));
        pushButton_OpenImage->setGeometry(QRect(10, 20, 91, 51));
        QFont font;
        font.setItalic(true);
        pushButton_OpenImage->setFont(font);
        pushButton_openvideo = new QPushButton(tab);
        pushButton_openvideo->setObjectName(QStringLiteral("pushButton_openvideo"));
        pushButton_openvideo->setGeometry(QRect(10, 90, 91, 51));
        pushButton_openvideo->setFont(font);
        pushButton_opencamera = new QPushButton(tab);
        pushButton_opencamera->setObjectName(QStringLiteral("pushButton_opencamera"));
        pushButton_opencamera->setGeometry(QRect(10, 154, 91, 51));
        pushButton_opencamera->setFont(font);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 634, 22));
        MainWindow->setMenuBar(menuBar);
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
        pushButton_EXIT->setText(QApplication::translate("MainWindow", "EXIT", Q_NULLPTR));
        pushButton_OpenImage->setText(QApplication::translate("MainWindow", "Open Image", Q_NULLPTR));
        pushButton_openvideo->setText(QApplication::translate("MainWindow", "Open video", Q_NULLPTR));
        pushButton_opencamera->setText(QApplication::translate("MainWindow", "Open Camera", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "image", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
