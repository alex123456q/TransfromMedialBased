
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <stdio.h>
#include <iostream>

#include "Running.h"

#include "PaintFig.h"
//#include "ui_PaintFig.h"


void PaintFig::setImage(QImage* im){
    mainImage = im;
}

PaintFig::PaintFig(QWidget *parent)
    : MyWidget(parent)
{
//  setMinimumSize(500, 300);
  resize(500, 300);
    //setSizePolicy(300, 300);//QSizePolicy::Minimum, QSizePolicy::Minimum);
  newPol = true;
  PaintFig::setMouseTracking(true);
  mainImage = new QImage(500, 300, 32);
  mainImage->fill(qRgb(255, 255, 255));
  //QPixmap pixmap(300,500);
  //pixmap.fill(QColor("transparent"));
  setVisible(false);
}
//PaintFig::PaintFig(QWidget *parent) :
//    QPaintFig(parent),
//    ui(new Ui::PaintFig)
//{
//    ui->setupUi(this);

//    newPol = true;
//    PaintFig::setMouseTracking(true);
//    mainImage.create(300, 300, 32);//QImage::Format_RGB444);
//    mainImage.fill(qRgb(255, 255, 255));
//}

PaintFig::~PaintFig()
{
    delete mainImage;
    polygons.clear();
    //delete ui;
}

//void PaintFig::createActions()
//{
//    newAct = new QAction(tr("&Open"), tr("Ctrl+N"), this);
//    newAct->setIconSet(QPixmap::fromMimeSource("new.png"));
//    newAct->setStatusTip(tr("Open file"));
//    connect(newAct, SIGNAL(activated()), this, SLOT(openFile()));

//    showGridAct = new QAction(tr("&Show Grid"), 0, this);
//    showGridAct->setToggleAction(true);
//    showGridAct->setOn(spreadsheet->showGrid());
//    showGridAct->setStatusTip(tr("Show or hide the spreadsheet s " "grid"));
//    connect(showGridAct, SIGNAL(toggled(bool)), spreadsheet, SLOT(setShowGrid(bool)));
//}

void PaintFig::mousePressEvent(QMouseEvent *event)
{
  pressed = false;
  if (event->button() == Qt::LeftButton){
    setVertex(event->pos(), true);
//    paintTrace(event->pos(), 3);
    this->update();
  }
  else if (event->button() == Qt::RightButton){
    setVertex(event->pos(), false);
//    paintTrace(event->pos(), 2);
    this->update();
  }
}

void PaintFig :: mouseDoubleClickEvent(QMouseEvent *)
{
    pressed = true;
    newPol = true;
}

void PaintFig::mouseMoveEvent(QMouseEvent *event)
{
    if (!newPol)
        xPr = event->pos().x();
        yPr = event->pos().y();
//        paintTrace(event->pos(), 3);
        this->update();
//  if (event->state() & LeftButton)
//    setImagePixel(event->pos(), true);
//  else if (event->state() & RightButton)
//    setImagePixel(event->pos(), false);
}

//void PaintFig::keyPressEvent (QKeyEvent * event){
//    if (event->isAutoRepeat())
//        return;
//    if (event->key() == Qt::Key_Escape)
//        QApplication::quit();
//    if (event->key() == Qt::Key_Space)//Key_Enter)
//        Run();
//}

void PaintFig::paintTrace(const QPoint &pos, int cond){
    int i = pos.x(); // zoom;
    int j = pos.y();// zoom;
//    QPainter painter(this);
    QPainter painter(&pixmap);
//    painter.setBrush(QBrush(Qt::black));
//        painter.drawRect(10, 10, 100, 100);


//    paint(&painter, pos);
    if (1){//mainImage.rect().contains(i, j)){
        QPoint pPr = polygons.back().getLastPoint();
        if (cond == 3){
            painter.setPen(QPen(Qt::white, 3, Qt::DotLine));
            painter.drawLine(pPr.x(), pPr.y(), xPr, yPr);
            painter.setPen(QPen(Qt::black, 3, Qt::DotLine));
        }
        if (cond == 2){
            painter.setPen(QPen(Qt::black, 3, Qt::SolidLine));
        }
        painter.drawLine(pPr.x(), pPr.y(), i, j);


//        label.setPixmap(pixmap);

        xPr = i; yPr = j;
    }
}


void PaintFig::setVertex(const QPoint &pos, bool cond){
    if (cond){
        if (newPol){
            polygons.push_back(Polygon(pos));
        } else {
            polygons.back().addPoint(pos);
        }
        newPol = false;
    } else {
        if (!polygons.empty()){
            polygons.back().delPoint();
            if (polygons.back().isEmpty()){
                polygons.pop_back();
                newPol = true;}
        }
    }
}

