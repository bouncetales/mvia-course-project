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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
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
    QPushButton *pushButton_cameratrack;
    QPushButton *pushButton_approx;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
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
        tabWidget->setGeometry(QRect(0, 0, 621, 271));
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
        pushButton_cameratrack = new QPushButton(tab);
        pushButton_cameratrack->setObjectName(QStringLiteral("pushButton_cameratrack"));
        pushButton_cameratrack->setGeometry(QRect(150, 20, 91, 51));
        pushButton_cameratrack->setFont(font);
        pushButton_approx = new QPushButton(tab);
        pushButton_approx->setObjectName(QStringLiteral("pushButton_approx"));
        pushButton_approx->setGeometry(QRect(150, 90, 91, 51));
        pushButton_approx->setFont(font);
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(430, 20, 121, 77));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

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
        pushButton_cameratrack->setText(QApplication::translate("MainWindow", "Camera track", Q_NULLPTR));
        pushButton_approx->setText(QApplication::translate("MainWindow", "Approx", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\347\224\265\344\277\241172", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "3170406056", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\351\203\221\345\272\267", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "image", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
