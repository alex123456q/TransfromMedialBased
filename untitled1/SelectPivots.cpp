#include "SelectPivots.h"
#include "SkeletProcess.h"

#include <QMouseEvent>
#include <QCursor>

SelectPivots::SelectPivots(QWidget *parent, QImage im)
    : MyWidget(parent)
{
    setMinimumSize(500, 300);
    resize(500, 300);
    setCursor(Qt::CrossCursor);
    setVisible(false);
    image = im;
    //skeleton = sk;
}

SelectPivots::~SelectPivots()
{
}

void SelectPivots::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton){
    setVertex(event->pos(), true);
    this->update();
  }
  else if (event->button() == Qt::RightButton){
    setVertex(event->pos(), false);
    this->update();
  }
}

Point get_perpendicular_pt_from_pt_to_line(
       Point& pta,
       Point& ptb,
       Point& pt_from){
    Point pt_to;
    double b1 = pt_from.X * (pta.X - ptb.X) + pt_from.Y * (pta.Y - ptb.Y);
    double b2 = pta.X * ptb.Y - pta.Y * ptb.X;
    pt_to.Y = (pta.X - ptb.X) * (pta.X - ptb.X) + (pta.Y - ptb.Y) * (pta.Y - ptb.Y);
    double det_k = b1 * (pta.X - ptb.X) - b2 * (pta.Y - ptb.Y);

    pt_to.X = det_k/pt_to.Y;
    det_k = (pta.X - ptb.X) * b2 + (pta.Y - ptb.Y) * b1;
    pt_to.Y = det_k/pt_to.Y;
    return pt_to;
}



void SelectPivots::setVertex(const QPoint &pos, bool cond){
//    pivots.push_back(pos);
    QPoint curpos;
    QRgb white = qRgb(255, 255, 255);
    if (cond){
//        std::cout<<("paste vertex");
//        for (int x = 0; x < 20; ++x){
//            curpos.setX(pos.x() + x);
//            for (int y = 0; y < 20; ++y){
//                curpos.setY(pos.y() + y);
//                if (image.pixel(curpos) != white)
//                    break;
//                curpos.setY(pos.y() - y);
//                if (image.pixel(curpos) != white)
//                    break;
//            }
//            curpos.setX(pos.x() - x);
//            for (int y = 0; y < 20; ++y){
//                curpos.setY(pos.y() + y);
//                if (image.pixel(curpos) != white)
//                    break;
//                curpos.setY(pos.y() - y);
//                if (image.pixel(curpos) != white)
//                    break;
//            }
//            if (image.pixel(curpos) != white)
//                break;
//        }
        TConnected* Com = skeleton->Components->first();
        TBone *minBone = NULL;
        double min = 10000000000;
        double tmp0;
        while (Com != NULL) {
            TBone* Bone = Com->Bones->first();
                 while (Bone != NULL) {
                     tmp0= DistEdge(
                            &Point(Bone->org->Disc->X,
                            Bone->org->Disc->Y),
                            &Point(Bone->dest->Disc->X,
                            Bone->dest->Disc->Y),
                            &Point(pos.x(), pos.y()));
                     if (min > tmp0){
                         min = tmp0;
                         minBone = Bone;
                 }

                        Bone = Bone->getNext();
                    }
            Com = Com->getNext();
        }
        Point tmp  = (get_perpendicular_pt_from_pt_to_line(
                            Point(minBone->org->Disc->X,
                            minBone->org->Disc->Y),
                            Point(minBone->dest->Disc->X,
                            minBone->dest->Disc->Y),
                            Point(pos.x(), pos.y()))
                            );
        curpos = QPoint(tmp.X, tmp.Y);
        //pivots.push_back(curpos);
        SkeletProcess p(skeleton);
        //pivNodes.push_back(p.setPivot(curpos.x(), curpos.y(), minBone));
        TNode *verti = p.setPivot(curpos.x(), curpos.y(), minBone);
        if (verti){
            pivNodes.push_back(verti);
            pivots.push_back(curpos);
        }
    } else {
        if (!pivots.empty()){
            pivots.pop_back();
        }
    }
}

std::vector<TNode*> SelectPivots::getPivots(){
    return pivNodes;
}

void SelectPivots::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
//    QImage mainImage(500, 300, 32);
//    mainImage.fill(qRgb(255, 255, 255));
//    painter.drawImage(0, 0, mainImage);

    painter.drawImage(0, 0, image);
    painter.setPen(QPen(Qt::black, 8, Qt::SolidLine, Qt::RoundCap,
                        Qt::MiterJoin));
    for (int i = 0; i < pivots.size(); ++i){
        painter.drawPoint(pivots[i].x(), pivots[i].y());
    }
}
