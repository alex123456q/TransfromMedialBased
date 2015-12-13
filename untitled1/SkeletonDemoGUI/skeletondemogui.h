#pragma once

#include <QMainWindow>
#include "ui_skeletondemogui.h"

#include <QFileDialog>
#include <string>
using std::string;

#include <fstream>
using std::ofstream;

#include "SkeletonLib/BSTrans.h"

class SkeletonDemoGUI : public QMainWindow
{
	Q_OBJECT

public:
	SkeletonDemoGUI(QWidget *parent = 0);
	~SkeletonDemoGUI();

private:
    Ui::SkeletonDemoGUIClass ui;
	QString imagepath;
	QImage image;
	TPolFigure* skeleton;
	BitRaster* srcimg;
	
private slots:
	void openImageButtonClicked();
	void checkBoxesChanged(int);
	void updateSkeleton();
	void saveImage();
    void savePolygons();

signals:
	void newImageLoaded(QString filepath_);
};
