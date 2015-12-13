#include "MoveSkeletW.h"
#include "SkeletProcess.h"

#include <QMouseEvent>
#include <QCursor>
#include<cmath>


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
}

MoveSkeletW::~MoveSkeletW()
{
}
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
    double hip = sqrt(pow(newY-oldY, 2)+ pow(newX-oldX, 2));
    rotMatr[0][0] = (newY-oldY)/hip;
    rotMatr[0][2] = 0;
    rotMatr[0][1] = (newX - oldX)/hip;
    rotMatr[1][0] = -rotMatr[0][1];
    rotMatr[1][1] = rotMatr[0][0];
    rotMatr[1][2] = 0;
    rotMatr[2][2] = 1;
    rotMatr[2][0] = -rotX*(rotMatr[0][0]-1)+rotY*rotMatr[0][1];
    rotMatr[2][1] = -rotY*(rotMatr[0][0]-1)-rotX*rotMatr[0][1];
    return rotMatr;
}

double* mult(double* vect, double** matr){
    double* res = new double[3];
    for (int i = 0; i < 3; ++i){
        res[i] = 0;
        for (int j = 0; j < 3; ++j)
            res[i] += vect[j]*matr[j][i];
    }
    return res;
}

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
void dfs(TNode* curNode){
    if (curNode == NULL || curNode->Depth == -1)
        return;
    int i = 0;
    curNode->Depth = -1;
    curRot.push_back(curNode);
    TBone* Bone;
    while (i <= curNode->Kind()){
        Bone = curNode->Bones[i];
        rotBone(rotMatr, Bone->GetNextNode(curNode));
        ++i;
    }
}

void changeSkelet(double** rotMatr, TNode* curNode, double x, double y){
    TBone* Bone = curNode->Bones[0];
    double cos = -5;
    TNode* nextNode;
    int i = 0;
    curNode->Depth = -1;
    while (cos <0 && i <= curNode->Kind()) {
        Bone = curNode->Bones[i];
        nextNode = Bone->GetNextNode(curNode);
        cos = ((-curNode->Disc->X+nextNode->Disc->X)*(x-curNode->Disc->X)+
               (-curNode->Disc->Y+nextNode->Disc->Y)*(y-curNode->Disc->Y));
//        std::cout<<"Here it is cos "<<cos<<std::endl;
        ++i;
    }
    dfs(nextNode);
}


void MoveSkeletW::mouseMoveEvent(QMouseEvent *event){
    setCursor(Qt::ClosedHandCursor);
    point = false;
    double** rotMatr = createMatr(curNode->Disc->X, curNode->Disc->Y,
               event->pos().x(), event->pos().y(),
               curNode->Disc->X, curNode->Disc->Y);
    if (curRot.empty())
         changeSkelet(rotMatr, curNode, event->pos().x(), event->pos().y());
    for (std::vector<TNode*>::iterator it = curRot.begin() ; it != curRot.end(); ++it)
         rotBone(rotMatr, *it);
//    std::cout << event->pos().x(),event->pos().y();
    this->update();
}
void MoveSkeletW::mouseReleaseEvent(QMouseEvent *event){
    if (!point){
        setCursor(Qt::OpenHandCursor);
    } else {
        setCursor(Qt::PointingHandCursor);
    }
}


void MoveSkeletW::selectPivot(int x, int y){
    int mini = 0;
    int min = 1000000;
    curRot.clear();
//    std::cout<<"SELECTING of: "<<vertices.size();
    for (int i = 0; i < vertices.size(); ++i){
//        std::cout<<vertices[i]->Disc->X <<"-"<<vertices[i]->Disc->Y<<"="<<x<<"-"<<y<<";";
        if (min > (pow(vertices[i]->Disc->X - x, 2) + pow(vertices[i]->Disc->Y - y, 2))){
            mini = i;
            min = (pow(vertices[i]->Disc->X - x, 2) + pow(vertices[i]->Disc->Y - y, 2));
        }
    }
    std::cout<<"RESULT "<<mini<<std::endl;
    curNode = vertices[mini];
}

void MoveSkeletW::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton){
    if (point){
        selectPivot(event->pos().x(), event->pos().y());
    }
    point = false;
    setCursor(Qt::OpenHandCursor);//(Qt::DragMoveCursor);
//    this->update();
  }
  else if (event->button() == Qt::RightButton){
    point = true;
    setCursor(Qt::PointingHandCursor);//(Qt::DragMoveCursor);
//    this->update();
  }
}



void MoveSkeletW::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

//    QImage mainImage(500, 300, 32);
//    mainImage.fill(qRgb(255, 255, 255));
//    painter.drawImage(0, 0, mainImage);

    painter.fillRect(0, 0, image.width(), image.height(), Qt::white);

    painter.setRenderHint(QPainter::Antialiasing);

    if (skeleton == NULL) {
        return;
    }

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
                painter.drawLine(points[j]->X, points[j]->Y, points[j + 1]->X, points[j + 1]->Y);
            }
            painter.drawLine(points[cornersCount - 1]->X, points[cornersCount - 1]->Y, points[0]->X, points[0]->Y);

            delete points;
            S = S->getNext();
        }

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
    painter.setPen(QPen(Qt::black, 8, Qt::SolidLine, Qt::RoundCap,
                        Qt::MiterJoin));
    for (int i = 0; i < vertices.size(); ++i){
        painter.drawPoint(vertices[i]->Disc->X, vertices[i]->Disc->Y);
    }
}

