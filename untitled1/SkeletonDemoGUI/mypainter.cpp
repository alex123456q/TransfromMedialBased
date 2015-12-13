#include "mypainter.h"

MyPainter::MyPainter(QWidget *parent)
	: QWidget(parent)
{
	ready = false;

	drawBones = true;
	drawCircles = false;
	drawContours = true;
	drawImage = true;
}

MyPainter::~MyPainter()
{

}

void MyPainter::paintEvent(QPaintEvent *)
{
	if (ready) {
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

void MyPainter::imageChanged(QString filepath_)
{
	filepath = filepath_;
	image = QImage(filepath);
}