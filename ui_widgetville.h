/********************************************************************************
** Form generated from reading UI file 'widgetville.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETVILLE_H
#define UI_WIDGETVILLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widgetville
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_8;
    QLabel *textdateville;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *texthumiville;
    QLabel *label_6;
    QLabel *label;
    QLabel *label_4;
    QLabel *textdescville;
    QHBoxLayout *horizontalLayout;
    QLabel *texttempville;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *textpressville;
    QLabel *label_7;
    QLabel *label_3;

    void setupUi(QWidget *widgetville)
    {
        if (widgetville->objectName().isEmpty())
            widgetville->setObjectName(QString::fromUtf8("widgetville"));
        widgetville->resize(618, 408);
        verticalLayout = new QVBoxLayout(widgetville);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        label_8 = new QLabel(widgetville);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout->addWidget(label_8);

        textdateville = new QLabel(widgetville);
        textdateville->setObjectName(QString::fromUtf8("textdateville"));

        verticalLayout->addWidget(textdateville);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(widgetville);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        texthumiville = new QLabel(widgetville);
        texthumiville->setObjectName(QString::fromUtf8("texthumiville"));

        horizontalLayout_2->addWidget(texthumiville);

        label_6 = new QLabel(widgetville);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);


        gridLayout->addLayout(horizontalLayout_2, 1, 1, 1, 1);

        label = new QLabel(widgetville);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_4 = new QLabel(widgetville);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        textdescville = new QLabel(widgetville);
        textdescville->setObjectName(QString::fromUtf8("textdescville"));

        gridLayout->addWidget(textdescville, 3, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        texttempville = new QLabel(widgetville);
        texttempville->setObjectName(QString::fromUtf8("texttempville"));

        horizontalLayout->addWidget(texttempville);

        label_5 = new QLabel(widgetville);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        textpressville = new QLabel(widgetville);
        textpressville->setObjectName(QString::fromUtf8("textpressville"));

        horizontalLayout_3->addWidget(textpressville);

        label_7 = new QLabel(widgetville);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_3->addWidget(label_7);


        gridLayout->addLayout(horizontalLayout_3, 2, 1, 1, 1);

        label_3 = new QLabel(widgetville);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(widgetville);

        QMetaObject::connectSlotsByName(widgetville);
    } // setupUi

    void retranslateUi(QWidget *widgetville)
    {
        widgetville->setWindowTitle(QCoreApplication::translate("widgetville", "Form", nullptr));
        label_8->setText(QCoreApplication::translate("widgetville", "Date :", nullptr));
        textdateville->setText(QCoreApplication::translate("widgetville", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("widgetville", "Humidite :", nullptr));
        texthumiville->setText(QCoreApplication::translate("widgetville", "TextLabel", nullptr));
        label_6->setText(QCoreApplication::translate("widgetville", "%", nullptr));
        label->setText(QCoreApplication::translate("widgetville", "Temperature :", nullptr));
        label_4->setText(QCoreApplication::translate("widgetville", "Description: ", nullptr));
        textdescville->setText(QCoreApplication::translate("widgetville", "TextLabel", nullptr));
        texttempville->setText(QCoreApplication::translate("widgetville", "TextLabel", nullptr));
        label_5->setText(QCoreApplication::translate("widgetville", "\302\260C", nullptr));
        textpressville->setText(QCoreApplication::translate("widgetville", "TextLabel", nullptr));
        label_7->setText(QCoreApplication::translate("widgetville", "hpa", nullptr));
        label_3->setText(QCoreApplication::translate("widgetville", "Pression :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widgetville: public Ui_widgetville {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETVILLE_H
