#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "TransformMedialBased.h"
#include "SkeletonDemoGUI/MyPainter_.h"
#include "PaintFig.h"
#include "SelectPivots.h"
#include "MyWidget.h"
#include "MoveSkeletW.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
//    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
public:
    MainWindow(QWidget *parent = 0); //explicit
//    explicit MainWindow(QWidget *parent = 0, const char *name = 0);
    ~MainWindow();
private slots:
    void SkeletButtonClicked();
    void PivotsButtonClicked();
    void OkButtonClicked();
    void saveImageButtonClicked();
    void openImageButtonClicked();
    void errorMessage();
    void MovingButtonClicked();
    //void savePolygons();

//protected:
//    void keyPressEvent(QKeyEvent*);
//    void mousePressEvent(QMouseEvent*);
//    void mouseDoubleClickEvent(QMouseEvent*);
//    void mouseMoveEvent(QMouseEvent*);
//    void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow *ui;
    //QWidget* curWidget;
    MyWidget* curWidget;
    QImage mainImage;
//    int xPr, yPr;
//    bool pressed;
//    bool newPol;
//    vector<Polygon> polygons;
//    QPixmap   pixmap;

//    void paintTrace(const QPoint&, int);
//    void setVertex(const QPoint&, bool);
//    void Run();
//    void paint(QPainter*, const QPoint&);

};

#endif // MAINWINDOW_H
