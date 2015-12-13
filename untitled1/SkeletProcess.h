#ifndef SKELETPROCESS_H
#define SKELETPROCESS_H

#include "SkeletonDemoGUI/SkeletonLib/BSTrans.h"
#include <vector>

class SkeletProcess{
    TPolFigure *skeleton;
public:
    std::vector<TNode*> pivots;
    SkeletProcess(TPolFigure*);
    void Rotate(double, double);
//    void Rotate(TNode*, TBone*);
    TNode* setPivot(double, double, TBone*);
};

#endif // SKELETPROCESS_H
