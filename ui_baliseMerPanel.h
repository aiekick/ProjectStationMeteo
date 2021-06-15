/********************************************************************************
** Form generated from reading UI file 'baliseMerPanel.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BALISEMERPANEL_H
#define UI_BALISEMERPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_baliseMerPanel
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_Refresh;
    QLabel *label;
    QLabel *label_Temperature_Mer;
    QLabel *label_4;
    QLabel *label_Pressure_Mer;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_Humidity_Mer;
    QLabel *label_8;
    QPushButton *pushButton_Degrees;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *baliseMerPanel)
    {
        if (baliseMerPanel->objectName().isEmpty())
            baliseMerPanel->setObjectName(QString::fromUtf8("baliseMerPanel"));
        baliseMerPanel->resize(589, 253);
        centralWidget = new QWidget(baliseMerPanel);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton_Refresh = new QPushButton(centralWidget);
        pushButton_Refresh->setObjectName(QString::fromUtf8("pushButton_Refresh"));
        pushButton_Refresh->setGeometry(QRect(90, 90, 80, 21));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(220, 50, 47, 13));
        label_Temperature_Mer = new QLabel(centralWidget);
        label_Temperature_Mer->setObjectName(QString::fromUtf8("label_Temperature_Mer"));
        label_Temperature_Mer->setGeometry(QRect(290, 50, 47, 13));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(230, 80, 47, 13));
        label_Pressure_Mer = new QLabel(centralWidget);
        label_Pressure_Mer->setObjectName(QString::fromUtf8("label_Pressure_Mer"));
        label_Pressure_Mer->setGeometry(QRect(290, 80, 47, 13));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(350, 80, 47, 13));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(230, 110, 47, 13));
        label_Humidity_Mer = new QLabel(centralWidget);
        label_Humidity_Mer->setObjectName(QString::fromUtf8("label_Humidity_Mer"));
        label_Humidity_Mer->setGeometry(QRect(300, 110, 47, 13));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(360, 110, 47, 13));
        pushButton_Degrees = new QPushButton(centralWidget);
        pushButton_Degrees->setObjectName(QString::fromUtf8("pushButton_Degrees"));
        pushButton_Degrees->setGeometry(QRect(350, 50, 31, 21));
        baliseMerPanel->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(baliseMerPanel);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 589, 20));
        baliseMerPanel->setMenuBar(menuBar);
        mainToolBar = new QToolBar(baliseMerPanel);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        baliseMerPanel->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(baliseMerPanel);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        baliseMerPanel->setStatusBar(statusBar);

        retranslateUi(baliseMerPanel);

        QMetaObject::connectSlotsByName(baliseMerPanel);
    } // setupUi

    void retranslateUi(QMainWindow *baliseMerPanel)
    {
        baliseMerPanel->setWindowTitle(QCoreApplication::translate("baliseMerPanel", "baliseMerPanel", nullptr));
        pushButton_Refresh->setText(QCoreApplication::translate("baliseMerPanel", "Refresh", nullptr));
        label->setText(QCoreApplication::translate("baliseMerPanel", "Temperature :", nullptr));
        label_Temperature_Mer->setText(QCoreApplication::translate("baliseMerPanel", "TextLabel", nullptr));
        label_4->setText(QCoreApplication::translate("baliseMerPanel", "Pression : ", nullptr));
        label_Pressure_Mer->setText(QCoreApplication::translate("baliseMerPanel", "TextLabel", nullptr));
        label_6->setText(QCoreApplication::translate("baliseMerPanel", "hPa", nullptr));
        label_5->setText(QCoreApplication::translate("baliseMerPanel", "Humidit\303\251 :", nullptr));
        label_Humidity_Mer->setText(QCoreApplication::translate("baliseMerPanel", "TextLabel", nullptr));
        label_8->setText(QCoreApplication::translate("baliseMerPanel", "%", nullptr));
        pushButton_Degrees->setText(QCoreApplication::translate("baliseMerPanel", "\302\260C", nullptr));
    } // retranslateUi

};

namespace Ui {
    class baliseMerPanel: public Ui_baliseMerPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BALISEMERPANEL_H
