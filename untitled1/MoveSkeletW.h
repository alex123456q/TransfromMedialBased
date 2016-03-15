#ifndef MOVESKELETW_H
#define MOVESKELETW_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include "MyWidget.h"
#include <vector>

class MoveSkeletW : public MyWidget
{
    Q_OBJECT
public:
    MoveSkeletW(QWidget *parent = 0);
    MoveSkeletW(QWidget *, QImage);
    ~MoveSkeletW();
protected:
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    TPolFigure *skeleton;
    QPainterPath path;
    QImage image;
    bool point;
    int xPr, yPr;
    TNode* curNode;
    TNode* endPoint;//TNode*
    TNode* endPointst;
    TPoint* start;
    TPoint* finish;
    TPoint* tmpCorn;
    std::vector<Point> circPoint;
    std::vector<TNode* > curRot;
    std::vector<TNode *> vertices;
    void selectPivot(int , int );

    void renewSkelet();
    void Circles(double x, double y);
    void dfs(TNode* curNode);
    void changeSkelet(TNode* curNode, double x, double y);
};


#endif // MOVESKELETW_H
