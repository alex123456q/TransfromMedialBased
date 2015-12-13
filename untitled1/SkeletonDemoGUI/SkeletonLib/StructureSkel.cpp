#include "StructureSkel.h"

typedef unsigned int unsignedint;


int NodeCount = 0, BoneCount = 0, CompCount = 0;


unsignedint TimeInMilSecond()
/*Текущее время в миллисекундах*/
{
	return 1000 * (clock() / float(CLOCKS_PER_SEC));
}


double TNode::X()
{
	return Disc->X;	
}


double TNode::Y()
{
	return Disc->Y;
}


double TNode::r()
{
	return Disc->Rad;
}


NodeKind TNode::Kind()
{
	NodeKind result = Isolated;
	if (Bones[1 - 1] == NULL)
		result = Isolated;
	else
		if (Bones[2 - 1] == NULL)
			result = TailNode;
		else
			if (Bones[3 - 1] == NULL)
				result = JointNode;
			else
				result = ForkNode;
	return result;
}


TConnected::TConnected()
	: Nodes(new LinkedListTail<TNode>),
	Bones(new LinkedListTail<TBone>)
{
	CompCount++;
}


TNode::TNode()
	: Number(0),
	Disc(NULL),
	Depth(0.0),
	Merge(NULL)
{
	for (int i = 1; i <= 3; i++) {
		Bones[i - 1] = NULL;
		Sites[i - 1] = NULL;
	}
	NodeCount++;
}


TNode::~TNode()
{
	NodeCount--;
	if (Disc != NULL)
		delete Disc;
	// todo check:  inherited::Destroy;
}


void TNode::DetachBone(TBone* Bone) /*отцепить кость*/
{
	if (Bones[1 - 1] == Bone)
	{
		Bones[1 - 1] = Bones[2 - 1];
		Bones[2 - 1] = Bones[3 - 1];
		Bones[3 - 1] = NULL;
	}
	else
		if (Bones[2 - 1] == Bone)
		{
		Bones[2 - 1] = Bones[3 - 1];
		Bones[3 - 1] = NULL;
		}
		else
			if (Bones[3 - 1] == Bone)
				Bones[3 - 1] = NULL;
}


TBone::TBone()
	: Com(NULL),
	org(NULL),
	dest(NULL),
	Met(false),
	Virt(NULL)
{
	BoneCount++;
}


TNode* TBone::GetNextNode(TNode* Source)
/*узел, противоположный Node на этой же кости*/
{
	TNode* result = NULL;
	if (org == Source)
		result = dest;
	else
		if (dest == Source)
			result = org;
		else
			result = NULL;
	return result;
}


void TBone::DetachNode(TNode* Node)
{     /*отцепиться от узла*/
	if (Node == org)
		org = NULL;
	else
		if (Node == dest)
			dest = NULL;
}


TBone::~TBone()
{
	BoneCount--;
	if (Virt != NULL) {
		delete Virt;
		Virt = NULL;
	}
}


void TBone::DestroyWithDetach()
/*отцепиться и уничтожить кость*/
{
	if (org != NULL)
		org->DetachBone(this);
	if (dest != NULL)
		dest->DetachBone(this);
	BoneCount--;
	if (Virt != NULL) {
		delete Virt;
		Virt = NULL;
	}
	// todo check:  inherited::Destroy;
	// TODO find usage
}


bool TBone::Fiction()
/*кость вдоль фиктивного контура */
{
	bool result = false;
	bool b1 = false, b2 = false;
    b1 = false;
	b2 = false;
	for (int i = 1; i <= 3; i++)
	{
		b1 = b1 || org->Sites[i - 1]->Cont->Fiction;
		b2 = b2 || dest->Sites[i - 1]->Cont->Fiction;
	}
	result = b1 && b2;
	return result;
}


