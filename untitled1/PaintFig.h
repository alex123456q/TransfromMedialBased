#ifndef PAINTFIG_H
#define PAINTFIG_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <vector>
#include "TransformMedialBased.h"
#include "MyWidget.h"


class PaintFig : public MyWidget//QPaintFig
{
    Q_OBJECT
public:
    void setImage(QImage* im);
    PaintFig(QWidget *parent = 0);
//    PaintFig(QWidget *parent, QImage);
//    QImage getImage();
    ~PaintFig();
protected:
    void keyPressEvent(QKeyEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void paintEvent(QPaintEvent *);

private:
//    Ui::PaintFig *ui;
    QImage* mainImage;
    int xPr, yPr;
    bool pressed;
    bool newPol;
    std::vector<Polygon> polygons;
    QPixmap   pixmap;

    void paintTrace(const QPoint&, int);
    void setVertex(const QPoint&, bool);
//    void Run();
    void paint(QPainter*, const QPoint&);
};

#endif // PAINTFIG_H