void PaintFig::paint(QPainter *painter, const QPoint &pos){
    if (polygons.empty())
        return;
    QPoint pPr = polygons.back().getLastPoint();
    painter->setPen(QPen(Qt::black, 3, Qt::DotLine));
    painter->drawLine(pPr.x(), pPr.y(), pos.x(), pos.y());
}

void PaintFig::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

//    int side = QMIN(width(), height());
//    painter.setViewport((width() - side) / 2, (height() - side) / 2,
//                        side, side);
    painter.drawImage(0, 0, *mainImage);
    painter.setBackground(QBrush(Qt::CrossPattern));
//    cout << "beginning" << endl;
    QPoint cur, pred;
    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine));

//    if (!polygons.empty()){
//        QPoint pPr = polygons.back().getLastPoint();
//        painter.setPen(QPen(Qt::black, 3, Qt::DotLine));
//        painter.drawLine(pPr.x(), pPr.y(), xPr, yPr);
//    }
    if (polygons.empty())
        return;
    if (polygons.back().size() == 1){
        painter.drawPoint(polygons.back().getLastPoint().x(), polygons.back().getLastPoint().y());
    }

//    for (int i = 0; i < polygons.size(); ++i) {
//        pred = polygons[i].getPoint(0);
//        for (int j = 1; j < polygons[i].size(); ++j){
//            cur = polygons[i].getPoint(j);
//            painter.drawLine(pred.x(), pred.y(), cur.x(), cur.y());
//            pred = cur;
//        }
//        cur = polygons[i].getPoint(0);
//        if (i == polygons.size()-1 && !pressed){
//            painter.setPen(QPen(Qt::black, 1, Qt::DotLine));
//        }
//        painter.drawLine(pred.x(), pred.y(), cur.x(), cur.y());
//    }
    QPoint* points;
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    QPolygonF pol;
    for (int i = 0; i < polygons.size()-1; ++i) {
        points = new QPoint[polygons[i].size()];
        for (int j = 0; j < polygons[i].size(); ++j){
           points[j] = polygons[i].getPoint(j);
           pol << polygons[i].getPoint(j);
        }
//        painter.drawPolygon(points, polygons[i].size(), Qt::OddEvenFill);//Qt::WindingFill
        path.addPolygon(pol);
//        painter.drawPath(path);
        pol.clear();
        delete points;
    }
    if (!pressed){
        painter.setBrush(Qt::green);
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        painter.drawPath(path);

        pred = polygons.back().getPoint(0);
        for (int j = 1; j < polygons[polygons.size()-1].size(); ++j){
            cur = polygons.back().getPoint(j);
            painter.drawLine(pred.x(), pred.y(), cur.x(), cur.y());
            pred = cur;
        }
        cur = polygons.back().getPoint(0);
        painter.setPen(QPen(Qt::black, 1, Qt::DotLine));
        painter.drawLine(pred.x(), pred.y(), cur.x(), cur.y());
    } else {
        int tmpsize =  polygons.back().size();
        points = new QPoint[tmpsize];
        for (int j = 0; j < tmpsize; ++j){
           points[j] = polygons.back().getPoint(j);
           pol <<polygons.back().getPoint(j);
        }
        path.addPolygon(pol);
        delete points;
        painter.setBrush(Qt::green);
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        painter.drawPath(path);

        // Fill polygon

        // Draw polygon
//        painter.drawPolygon(poly);
//        painter.drawPolygon(points, tmpsize, Qt::OddEvenFill);
//        painter.fillPath(path, Qt::blue);

    }
//    QPainter p(this);
//    p.drawPixmap(0, 0,pixmap);
//    paint(&painter, QPoint(xPr, yPr));
//  if (zoom >= 3) {
//    painter.setPen(colorGroup().foreground());
//    for (int i = 0; i <= image.width(); ++i)
//      painter.drawLine(zoom * i, 0,
//                       zoom * i, zoom * image.height());
//    for (int j = 0; j <= image.height(); ++j)
//      painter.drawLine(0, zoom * j,
//                       zoom * image.width(), zoom * j);
//  }

//  for (int i = 0; i < image.width(); ++i) {
//    for (int j = 0; j < image.height(); ++j)
//      drawImagePixel(&painter, i, j);
//  }
}

void PaintFig::keyPressEvent (QKeyEvent * event){
    if (event->isAutoRepeat())
        return;
//    if (event->key() == Qt::Key_Escape)
//        QApplication::quit();
    if (event->key() == Qt::Key_Space){//Key_Enter)
//        this->setVisible(false);
        std::cout<<"end";
    }
}

//QImage PaintFig::getImage(){
////    QImage img(this->size(), QImage::Format_ARGB32);


//    QPainter painter(mainImage);//img
//    this->render(&painter);


//    //    QImage img(300, 500, QImage::Format_ARGB32);

////    QPainter painter;
////    painter.begin(&img);
////    paint(painter);
////    painter.end();

////    QImage img(mywidget.size());
////    QPainter painter(&img);
////    this->render(&painter);
//    return mainImage->copy();
//}

