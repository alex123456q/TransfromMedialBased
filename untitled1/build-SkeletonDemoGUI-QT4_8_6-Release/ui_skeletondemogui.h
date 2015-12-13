/********************************************************************************
** Form generated from reading UI file 'skeletondemogui.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKELETONDEMOGUI_H
#define UI_SKELETONDEMOGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "mypainter.h"

QT_BEGIN_NAMESPACE

class Ui_SkeletonDemoGUIClass
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    MyPainter *Painter;
    QVBoxLayout *menuLayout;
    QPushButton *openImageButton;
    QPushButton *saveImageButton;
    QPushButton *refreshSkeletonButton;
    QPushButton *savePolyButton;
    QLabel *label;
    QSpinBox *pruning;
    QLabel *label_2;
    QSpinBox *area;
    QCheckBox *invertCheckBox;
    QLabel *filenameLabel;
    QLabel *timeLabel;
    QSpacerItem *verticalSpacer;
    QCheckBox *imageCB;
    QCheckBox *bonesCB;
    QCheckBox *circlesCB;
    QCheckBox *contoursCB;

    void setupUi(QMainWindow *SkeletonDemoGUIClass)
    {
        if (SkeletonDemoGUIClass->objectName().isEmpty())
            SkeletonDemoGUIClass->setObjectName(QString::fromUtf8("SkeletonDemoGUIClass"));
        SkeletonDemoGUIClass->resize(771, 622);
        centralWidget = new QWidget(SkeletonDemoGUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 751, 942));
        horizontalLayout = new QHBoxLayout(verticalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Painter = new MyPainter(verticalLayoutWidget);
        Painter->setObjectName(QString::fromUtf8("Painter"));

        horizontalLayout->addWidget(Painter);

        menuLayout = new QVBoxLayout();
        menuLayout->setSpacing(5);
        menuLayout->setObjectName(QString::fromUtf8("menuLayout"));
        openImageButton = new QPushButton(verticalLayoutWidget);
        openImageButton->setObjectName(QString::fromUtf8("openImageButton"));
        openImageButton->setMinimumSize(QSize(150, 34));
        openImageButton->setFlat(false);

        menuLayout->addWidget(openImageButton);

        saveImageButton = new QPushButton(verticalLayoutWidget);
        saveImageButton->setObjectName(QString::fromUtf8("saveImageButton"));
        saveImageButton->setMinimumSize(QSize(150, 34));

        menuLayout->addWidget(saveImageButton);

        refreshSkeletonButton = new QPushButton(verticalLayoutWidget);
        refreshSkeletonButton->setObjectName(QString::fromUtf8("refreshSkeletonButton"));
        refreshSkeletonButton->setMinimumSize(QSize(150, 34));

        menuLayout->addWidget(refreshSkeletonButton);

        savePolyButton = new QPushButton(verticalLayoutWidget);
        savePolyButton->setObjectName(QString::fromUtf8("savePolyButton"));

        menuLayout->addWidget(savePolyButton);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        menuLayout->addWidget(label);

        pruning = new QSpinBox(verticalLayoutWidget);
        pruning->setObjectName(QString::fromUtf8("pruning"));
        pruning->setMaximum(100000000);
        pruning->setValue(1);

        menuLayout->addWidget(pruning);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        menuLayout->addWidget(label_2);

        area = new QSpinBox(verticalLayoutWidget);
        area->setObjectName(QString::fromUtf8("area"));
        area->setMaximum(100000000);
        area->setValue(100);

        menuLayout->addWidget(area);

        invertCheckBox = new QCheckBox(verticalLayoutWidget);
        invertCheckBox->setObjectName(QString::fromUtf8("invertCheckBox"));

        menuLayout->addWidget(invertCheckBox);

        filenameLabel = new QLabel(verticalLayoutWidget);
        filenameLabel->setObjectName(QString::fromUtf8("filenameLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(filenameLabel->sizePolicy().hasHeightForWidth());
        filenameLabel->setSizePolicy(sizePolicy);

        menuLayout->addWidget(filenameLabel);

        timeLabel = new QLabel(verticalLayoutWidget);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));
        sizePolicy.setHeightForWidth(timeLabel->sizePolicy().hasHeightForWidth());
        timeLabel->setSizePolicy(sizePolicy);

        menuLayout->addWidget(timeLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        menuLayout->addItem(verticalSpacer);

        imageCB = new QCheckBox(verticalLayoutWidget);
        imageCB->setObjectName(QString::fromUtf8("imageCB"));
        imageCB->setChecked(true);

        menuLayout->addWidget(imageCB);

        bonesCB = new QCheckBox(verticalLayoutWidget);
        bonesCB->setObjectName(QString::fromUtf8("bonesCB"));
        bonesCB->setAutoFillBackground(false);
        bonesCB->setChecked(true);

        menuLayout->addWidget(bonesCB);

        circlesCB = new QCheckBox(verticalLayoutWidget);
        circlesCB->setObjectName(QString::fromUtf8("circlesCB"));
        circlesCB->setChecked(false);

        menuLayout->addWidget(circlesCB);

        contoursCB = new QCheckBox(verticalLayoutWidget);
        contoursCB->setObjectName(QString::fromUtf8("contoursCB"));
        contoursCB->setChecked(true);

        menuLayout->addWidget(contoursCB);


        horizontalLayout->addLayout(menuLayout);

        horizontalLayout->setStretch(0, 1);
        SkeletonDemoGUIClass->setCentralWidget(centralWidget);

        retranslateUi(SkeletonDemoGUIClass);

        QMetaObject::connectSlotsByName(SkeletonDemoGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *SkeletonDemoGUIClass)
    {
        SkeletonDemoGUIClass->setWindowTitle(QApplication::translate("SkeletonDemoGUIClass", "SkeletonDemoGUI", 0, QApplication::UnicodeUTF8));
        openImageButton->setText(QApplication::translate("SkeletonDemoGUIClass", "\320\236\320\261\321\200\320\260\320\261\320\276\321\202\320\260\321\202\321\214 \320\272\320\260\321\200\321\202\320\270\320\275\320\272\321\203", 0, QApplication::UnicodeUTF8));
        saveImageButton->setText(QApplication::translate("SkeletonDemoGUIClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\321\200\321\202\320\270\320\275\320\272\321\203", 0, QApplication::UnicodeUTF8));
        refreshSkeletonButton->setText(QApplication::translate("SkeletonDemoGUIClass", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \321\201\320\272\320\265\320\273\320\265\321\202", 0, QApplication::UnicodeUTF8));
        savePolyButton->setText(QApplication::translate("SkeletonDemoGUIClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\277\320\276\320\273\320\270\320\263\320\276\320\275\321\213", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SkeletonDemoGUIClass", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200 \321\201\321\202\321\200\320\270\320\266\320\272\320\270:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SkeletonDemoGUIClass", "\320\230\320\263\320\275\320\276\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\273\320\276\321\211\320\260\320\264\321\214 \320\274\320\265\320\275\321\214\321\210\320\265:", 0, QApplication::UnicodeUTF8));
        invertCheckBox->setText(QApplication::translate("SkeletonDemoGUIClass", "\320\230\320\275\320\262\320\265\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\272\320\260\321\200\321\202\320\270\320\275\320\272\321\203", 0, QApplication::UnicodeUTF8));
        filenameLabel->setText(QApplication::translate("SkeletonDemoGUIClass", "\320\230\320\274\321\217 \321\204\320\260\320\271\320\273\320\260:", 0, QApplication::UnicodeUTF8));
        timeLabel->setText(QApplication::translate("SkeletonDemoGUIClass", "\320\222\321\200\320\265\320\274\321\217:", 0, QApplication::UnicodeUTF8));
        imageCB->setText(QApplication::translate("SkeletonDemoGUIClass", "\320\230\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        bonesCB->setText(QApplication::translate("SkeletonDemoGUIClass", "\320\240\320\265\320\261\321\200\320\260", 0, QApplication::UnicodeUTF8));
        circlesCB->setText(QApplication::translate("SkeletonDemoGUIClass", "\320\232\321\200\321\203\320\263\320\270", 0, QApplication::UnicodeUTF8));
        contoursCB->setText(QApplication::translate("SkeletonDemoGUIClass", "\320\232\320\276\320\275\321\202\321\203\321\200\321\213", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SkeletonDemoGUIClass: public Ui_SkeletonDemoGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKELETONDEMOGUI_H
