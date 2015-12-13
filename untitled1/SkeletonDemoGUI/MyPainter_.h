#pragma once

#include <QWidget>
#include <QImage>
#include <QPainter>

#include "MyWidget.h"
#include "SkeletonLib/BSTrans.h"

class MyPainter : public MyWidget//QWidget
{
	Q_OBJECT

public:
    MyPainter(QWidget *parent, QImage);
    MyPainter(QWidget *parent);
	~MyPainter();
//    QImage getImage();


    BitRaster* srcimg;
//	TPolFigure *skeleton;
	bool ready;
	bool drawBones;
	bool drawCircles;
	bool drawContours;
	bool drawImage;

private:
//	QString filepath;
	QImage image;

protected:
    //void keyPressEvent(QKeyEvent*);
	void paintEvent(QPaintEvent *e);

public slots:
    void imageChanged(QImage filepath_);
    void savePolygons();
	
};
