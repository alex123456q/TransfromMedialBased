#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <stdio.h>
#include <iostream>

#include <QWidget>
#include <QImage>
#include <QPainter>

#include "SkeletonDemoGUI/SkeletonLib/BSTrans.h"


class MyWidget : public QWidget
{
    Q_OBJECT
public:
    MyWidget(QWidget *parent = 0):QWidget(parent){}
    TPolFigure *skeleton;
//    std::vector<TNode*> pivNodes;
    //virtual QImage getImage() = 0;
    virtual std::vector<TNode*> getPivots(){std::cout<<"in my widget ";return std::vector<TNode*>();};
    QImage getImage(){
        QImage img(this->size(), QImage::Format_ARGB32);
        QPainter painter(&img);
        this->render(&painter);
        return img;
    }
public slots:
    virtual void savePolygons(){
        std::cout << ("saving");
    }

//protected:
//    void keyPressEvent(QKeyEvent*);
//    void mousePressEvent(QMouseEvent*);
//    void mouseDoubleClickEvent(QMouseEvent*);
//    void mouseMoveEvent(QMouseEvent*);
//    void paintEvent(QPaintEvent *);

//private:
//    QImage* mainImage;
//    int xPr, yPr;
//    bool pressed;
//    bool newPol;
//    std::vector<Polygon> polygons;
//    QPixmap   pixmap;

//    void paintTrace(const QPoint&, int);
//    void setVertex(const QPoint&, bool);
//    void paint(QPainter*, const QPoint&);
};
#endif // MYWIDGET_H
