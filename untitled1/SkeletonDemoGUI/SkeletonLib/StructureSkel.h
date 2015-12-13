# pragma once

/*Модуль содержит описание структуры скелета в терминах классы-объекты.
  Этот модуль наследует многие вещи из модуля StructureTD, поскольку
  исторически был написан после него. Модуль StructureSkel описывает
  скелет как подмножество диаграммы Вороного, а модуль StructureTD
  описывает граф смежности сайтов - обобщённую триангуляцию Делоне,
  являющуюся двойственным графом для диаграммы Вороного*/

#include "math.h"
#include "LinkedList.h"
#include "ContourTracer.h"
#include "StructureTD.h"
#include "TriDel.h"
#include "SpanTree.h"
#include <ctime>
#include <QDebug>

#include <sstream>
#include <fstream>
using std::stringstream;
using std::ofstream;

struct ResultTable;
class TBone;
class TConnected;
class TNode;
class TPolFigure;
typedef unsigned int unsignedint;


typedef Point TPoint;
typedef Element TSite;
typedef Vertex TVertex;
typedef Edge TEdge;


/*Таблица для формирования статистики вычислений*/
struct ResultTable {
	int BMPm, BMPn;  /* размеры образа строли - столбцы */
	int Polygons;   /* количество полигональных контуров */
	int ConnectComp;/* количество связных копонент */
	int Points;     /* количество вершин в полигонах */
	int Vertex;     /* количество вершин в скелете */
	int Edges;     /* количество ребер в скелете */
	unsigned int TimeTrace;  /* время трассировки */
	unsigned int TimeTree;   /*Время построения дерева смежности контуров*/
	unsigned int TimeSkelet; /* время скелетизации */
	unsigned int TimePrun; /* время стрижки*/
	unsigned int Total; /* время общее*/
	ResultTable() {
		BMPm = BMPn = Polygons = ConnectComp = Points = Vertex = Edges = 0;
		TimeTrace = TimeTree = TimeSkelet = TimePrun = Total = 0;
	}
};


enum NodeKind {
	Isolated,
	TailNode,
	JointNode,
	ForkNode
};
/*Возможные типы узла: изолироанный,хвост, сустав,
  развилка - по числу выходящих костей 0,1,2,3 */

class TNode : public LinkedListElement < TNode > /*Элемент скелета типа 'узел'*/ {
	friend class TBone;
	friend class TConnected;
	friend class TPolFigure;
public:
	int Number;  /*Порядковый номер*/
	TDisc* Disc; /*Пустой круг узла*/
	TSite* Sites[3]; /*Массив инцидентных сайтов*/
	TBone* Bones[3]; /*массив инцидентных костей*/
	double Depth; /*глубина, используемая при стрижке*/
	TBone* Merge;  /* Кость от присоединяемого штриха */
	double X();   //  координаты
	double Y();   //  узла
	double r();   //  и радиус его пустого круга
	NodeKind Kind(); /*определение типа узла*/
	TNode();
	virtual ~TNode();
	void AddBone(TBone* Bone); /*добавить кость*/
	void DetachBone(TBone* Bone); /*отцепить кость*/
};


class TBone : public LinkedListElement < TBone > /*Элемент скелета типа 'кость'*/ {
	friend class TConnected;
	friend class TNode;
	friend class TPolFigure;
public:
	TConnected* Com; /*компонента, к которой относится кость*/
	TNode* org, *dest; /*Начальный и конечный узлы кости*/
	bool Met;      /* Метка */
	TPoint* Virt; /*Контрольная точка для ребра-параболы, NIL для отрезка*/
	TBone();
	virtual ~TBone();
	void DestroyWithDetach(); /*отцепиться и уничтожить кость*/
	TNode* GetNextNode(TNode* Source);
	/*узел, противоположный Node на этой же кости*/
	void DetachNode(TNode* Node);
	/*отцепиться от узла*/
	void Bisector(TSite *E1, TSite *E2); /*Вычисление параболического бисектора*/
	void BezierPoints(double& X1, double& Y1, double& X2, double& Y2);
	/*Вычисление контрольных точек для параболического ребра*/
	bool Fiction(); /*кость вдоль фиктивного контура */
};


class TConnected : public LinkedListElement < TConnected >
	/*Связная компонента многоугольной фигуры */ {
	friend class TBone;
	friend class TNode;
	friend class TPolFigure;
public:
	TContour* Border;  /*Внешний контур компоненты*/
	LinkedListTail<TNode>* Nodes;  /*Список узлов скелета компоненты*/
	LinkedListTail<TBone>* Bones;  /*Список костей скелета компоненты*/
	/*скелет компненты - только то, что лежит внутри нее*/
	vector<TContour*> HoleList; /*Список дыр - внутренних контуров компоненты*/
	void CutSkeleton(double Eps);
	/*стрижка-укорачивание на Eps - точность*/
	TConnected();
	virtual ~TConnected();
};


class TPolFigure : public Domain
	/*Граничное и скелетное представление бинарной области */
	/*Описание скелета области в виде списков узлов и костей*/ {
	typedef Domain inherited;
	friend class TBone;
	friend class TConnected;
	friend class TNode;
public:
	LinkedListTail<TConnected>* Components;  /*Список компонент многоуг.фигуры*/
	bool SkelExist; /*Признак, что скелет построен*/
	bool InternalSkel;  /*Текущий скелет - внутрений*/
	ResultTable RTab;  /*Статистика вычислений*/
	virtual ~TPolFigure();
	TPolFigure(BitRaster* PM, double Amin);
	/*Построение компонент для битмапа с отбрасыванием малых контуров*/
	void CreateContours(ContourTracer *BinIm);
	/*Построение контуров для бинарного образа BinIm*/
	void MakeComponents();
	/*Формирование компонент из контуров*/
	void Invert();
	/*Инверсия фигуры*/
	void RestoreInversion();
	/*Восстановление фигуры после инверсии*/
	void ClearAll(); /*Чистка всех списков*/
	void MakeNodeBoneRepresentation();
	/*Построение скелета по графу смежности (трианг.Делоне)*/
	void MakeTriangDel();  /*Построение графа смежности*/
	void CutSkeleton(double Eps); /*Стрижка скелета с параметром Eps*/
    TPolFigure() {}
};


unsignedint TimeInMilSecond(); /*Текущее время в миллисекундах*/
extern int NodeCount, BoneCount, CompCount; /*Число узлов, костей и компонент*/
