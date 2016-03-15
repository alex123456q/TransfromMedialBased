#include "MyPainter_.h"
//#include <QKeyEvent>

MyPainter::MyPainter(QWidget *parent)
    : MyWidget(parent)
{
}
MyPainter::MyPainter(QWidget *parent, QImage filepath)
    : MyWidget(parent)
{
    setMinimumSize(500, 300);
    resize(500, 300);
    setVisible(false);
    image = filepath;

    ready = true;//false;

	drawBones = true;
	drawCircles = false;
	drawContours = true;
    drawImage = false;//true;
    srcimg = NULL;

}

MyPainter::~MyPainter()
{
    //delete skeleton;
    //delete srcimg;
}

void MyPainter::paintEvent(QPaintEvent *)
{
    if (ready) {
        if (skeleton != NULL) {
            delete skeleton;
        }
        if (srcimg) {
            delete srcimg;
        }

        srcimg = new BitRaster(image.width(), image.height());

        bool inverted = false;//ui.invertCheckBox->checkState() == Qt::Checked;

        for (int i = 0; i < image.height(); i++) {
            for(int j = 0; j < image.width(); j++) {
                bool isBlack = qGreen(image.pixel(j, i)) < 128;
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

        BondSkeletTrans(srcimg, 1, 100, skeleton);//ui.pruning->value(), ui.area->value(), skeleton);

        QPainter painter(this);

        painter.fillRect(0, 0, image.width(), image.height(), Qt::white);
		
        painter.setRenderHint(QPainter::Antialiasing);

        if (drawImage) {
            painter.drawImage(0, 0, image);
        }

        if (skeleton == NULL) {
            return;
        }

        // рисуем овбодку
        if (drawContours) {
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
        }
		
        // рисуем скелеты
        TConnected* Com = skeleton->Components->first();
	
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
    }
}

void MyPainter::imageChanged(QImage filepath)
{
    image = filepath;
}

//QImage MyPainter::getImage(){
//    QImage img(this->size(), QImage::Format_ARGB32);
//    QPainter painter(&img);
//    this->render(&painter);
//    return img;
//}


//void MyPainter::keyPressEvent (QKeyEvent * event){
//    if (event->isAutoRepeat())
//        return;
//    if (event->key() == Qt::Key_Space){//Key_Enter)
//        std::cout<<"end";
//    }
//}

#include <QFileDialog>


void MyPainter::savePolygons()
{
    if (skeleton != NULL) {
        QFileDialog* fileDialog = new QFileDialog(this);

        fileDialog->setFileMode(QFileDialog::AnyFile);
        fileDialog->setNameFilter("Polygons (*.txt)");
        fileDialog->setAcceptMode(QFileDialog::AcceptSave);
        fileDialog->setDirectory("..\\SavedData\\");

        QStringList fileNames;

        if (fileDialog->exec()) {
            fileNames = fileDialog->selectedFiles();
        }

        if (fileNames.size() != 0) {
            QString filen = fileNames.at(0);

            if (!filen.endsWith(".txt")) {
                filen += ".txt";
            }

            // print polygons in file
            vector<string> edgesList;

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
                    stringstream ss;
                    ss << points[j]->X << " " << points[j]->Y << " " << points[j + 1]->X << " " << points[j + 1]->Y;
                    edgesList.push_back(ss.str());
                }
                stringstream ss;
                ss << points[cornersCount - 1]->X << " " << points[cornersCount - 1]->Y << " " << points[0]->X << " " << points[0]->Y;
                edgesList.push_back(ss.str());

                delete points;
                S = S->getNext();
            }

            ofstream f(filen.toStdString().c_str());
            f << "0" << endl;
            f << edgesList.size() << endl;
            for (ulong i = 0; i < edgesList.size(); ++i) {
                f << edgesList[i] << endl;
            }
            f.close();
        }
    }
}