void TBone::Bisector(TSite *E1, TSite *E2)
/*Вычисление параболического бисектора*/
{
	double xv = 0.0, yv = 0.0, Z = 0.0;
	TPoint *s0 = NULL, *S1 = NULL, *S2 = NULL, *St = NULL;
	TDisc *C1 = NULL, *C2 = NULL, *ct = NULL;
	double ex = 0.0, ey = 0.0, fx = 0.0, fy = 0.0;
	double d0 = 0.0, d1 = 0.0, d2 = 0.0, t0 = 0.0, t1 = 0.0, t2 = 0.0, a = 0.0, B = 0.0, M = 0.0, XT = 0.0, yt = 0.0;
	/*#
	St1:
	St2:
	St3:
	St4:
	St5:
	St6:
	St7:
	St8:
	*/
	/*определение и правильная ориентация всех точек*/
	if (E1->IsVertex())
	{
		s0 = ((Vertex*)E1)->p;
		S1 = ((TEdge*)E2)->org;
		S2 = ((TEdge*)E2)->dest;
	}
	else
	{
		s0 = ((Vertex*)E2)->p;
		S1 = ((TEdge*)E1)->org;
		S2 = ((TEdge*)E1)->dest;
	}
	Z = (S1->X - s0->X) * (S2->Y - s0->Y) - (S2->X - s0->X) * (S1->Y - s0->Y);
	if (Z == 0)
		return;
	if (Z < 0)
	{
		St = S1;
		S1 = S2;
		S2 = St;
	}
	C1 = org->Disc;
	C2 = dest->Disc;
	Z = (S2->X - S1->X) * (C2->X - C1->X) + (S2->Y - S1->Y) * (C2->Y - C1->Y);
	if (Z < 0)
	{
		ct = C1;
		C1 = C2;
		C2 = ct;
	}
	/*вычисление контрольной точки*/
//St1:
	ex = S2->X - S1->X;
	ey = S2->Y - S1->Y;
	fx = -ey;
	fy = ex;
//St2:
	M = Sqr(ex) + Sqr(ey);
	d1 = (ex * (C1->Y - S1->Y) - ey * (C1->X - S1->X)) / M;
	d2 = (ex * (C2->Y - S1->Y) - ey * (C2->X - S1->X)) / M;
	d0 = (ex * (s0->Y - S1->Y) - ey * (s0->X - S1->X)) / M;
//St3:
	t1 = (ex * (C1->X - S1->X) + ey * (C1->Y - S1->Y)) / M;
	t2 = (ex * (C2->X - S1->X) + ey * (C2->Y - S1->Y)) / M;
	t0 = (ex * (s0->X - S1->X) + ey * (s0->Y - S1->Y)) / M;
	if (abs(t1 - t2) < 0.0001)
		return;
//St4:
	B = d0 / 2;
//St5:
	if (abs(t1 - t0) > abs(t2 - t0))
		a = (d1 - B) / Sqr(t1 - t0);
	else
		a = (d2 - B) / Sqr(t2 - t0);
//St6:
	XT = ((t2 - t0) * t2 - (t1 - t0) * t1 - (d2 - d1) / (2 * a)) / (t2 - t1);
	yt = d1 + (XT - t1) * 2 * a * (t1 - t0);
//St7:
	xv = S1->X + XT * ex + yt * fx;
	yv = S1->Y + XT * ey + yt * fy;
	Virt = new TPoint(xv, yv);
}


void TBone::BezierPoints(double& X1, double& Y1, double& X2, double& Y2)
/*Вычисление контрольных точек для параболического ребра*/
{
	if (Virt == NULL)
	{
		X1 = org->X();
		Y1 = org->Y();
		X2 = dest->X();
		Y2 = dest->Y();
	}
	else
	{
		X1 = org->X() + double(2) * (Virt->X - org->X()) / 3;
		Y1 = org->Y() + double(2) * (Virt->Y - org->Y()) / 3;
		X2 = dest->X() + double(2) * (Virt->X - dest->X()) / 3;
		Y2 = dest->Y() + double(2) * (Virt->Y - dest->Y()) / 3;
		//       x1:=Virt.X; y1:=Virt.Y;
		//       x2:=Virt.X; y2:=Virt.Y;
	}
}


TConnected::~TConnected()
/*Уничтожение компоненты*/
{
	TBone* B = NULL;
	TNode* n = NULL;
	HoleList.clear();
	while (!Bones->isEmpty())
	{
		B = (TBone*)Bones->first();
		B->removeFromCurrentList();
		delete B;
	}
	while (!Nodes->isEmpty())
	{
		n = (TNode*)Nodes->first();
		n->removeFromCurrentList();
		delete n;
	}
	delete Bones;
	delete Nodes;
	CompCount--;
	// todo check:  inherited::Destroy;
}


