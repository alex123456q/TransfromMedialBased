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
    MoveSkeletW(QWidget *, QImage, TPolFigure *, std::vector<TNode*>);
    ~MoveSkeletW();
protected:
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    QImage image;
    bool point;
    int xPr, yPr;
    TNode* curNode;
    std::vector<Point> circPoint;
    std::vector<TNode* > curRot;
    std::vector<TNode *> vertices;
    void selectPivot(int , int );

    void Circles();
    void dfs(TNode* curNode);
    void changeSkelet(double** rotMatr, TNode* curNode, double x, double y);
};


#endif // MOVESKELETW_H
