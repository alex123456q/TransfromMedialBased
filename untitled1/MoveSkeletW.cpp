#include "MoveSkeletW.h"
#include "SkeletProcess.h"
#include <QMouseEvent>
#include <QCursor>
#include "SelectPivots.h"
#include<cmath>
#include "SkeletonDemoGUI/SkeletonLib/BSTrans.h"
/*
 * Initialization
 */
MoveSkeletW::MoveSkeletW(QWidget *parent, QImage im, TPolFigure *sk, std::vector<TNode *> vert)
    : MyWidget(parent)
{
    MoveSkeletW::setMouseTracking(false);
    setMinimumSize(500, 300);
    resize(500, 300);
    setCursor(Qt::PointingHandCursor);
    setVisible(false);
    point = true;
    image = im;
    skeleton = sk;
    vertices = vert;
    endPoint = NULL;
    xPr = 0;
    yPr = 0;
}

MoveSkeletW::~MoveSkeletW()
{
}


/*
 * Matrix for rotating
 */
//std::vector<std::vector<double>>
double** createMatr(double oldX, double oldY, double newX, double newY, double rotX, double rotY){
    //std::vector<std::vector<double>> rotMatr;
//    rotMatr.resize(3);
//    for (int i=0; i < 3; +i){
//        rotMatr[i].resize(3);
//    }
    double** rotMatr;
    rotMatr = new double*[3];
    for (int i = 0; i < 3; ++i){
        rotMatr[i] = new double[3];
    }
    double hip2 = (pow(newY-oldY, 2)+ pow(newX-oldX, 2));
    //double angle = (double)atan2((-newY+oldY),(-newX+oldX))*(double)(180.0/(std::atan(1.0)*4.0));
    double a2 = pow(oldX-rotX, 2)+pow(oldY-rotY, 2);
    double b2 = pow(newX-rotX, 2)+pow(newY-rotY, 2);
    double angle = acos((a2+b2-hip2)/(2*(sqrt(a2)*sqrt(b2))));
    if ((oldX-rotX)*(-rotY+newY)-(oldY-rotY)*(-rotX+newX) < 0)
        angle *= -1;
    //double angle = acos(((oldX-rotX)*(newX-rotX) + (oldY-rotY)*(newY-rotY))/(a2*b2));
    //std::cout << angle << " " <<acos((a2+b2-hip2)/(2*(sqrt(a2)*sqrt(b2))))<<std::endl;//<< atan2((-newY+oldY),(-newX+oldX))<< " " << 180.0/(std::atan(1.0)*4.0)<<std::endl;
    rotMatr[0][0] = cos(angle);//(newY-oldY)/hip; //cos(angle);//
    rotMatr[0][2] = 0;
    rotMatr[0][1] = sin(angle);//(newX - oldX)/hip; //sin(angle);//
    rotMatr[1][0] = -rotMatr[0][1];
    rotMatr[1][1] = rotMatr[0][0];
    rotMatr[1][2] = 0;
    rotMatr[2][2] = 1;
    rotMatr[2][0] = -rotX*(rotMatr[0][0]-1)+rotY*rotMatr[0][1];
    rotMatr[2][1] = -rotY*(rotMatr[0][0]-1)-rotX*rotMatr[0][1];

    return rotMatr;
}


/*
 * Multplication vector and matrix
 */
double* mult(double* vect, double** matr){
    double* res = new double[3];
    for (int i = 0; i < 3; ++i){
        res[i] = 0;
        for (int j = 0; j < 3; ++j)
            res[i] += vect[j]*matr[j][i];
    }
    return res;
}

/*
 * Creating vector for rotating and founding new vector
 */
void rotBone(double** rotMatr, TNode* curNode){
//    std::cout << (curNode->Depth);
    double* vect = new double[3];
    vect[0] = curNode->Disc->X;
    vect[1] = curNode->Disc->Y;
    vect[2] = 1;
    vect = mult(vect, rotMatr);
    curNode->Disc->X = vect[0];
    curNode->Disc->Y = vect[1];
}
void rotEdge(double** rotMatr, TPoint* curPoint){
//    std::cout << (curNode->Depth);
    double* vect = new double[3];
    vect[0] = curPoint->X;
    vect[1] = curPoint->Y;
    vect[2] = 1;
    vect = mult(vect, rotMatr);
    curPoint->X = vect[0];
    curPoint->Y = vect[1];
}