void TConnected::CutSkeleton(double Eps)
/*стрижка-укорачивание на Eps - точность*/
{
	LinkedListTail<TNode>* Hairs;
	TNode* Node = NULL, *Node1 = NULL, *t = NULL;
	TBone* Bone = NULL;
	double l = 0.0, D = 0.0;
	/*поиск всех терминальных узлов*/
	Hairs = new LinkedListTail < TNode > ;
	Node = (TNode*)Nodes->first();
	while (Node != NULL)
	{
		Node1 = Node->getNext();
		Node->Depth = Node->r();
		if (Node->Kind() == TailNode)
			Node->moveIntoTail(Hairs);
		Node = Node1;
	}
	/*собственно стрижка*/
	while (!Hairs->isEmpty())
	{
		t = (TNode*)Hairs->first();
		Bone = t->Bones[1 - 1];
		if (Bone != NULL)
		{
			Node = Bone->GetNextNode(t);
			l = sqrt(Sqr(t->X() - Node->X()) + Sqr(t->Y() - Node->Y()));
			if ((l + t->Depth - Node->r() < Eps) && (Node->Kind() != TailNode))
			{
				D = l + t->Depth;
				if (D > Node->Depth)
					Node->Depth = D;
				t->DetachBone(Bone);
				Bone->DetachNode(t);
				delete t;
				Bone->DetachNode(Node);
				Node->DetachBone(Bone);
				Bone->DestroyWithDetach(); /// !!!
				delete Bone;
				if (Node->Kind() == TailNode)
					Node->moveIntoTail(Hairs);
			}
			else
				t->moveIntoTail(Nodes);
		}
		else
			delete t;
	}
	delete Hairs;
}


void TPolFigure::ClearAll()
{
	TConnected* Com = NULL; /*уничтожение компонент*/
	while (!Components->isEmpty())
	{
		Com = (TConnected*)Components->first();
		delete Com;
	}
}


TPolFigure::~TPolFigure()
{
	ClearAll();
	delete Components;
	Components = NULL;
	// todo check:  inherited::Destroy;
}


TPolFigure::TPolFigure(BitRaster* bitRaster, double Amin)
/*Построение компонент для матрицы с отбрасыванием малых контуров*/
{
	unsigned int TT, TT1;
	TT1 = TimeInMilSecond();
	Components = new LinkedListTail < TConnected > ;/*Порождение списка компонент*/
	
	ContourTracer* BinIm = new ContourTracer(bitRaster, Amin);
	BinIm->traceContours();

	CreateContours(BinIm);
	
	/*Упорядочение контуров АВЛ деревом*/
	if (!ElementsExist)
	{
		ProduceElements(this);
		ElementsExist = true;
	}
	TT = TimeInMilSecond();
	SpaningTree(this);
	MakeComponents();

	RTab.TimeTree = TimeInMilSecond() - TT;
	RTab.ConnectComp = CompCount;
	delete BinIm;
	RTab.TimeTrace = TimeInMilSecond() - TT1 - RTab.TimeTree;
	RTab.Total = RTab.TimeTrace + RTab.TimeTree + RTab.TimeSkelet + RTab.TimePrun;
}


void TPolFigure::CreateContours(ContourTracer *BinIm)
/*Построение контуров для бинарного образа BinIm*/
{
    ClosedPath* CP; /* контур из растрового образа (модуль Kontur) */
	RasterPoint* r;  /* точка контура (модуль Kontur) */
	TContour* S;       /* контур для скелетизации (модуль Structure) */
	int i = 0;
	RTab.Points = 0;
	RTab.Polygons = 0;
	CP = BinIm->initialContour();
	while (CP != NULL)
	{
		S = AddContour();
		S->Internal = CP->Internal;
		r = CP->initialPoint();
		i = 0;
		while (r != NULL)
		{
			S->AddPoint(r->x, r->y);
			i++;
			r = r->getNext();
		}
		if (i < 3)
			delete S;
		else
		{
			S->ShiftHead();
			if (S->Internal == S->ConterClockWise())
				S->Invert();
			S->ClosedPath = true;
			RTab.Polygons++;
			RTab.Points = RTab.Points + S->ListPoints->cardinal();
		}
		CP = CP->getNext();
	}
}

