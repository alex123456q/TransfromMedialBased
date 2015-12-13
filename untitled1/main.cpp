#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    w->show();
    return a.exec();
}
//#include <qapplication.h>
//#include <qpushbutton.h>

//int main(int argc, char **argv)
//{
//    QApplication app1(argc, argv);

//    QPushButton button1("linux.firststeps.ru!",0);
//    button1.resize(300,30);

//    app1.setMainWidget(&button1);
//    button1.show();
//    return app1.exec();
//}
