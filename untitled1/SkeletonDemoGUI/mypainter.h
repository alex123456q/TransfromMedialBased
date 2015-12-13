#pragma once

#include <QWidget>
#include <QImage>
#include <QPainter>

#include "SkeletonLib/BSTrans.h"

class MyPainter : public QWidget
{
	Q_OBJECT

public:
	MyPainter(QWidget *parent);
	~MyPainter();

	TPolFigure *skeleton;
	bool ready;
	bool drawBones;
	bool drawCircles;
	bool drawContours;
	bool drawImage;

private:
	QString filepath;
	QImage image;

protected:
	void paintEvent(QPaintEvent *e);

public slots:
	void imageChanged(QString filepath_);
	
};