/*
TContour* S = skeleton->Boundary->first();

while (S != NULL) {
    int cornersCount = S->ListPoints->cardinal();
    TPoint** points = new TPoint*[cornersCount];
    int i = 0;
    TPoint* Corn = S->ListPoints->first();
    while (Corn != NULL)
    {
        points[i++] = Corn;
        Corn = Corn->getNext();
    }
    for (int j = 0; j < cornersCount - 1; j++) {
        painter.drawLine(points[j]->X, points[j]->Y, points[j + 1]->X, points[j + 1]->Y);
    }
    painter.drawLine(points[cornersCount - 1]->X, points[cornersCount - 1]->Y, points[0]->X, points[0]->Y);

    delete points;
    S = S->getNext();
}

Classify(Point *P1, Point *P2, Point *q) == between;

*/







/*
 * dfs for all bones from choosed bone
 */
void MoveSkeletW::dfs(TNode* curNode){
    if (curNode == NULL)
        return;
    for (int i = 0; i < curRot.size(); ++i)
        if (curNode == curRot[i])
            return;
    int i = 0;
    //curNode->Depth = -1;
    curRot.push_back(curNode);
    TBone* Bone;
    if (curNode->Kind() == TailNode){
        endPoint = curNode;
        endPointst = curNode->Bones[0]->dest;
        if (endPointst == endPoint)
            endPointst = curNode->Bones[0]->org;
    }
    while (i < curNode->Kind()){
        Bone = curNode->Bones[i];
        dfs(Bone->GetNextNode(curNode));
        ++i;
    }
}

/*
 * Choose the base bone for rotating and dfs
 */

/*double DistEdge(Point *r1, Point *r2, Point *rp)
{
    double result = 0.0;
    double u1 = 0.0, V1 = 0.0, u2 = 0.0, V2 = 0.0, u3 = 0.0, v3 = 0.0, r = 0.0, X = 0.0, Y = 0.0;
    u1 = (r1->X - rp->X);
    V1 = (r1->Y - rp->Y);
    u2 = (r2->X - rp->X);
    V2 = (r2->Y - rp->Y);
    X = (rp->X);
    Y = (rp->Y);
    if (Tangent(r1, r2, X, Y))
    {
        r = u1 * V2 - u2 * V1;
        r = r * r;
        u3 = u1 - u2;
        v3 = V1 - V2;
        r = r / (u3 * u3 + v3 * v3);
        r = sqrt(r);
    }
    else
        r = MAXDOUBLE;
    result = r;
    return result;
} */


void MoveSkeletW::changeSkelet(TNode* curNode, double x, double y){
    TBone* Bone = curNode->Bones[0];
    double min = 1000000;
    int mini = 0;
    double tmp0;
    for (int i = 0; i < curNode->Kind(); ++i){
        Bone = curNode->Bones[i];
        Point pt_to = get_perpendicular_pt_from_pt_to_line(
                    Point(Bone->org->Disc->X,
                    Bone->org->Disc->Y),
                    Point(Bone->dest->Disc->X,
                    Bone->dest->Disc->Y),
                    Point(x, y));

        //if codirect
        tmp0 = pow(pt_to.X - x, 2) + pow(pt_to.Y - y, 2);
                /*DistEdge(
                        &Point(Bone->org->Disc->X,
                        Bone->org->Disc->Y),
                        &Point(Bone->dest->Disc->X,
                        Bone->dest->Disc->Y),
                        &Point(x, y));*/
        std::cout<<tmp0<<" ";
        if (min > tmp0){
            min = tmp0;
            mini = i;
        }
    }
    std::cout << "min distance " << min << " for i=" << mini <<std::endl;
    curRot.push_back(curNode);
    dfs(curNode->Bones[mini]->GetNextNode(curNode));
}

/*

  fi:=fi+dfi;
xc:=xc1+round(50*cos(fi*pi/180));
yc:=yc1-round(50*sin(fi*pi/180));
 x:=round(125*cos(a/57)+200);
 y:=round(125*sin(a/57)+150);
 */


