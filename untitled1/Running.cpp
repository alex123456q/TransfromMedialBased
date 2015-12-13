#include "Running.h"


static void Running::print(vector<Polygon>& polygons){
    for (int i = 0; i < polygons.size(); ++i) {
        pred = polygons[i].getPoint(0);

        for (int j = 0; j < polygons[i].size(); ++j){
            cur = polygons[i].getPoint(j);
            std:: cout << cur.x()<<" "<<cur.y()<<std::endl;
        }
    }
};
