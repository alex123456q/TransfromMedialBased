#ifndef RUNNING_H
#define RUNNING_H

#include <vector>
#include <iostream>

#include "TransformMedialBased.h"

class Running{
public:
   static void print(vector<Polygon>& polygons){
       QPoint pred, cur;
       for (int i = 0; i < polygons.size(); ++i) {
           pred = polygons[i].getPoint(0);

           for (int j = 0; j < polygons[i].size(); ++j){
               cur = polygons[i].getPoint(j);
               std:: cout << cur.x()<<" "<<cur.y()<<std::endl;
           }
       }
   }
};

#endif // RUNNING_H