void MoveSkeletW::Circles(){
    std::vector<TSite*> a;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (curRot[0]->Sites[i] == curRot[1]->Sites[j])
                a.push_back(curRot[0]->Sites[i]);

    //TSite* i1 = a[0];

    //i1->Cont->CreateElements(i1->NEl);
    //i1->Cont->ListElements->first();
    //while (i1->Cont->ListPoints->first());

    for (int j=0; j < a.size(); ++j){
        TSite* i = a[j];

        //Element* i = k->Cont->Elements[i->NEl];
        if (i->IsVertex()){
            Vertex* n = (Vertex*)i;
            circPoint.push_back(Point(n->p->X, n->p->Y));
        }
        else {
            Edge* edge = (Edge*) i;
            Point newPoint = (get_perpendicular_pt_from_pt_to_line(
                                Point(edge->org->X,
                                edge->org->Y),
                                Point(edge->dest->X,
                                edge->dest->Y),
                                Point(curNode->Disc->X, curNode->Disc->Y))
                                );

            circPoint.push_back(newPoint);
//            Vertex* newVert = new Vertex(&newPoint);


            //newVert->moveAsNextFor(n->org->X);
//            Edge* newEdge = new Edge(newVert->p, edge->dest); //LinkedListElement < TBone >
//            newEdge->org = newVert->p;
//            newEdge->dest = edge->dest;
//            edge->dest = newVert->p;
//            newEdge->moveAsNextFor(edge);
//            newVert->moveAsNextFor(newEdge);
        }
    }
    TContour* S = skeleton->Boundary->first();
    TPoint* Corn;

    while (S != NULL) {
        /*TPoint* */ Corn = S->ListPoints->first();
        while (Corn != NULL)
        {
            //find intersection of lines
            if (Codirect (new Point(endPointst->Disc->X, endPointst->Disc->Y),
                          new Point(endPoint->Disc->X, endPoint->Disc->Y), Corn) //){
            || Corn->X == endPoint->Disc->X && Corn->Y == endPoint->Disc->Y){
                std::cout << "here it is" << std::endl;
                break;
            }

            Corn = Corn->getNext();
        }
        if (S->getNext() == NULL)
            break;
        S = S->getNext();
    }
    start = Corn;
    finish = Corn;
    tmpCorn = Corn;

    //Codirect()
     while (Classify(finish->getNextLooped(), finish, &circPoint[0]) != Between
           && Classify(finish->getNextLooped(), finish, &circPoint[0]) != Origin
           && Classify(finish->getNextLooped(), finish, &circPoint[1]) != Between
           && Classify(finish->getNextLooped(), finish, &circPoint[1]) != Origin){
        finish = finish->getNextLooped();
        //if (finish == Corn)
        //    break;
        //std::cout << Classify(finish, finish->getNextLooped(), &circPoint[0]);
    }
    while (Classify(start, start->getPrevLooped(), &circPoint[0]) != Between
           && Classify(start, start->getPrevLooped(), &circPoint[0]) != Origin
           && Classify(start, start->getPrevLooped(), &circPoint[1]) != Between
           && Classify(start, start->getPrevLooped(), &circPoint[1]) != Origin){
        start = start->getPrevLooped();
    }
    if (Classify(start, start->getPrevLooped(), &circPoint[0]) == Between ||
        Classify(start, start->getPrevLooped(), &circPoint[0]) == Origin){
       (new Point(circPoint[0]))->moveAsPrevFor(start);
       start = start->getPrev();
 //   (new Point(curNode->Disc->X, curNode->Disc->Y))->moveAsPrevFor(start);
       (new Point(circPoint[0]))->moveAsPrevFor(start);
       (new Point(circPoint[1]))->moveAsNextFor(finish);
       finish = finish->getNext();
  //  (new Point(curNode->Disc->X, curNode->Disc->Y))->moveAsNextFor(finish);
       (new Point(circPoint[1]))->moveAsNextFor(finish);
   } else {
       TPoint* newPoint = new Point(circPoint[1]);
       newPoint->moveAsPrevFor(start);
  //(new Point(curNode->Disc->X, curNode->Disc->Y))->moveAsPrevFor(newPoint);
       (new Point(circPoint[1]))->moveAsPrevFor(newPoint);
       start = newPoint;
       newPoint = new Point(circPoint[0]);
       newPoint->moveAsNextFor(finish);
 // (new Point(curNode->Disc->X, curNode->Disc->Y))->moveAsNextFor(newPoint);
       (new Point(circPoint[0]))->moveAsNextFor(newPoint);
       finish = newPoint;
   }
}

