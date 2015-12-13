#include "SkeletProcess.h"

SkeletProcess::SkeletProcess(TPolFigure* sk){
    skeleton = sk;
}

TNode *SkeletProcess::setPivot(double x, double y, TBone* Bone){
//            bool Collinear(Point *r0, Point *r1, Point *r2);

//    TConnected* Com = skeleton->Components->first();
//    bool f = false;
    if (pow(x-Bone->org->X(), 2)+pow(y-Bone->org->Y(), 2)<100)
        return Bone->org;
    if (pow(x-Bone->dest->X(), 2)+pow(y-Bone->dest->Y(), 2)<100)
        return Bone->dest;
    std::cout <<"NULL" <<std::endl;
    return NULL;
    TNode* newVert = new TNode;
    newVert->Disc = new TDisc(x, y, 0);
//    TBone* Bone = NULL;
//    int i = 0;
//    while (Com != NULL && !f) {
//        Bone = Com->Bones->first();
//        while (Bone != NULL && !f) {
//            f = Collinear(&Point(Bone->org->X(), Bone->org->Y()),
//                          &Point(Bone->dest->Disc->X,Bone->dest->Disc->Y),
//                          &Point(x, y));
//            i++;
//            f = true;
//            if (!f)
//                Bone = Bone->getNext();
//        };
//       if (!f)
//           Com = Com->getNext();
//    }
//    if (f == true)
//        std::cout << "TRUEEEEEE";
//    std:cout << "AFTER   "<<i<<std::endl;
    newVert->Disc->Rad = (Bone->org->Disc->Rad+Bone->dest->Disc->Rad)/2;
    TBone* newBone = new TBone; //LinkedListElement < TBone >
    newBone->org = newVert;
    newBone->dest = Bone->dest;

    newBone->dest->DetachBone(Bone);
    newBone->dest->AddBone(newBone);

    Bone->dest = newVert;
    newVert->AddBone(newBone);
    newVert->AddBone(Bone);

    newBone->moveAsNextFor(Bone);
    newVert->moveAsNextFor(Bone->org);
//    newVert->Kind();

    return newVert;
}
    //    Com->Nodes->moveAsNextFor();

/*
 *
 * Something from triang to skelet
 *
 *
 *
 *
 *
 * */
//            TConnected* Com; /*компонента, к которой относится кость*/
//            TNode* org, *dest; /*Начальный и конечный узлы кости*/
//            bool Met;      /* Метка */
//            TPoint* Virt; /*Контрольная точка для ребра-параболы, NIL для отрезка*/

//            vector<Triplet*> ListOld;
//            vector<TNode*> ListNew; /*Рабочие списки*/
//            int M = 0;
//            TNode* Node = NULL, *Node1 = NULL;
//            TSite *S1 = NULL, *S2 = NULL;
//            Triplet *Tr = NULL, *Tr1 = NULL;
//            TBone* Bone = NULL;
//            TConnected* Com = NULL;
//            if ((Boundary == NULL) || Boundary->isEmpty())
//                return;
//            Com = (TConnected*)Components->first();
//            while (Com != NULL)
//            {
//                Tr = (Triplet*)Com->Border->Map->MapTriplet->first();
//                M = 0;
//                while (Tr != NULL)
//                {
//                    Node = new TNode;
//                    Node->Sites[1 - 1] = Tr->E1;
//                    Node->Sites[2 - 1] = Tr->E2;
//                    Node->Sites[3 - 1] = Tr->e3;
//                    Node->Disc = Tr->Circ;
//                    Tr->Circ = NULL;
//                    M++;
//                    Tr->Numb = M;
//                    ListOld.push_back(Tr);
//                    ListNew.push_back(Node);
//                    Node->moveIntoTail(Com->Nodes);  /* В список узлов */
//                    Tr = Tr->getNext();
//                    //printNode(Node);
//                }
//                /* M - число узлов*/

//                /*Образование костей*/
//                for (int stop = M - 1, i = 0; i <= stop; i++)
//                {
//                    Tr = ListOld[i];
//                    Node = ListNew[i];
//                    for (int stop = 3, j = 1; j <= stop; j++)
//                    {
//                        switch (j)
//                        {
//                        case 1:
//                        {
//                            Tr1 = Tr->t1;
//                            S1 = Tr->e3;
//                            S2 = Tr->E1;
//                        }
//                            break;
//                        case 2:
//                        {
//                            Tr1 = Tr->t2;
//                            S1 = Tr->E1;
//                            S2 = Tr->E2;
//                        }
//                            break;
//                        case 3:
//                        {
//                            Tr1 = Tr->t3;
//                            S1 = Tr->E2;
//                            S2 = Tr->e3;
//                        }
//                            break;
//                        default:
//                            Tr1 = NULL;
//                        }
//                        if ((Tr1 != NULL) && (Tr->Numb < Tr1->Numb))
//                        {
//                            Node1 = ListNew[Tr1->Numb - 1];
//                            Bone = new TBone;
//                            Bone->org = Node;
//                            Bone->dest = Node1;
//                            if (S1->IsVertex() == !S2->IsVertex())
//                                Bone->Bisector(S1, S2); /*параболическое ребро*/
//                            Bone->moveIntoTail(Com->Bones);   /*В список костей*/
//                            Node->AddBone(Bone);
//                            Node1->AddBone(Bone);
//                        }
//                    }
//                }
//                ListOld.clear();
//                ListNew.clear();
//                delete Com->Border->Map;
//                Com->Border->Map = NULL;
//                Com = Com->getNext();
//            }
//            SkelExist = true;
//            ListOld.clear();
//            ListNew.clear();
//            RTab.Vertex = NodeCount;
//            RTab.Edges = BoneCount;
//        }