void TPolFigure::MakeComponents()
/*Формирование компонент из контуров*/
{
	TContour *S = NULL, *S1 = NULL, *S2 = NULL;
	TConnected* Com = NULL;
	/*Временное размещение внутренних контуров во внешние*/
	S = (TContour*)Boundary->first();
	while (S != NULL)
	{
		S1 = S->getNext();
		if (S->Internal)
		{
			S2 = S->Container;
			if (S2->MySons == NULL)
				S2->MySons = new LinkedListTail < TContour > ;
			S->moveIntoTail(S2->MySons);
		}
		S = S1;
	}
	/*Из каждого внешнего создается компонента*/
	S = (TContour*)Boundary->first();
	while (S != NULL)
	{
		if (!S->Internal)
		{
			Com = new TConnected;
			Com->Border = S;
			Com->moveIntoTail(Components);
			while (S->MySons != NULL)
			{
				while (!S->MySons->isEmpty())
				{
					S1 = (TContour*)S->MySons->first();
					Com->HoleList.push_back(S1);
					S1->moveIntoTail(Boundary);
				}
				delete S->MySons;
				S->MySons = NULL;
			}
		}
		S = S->getNext();
	}
}


void TPolFigure::Invert()/*Инверсия фигуры*/
{
	TContour* S = NULL;
	Point *p = NULL;
	double xmin = 0.0, Xmax = 0.0, ymin = 0.0, Ymax = 0.0;
	int W = 0;
	W = 100;
	ClearAll();
	xmin = 10000;
	Xmax = -10000;
	ymin = 10000;
	Ymax = -10000;
	S = (TContour*)Boundary->first();
	while (S != NULL)
	{
		S->Internal = !S->Internal;
		p = (Point*)S->ListPoints->first();
		while (p != NULL)
		{
			if (p->X < xmin)
				xmin = p->X;
			if (p->X > Xmax)
				Xmax = p->X;
			if (p->Y < ymin)
				ymin = p->Y;
			if (p->Y > Ymax)
				Ymax = p->Y;
			p = p->getNext();
		}
		S->Invert();
		S->Container = NULL;
		S->ClosestSite = NULL;
		if (S->MySons != NULL)
			delete S->MySons;
		S->MySons = NULL;
		S = S->getNext();
	}
	S = new TContour;
	S->Internal = false;
	p = new Point(xmin - W, ymin - W);
	p->moveIntoTail(S->ListPoints);
	p = new Point(Xmax + W, ymin - W);
	p->moveIntoTail(S->ListPoints);
	p = new Point(Xmax + W, Ymax + W);
	p->moveIntoTail(S->ListPoints);
	p = new Point(xmin - W, Ymax + W);
	p->moveIntoTail(S->ListPoints);
	S->moveIntoTail(Boundary);
	S->Fiction = true;
	S->ShiftHead();
	if (S->Internal == S->ConterClockWise())
		S->Invert();
	ElementsExist = false;
	ProduceElements(this);
	ElementsExist = true;
}


void TPolFigure::RestoreInversion()
/*Восстановление фигуры после инверсии*/
{
	TContour *S = NULL, *s0 = NULL;
    /*Удаление частей скелета, инцидентных фиктивному контуру*/
	ClearAll();
	SkelExist = false;
	/*  Com:=Components.first AS TConnected;
	  WHILE Com<>NIL DO
	  BEGIN
	  Bone:=Com.Bones.first AS TBone;
	  WHILE Bone<>NIL DO
	  BEGIN
	  Node:=Bone.Org;
	  Node1:=Bone.Dest;
	  Bone1:=Bone.suc AS TBone;
	  IF Bone.Fiction THEN (*ребро инцидентное фиктивному контуру*)
	  BEGIN
	  Bone.DestroyWithDetach;
	  IF Node.Kind=Isolated THEN Node.Destroy;
	  IF Node1.Kind=Isolated THEN Node1.Destroy;
	  END;
	  Bone:=Bone1;
	  END;
	  Com:=Com.suc AS TConnected;
	  END; */
	/*Инвертирование направления контуров*/
	S = (TContour*)Boundary->first();
	while (S != NULL)
	{
		S->Internal = !S->Internal;
		if (S->Fiction)
			s0 = S;
		else
		{
			S->Invert();
			S->Container = NULL;
			S->ClosestSite = NULL;
		}
		S = S->getNext();
	}
	delete s0;
}

void printNode(TNode *n)
{
    qDebug() << n->Disc->X << " " << n->Disc->Y << " " << n->Disc->Rad << endl;
}