void MoveSkeletW::mouseMoveEvent(QMouseEvent *event){
    setCursor(Qt::ClosedHandCursor);
    point = false;

    double** rotMatr = createMatr(xPr, yPr,
               event->pos().x(), event->pos().y(),
               curNode->Disc->X, curNode->Disc->Y);
    xPr = event->pos().x();
    yPr = event->pos().y();


    if (curRot.empty()){
        changeSkelet(curNode, event->pos().x(), event->pos().y());
        Circles();
    }

    double angle = asin(rotMatr[0][1]);

    for (int i = 0; i < circPoint.size(); ++i){
        double angle0 = atan2((circPoint[i].Y-curNode->Disc->Y),(circPoint[i].X-curNode->Disc->X));
        circPoint[i].X = curNode->Disc->X + (curNode->Disc->Rad*cos(angle+angle0));
        circPoint[i].Y = curNode->Disc->Y + (curNode->Disc->Rad*sin(angle+angle0));
    }
    for (std::vector<TNode*>::iterator it = curRot.begin() ; it != curRot.end(); ++it)
         rotBone(rotMatr, *it);
//    std::cout << event->pos().x(),event->pos().y();

    TPoint* curPoint = start;
    while (curPoint != finish->getNextLooped()){
        rotEdge(rotMatr, curPoint);
        curPoint = curPoint->getNextLooped();
    }

    this->update();
}
void MoveSkeletW::mouseReleaseEvent(QMouseEvent *event){
    if (!point){
        setCursor(Qt::OpenHandCursor);
    } else {
        curRot.clear();
        circPoint.clear();
        setCursor(Qt::PointingHandCursor);
    }
}


void MoveSkeletW::selectPivot(int x, int y){
    int mini = 0;
    int min = 1000000;

//    std::cout<<"SELECTING of: "<<vertices.size();
    for (int i = 0; i < vertices.size(); ++i){
//        std::cout<<vertices[i]->Disc->X <<"-"<<vertices[i]->Disc->Y<<"="<<x<<"-"<<y<<";";
        if (min > (pow(vertices[i]->Disc->X - x, 2) + pow(vertices[i]->Disc->Y - y, 2))){
            mini = i;
            min = (pow(vertices[i]->Disc->X - x, 2) + pow(vertices[i]->Disc->Y - y, 2));
        }
    }
//    std::cout<<"RESULT "<<mini<<std::endl;
    curNode = vertices[mini];
}

void MoveSkeletW::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton){
    if (point){
        selectPivot(event->pos().x(), event->pos().y());
    }
    point = false;
    xPr = event->pos().x();
    yPr = event->pos().y();
    setCursor(Qt::OpenHandCursor);//(Qt::DragMoveCursor);
//    this->update();
  }
  else if (event->button() == Qt::RightButton){
    point = true;
    setCursor(Qt::PointingHandCursor);//(Qt::DragMoveCursor);

    //delete skeleton;

    QImage image = getImage();
    BitRaster* srcimg = new BitRaster(image.width(), image.height());
    bool inverted = false;//ui.invertCheckBox->checkState() == Qt::Checked;
    for (int i = 0; i < image.height(); i++) {
        for(int j = 0; j < image.width(); j++) {
            bool isBlack = (qBlue(image.pixel(j, i)) < 128
                            || qRed(image.pixel(j, i)) < 128
                            || qGreen(image.pixel(j, i)) < 128);
            if (!inverted) {
                if (isBlack) {
                    srcimg->setBit(j, i, isBlack);
                }
            }
            else {
                if (!isBlack) {
                    srcimg->setBit(j, i, !isBlack);
                }
            }
        }
    }

    BondSkeletTrans(srcimg, 1, 100, skeleton);
    vertices.clear();
    //skeleton = MyPainter(this, getImage()).skeleton;
//    this->update();
  }
}



void MoveSkeletW::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

