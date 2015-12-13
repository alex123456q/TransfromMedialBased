#ifndef SELECTPIVOTS_H
#define SELECTPIVOTS_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <vector>

#include "MyWidget.h"

class SelectPivots : public MyWidget//QWidget
{
    Q_OBJECT

public:
    SelectPivots(QWidget *parent, QImage, TPolFigure *);
    ~SelectPivots();
    std::vector<TNode*> getPivots();
private:
    QImage image;
//    TPolFigure *skeleton;
    std::vector<QPoint> pivots;
    std::vector<TNode*> pivNodes;
    void setVertex(const QPoint&, bool);
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent*);

};
Point get_perpendicular_pt_from_pt_to_line(Point& pta,
                                           Point& ptb,
                                           Point& pt_from);

#endif // SELECTPIVOTS_H
