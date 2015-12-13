#include "skeletondemogui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SkeletonDemoGUI w;
	w.show();
	return a.exec();
}