//    QImage mainImage(500, 300, 32);
//    mainImage.fill(qRgb(255, 255, 255));
//    painter.drawImage(0, 0, mainImage);
    path = QPainterPath();
    path.setFillRule(Qt::WindingFill);
    painter.fillRect(0, 0, image.width(), image.height(), Qt::white);

    painter.setRenderHint(QPainter::Antialiasing);

    if (skeleton == NULL) {
        return;
    }
    QPolygonF contour;
        painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

        TContour* S = skeleton->Boundary->first();

        while (S != NULL) {
            int cornersCount = S->ListPoints->cardinal();
            TPoint** points = new TPoint*[cornersCount];
            int i = 0;
            TPoint* Corn = S->ListPoints->first();
            while (Corn != NULL)
            {
                points[i++] = Corn;
                Corn = Corn->getNext();
            }
            for (int j = 0; j < cornersCount - 1; j++) {
                contour << QPointF(points[j]->X, points[j]->Y) << QPointF(points[j + 1]->X, points[j + 1]->Y);
         //c       painter.drawLine(points[j]->X, points[j]->Y, points[j + 1]->X, points[j + 1]->Y);
       //         painter.setPen(QPen(Qt::blue, 4.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
      //          painter.drawPoint(points[j]->X, points[j]->Y); ///
         //c       painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

            }
            contour << QPointF(points[cornersCount - 1]->X, points[cornersCount - 1]->Y) << QPointF(points[0]->X, points[0]->Y);

        //c    painter.drawLine(points[cornersCount - 1]->X, points[cornersCount - 1]->Y, points[0]->X, points[0]->Y);

            delete points;
            S = S->getNext();
        }
    path.addPolygon(contour);
  //c
    painter.setPen(QPen(Qt::cyan, 8, Qt::SolidLine, Qt::RoundCap,
                        Qt::MiterJoin));
    if (endPoint){
        painter.drawPoint(endPoint->Disc->X, endPoint->Disc->Y);
        painter.setPen(QPen(Qt::red, 8, Qt::SolidLine, Qt::RoundCap,
                            Qt::MiterJoin));
        painter.drawPoint(endPointst->Disc->X, endPointst->Disc->Y);
        painter.setPen(QPen(Qt::magenta, 10, Qt::SolidLine, Qt::RoundCap,
                            Qt::MiterJoin));
        painter.drawPoint(tmpCorn->X, tmpCorn->Y);
    }
    painter.setPen(QPen(Qt::green, 1, Qt::DotLine, Qt::RoundCap,
                        Qt::MiterJoin));
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern)); //Qt::TransparentMode Qt::SolidPattern Qt::NoBrush  Dense1Pattern
    if (!curRot.empty()){
 //c
        path.addEllipse(QPointF(curRot[0]->Disc->X,
                                curRot[0]->Disc->Y),
                                curRot[0]->Disc->Rad, curRot[0]->Disc->Rad);
 //       painter.drawEllipse(QPointF(curRot[0]->Disc->X,
 //                           curRot[0]->Disc->Y),
 //               curRot[0]->Disc->Rad, curRot[0]->Disc->Rad);
        /*painter.drawEllipse(QPointF(curRot[1]->Disc->X,
                            curRot[1]->Disc->Y),
                curRot[1]->Disc->Rad, curRot[1]->Disc->Rad);*/
   }
   painter.drawPath(path);


   // рисуем скелеты
   TConnected* Com = skeleton->Components->first();
   bool drawBones = 1;
   bool drawCircles = 0;
   while (Com != NULL) {
       painter.setPen(QPen(Qt::red, 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

       if (drawBones) {
           TBone* Bone = Com->Bones->first();
           while (Bone != NULL) {
               painter.drawLine(
                   Bone->org->Disc->X,
                   Bone->org->Disc->Y,
                   Bone->dest->Disc->X,
                   Bone->dest->Disc->Y
               );

               Bone = Bone->getNext();
           }
       }

       painter.setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

       if (drawCircles) {
           TNode* Node = Com->Nodes->first();

           while (Node != NULL) {
               painter.drawEllipse(Node->X() + 1 - Node->r(),
                   Node->Y() + 1 - Node->r(),
                   2 * Node->r(),
                   2 * Node->r());

               Node = Node->getNext();
           }
       }

       Com = Com->getNext();
   }
   painter.setPen(QPen(Qt::red, 8, Qt::SolidLine, Qt::RoundCap,
                       Qt::MiterJoin));
   for (int i = 0; i < vertices.size(); ++i){
       painter.drawPoint(vertices[i]->Disc->X, vertices[i]->Disc->Y);
       //painter.drawLine(vertices[i]->Disc->X, vertices[i]->Disc->Y, );
   }
   painter.setPen(QPen(Qt::black, 8, Qt::SolidLine, Qt::RoundCap,
                       Qt::MiterJoin));
   for (int i = 0; i < circPoint.size(); ++i){
       painter.drawPoint(circPoint[i].X, circPoint[i].Y);
       //painter.drawLine(circPoint[i].X, circPoint[i].Y
   }
   //painter.end();

}