void TPolFigure::MakeNodeBoneRepresentation()
/* Формирование структуры типа TPolFigure, описывающей
границу и внутренний скелет бинарной области из триангуляции.
Сама триангуляция при этом разрушается*/
{
	vector<Triplet*> ListOld;
	vector<TNode*> ListNew; /*Рабочие списки*/
    int M = 0;
	TNode* Node = NULL, *Node1 = NULL;
	TSite *S1 = NULL, *S2 = NULL;
	Triplet *Tr = NULL, *Tr1 = NULL;
	TBone* Bone = NULL;
	TConnected* Com = NULL;
	if ((Boundary == NULL) || Boundary->isEmpty())
		return;
	Com = (TConnected*)Components->first();
	while (Com != NULL)
	{
		Tr = (Triplet*)Com->Border->Map->MapTriplet->first();
		M = 0;
		while (Tr != NULL)
		{
			Node = new TNode;
			Node->Sites[1 - 1] = Tr->E1;
			Node->Sites[2 - 1] = Tr->E2;
			Node->Sites[3 - 1] = Tr->e3;
			Node->Disc = Tr->Circ;
			Tr->Circ = NULL;
			M++;
			Tr->Numb = M;
			ListOld.push_back(Tr);
			ListNew.push_back(Node);
			Node->moveIntoTail(Com->Nodes);  /* В список узлов */
			Tr = Tr->getNext();
            //printNode(Node);
		}
		/* M - число узлов*/

		/*Образование костей*/
		for (int stop = M - 1, i = 0; i <= stop; i++)
		{
			Tr = ListOld[i];
			Node = ListNew[i];
			for (int stop = 3, j = 1; j <= stop; j++)
			{
				switch (j)
				{
				case 1:
				{
					Tr1 = Tr->t1;
					S1 = Tr->e3;
					S2 = Tr->E1;
				}
					break;
				case 2:
				{
					Tr1 = Tr->t2;
					S1 = Tr->E1;
					S2 = Tr->E2;
				}
					break;
				case 3:
				{
					Tr1 = Tr->t3;
					S1 = Tr->E2;
					S2 = Tr->e3;
				}
					break;
				default:
					Tr1 = NULL;
				}
				if ((Tr1 != NULL) && (Tr->Numb < Tr1->Numb))
				{
					Node1 = ListNew[Tr1->Numb - 1];
					Bone = new TBone;
					Bone->org = Node;
					Bone->dest = Node1;
					if (S1->IsVertex() == !S2->IsVertex())
						Bone->Bisector(S1, S2); /*параболическое ребро*/
					Bone->moveIntoTail(Com->Bones);   /*В список костей*/
					Node->AddBone(Bone);
					Node1->AddBone(Bone);
				}
			}
		}
		ListOld.clear();
		ListNew.clear();
		delete Com->Border->Map;
		Com->Border->Map = NULL;
		Com = Com->getNext();
	}
	SkelExist = true;
	ListOld.clear();
	ListNew.clear();
	RTab.Vertex = NodeCount;
	RTab.Edges = BoneCount;
}


void TPolFigure::MakeTriangDel()
{
	unsigned int TT = 0;
	TT = TimeInMilSecond();
	if (!ElementsExist)
	{
		ProduceElements(this);
		ElementsExist = true;
	}
	CreateTriangulation(this);
	MakeNodeBoneRepresentation();
	MapExist = true;
	RTab.TimeSkelet = TimeInMilSecond() - TT;
	RTab.Total = RTab.TimeTrace + RTab.TimeTree + RTab.TimeSkelet + RTab.TimePrun;
}


void TPolFigure::CutSkeleton(double Eps)
/*Стрижка скелета*/
{
	TConnected* Com = NULL;
	unsigned int TT = 0;
	TT = TimeInMilSecond();
	Com = (TConnected*)Components->first();
	while (Com != NULL)
	{
		Com->CutSkeleton(Eps);
		Com = Com->getNext();
	}
	RTab.TimePrun = TimeInMilSecond() - TT;
	RTab.Total = RTab.TimeTrace + RTab.TimeTree + RTab.TimeSkelet + RTab.TimePrun;
	RTab.Vertex = NodeCount;
	RTab.Edges = BoneCount;
}


void TNode::AddBone(TBone* Bone) /*добавить кость*/
{
	if (Bones[1 - 1] == NULL)
		Bones[1 - 1] = Bone;
	else
		if (Bones[2 - 1] == NULL)
			Bones[2 - 1] = Bone;
		else
			if (Bones[3 - 1] == NULL)
				Bones[3 - 1] = Bone;
}
