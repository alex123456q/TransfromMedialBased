#ifndef TRANSFORMMEDIALBASED_H
#define TRANSFORMMEDIALBASED_H

#include <vector>
#include <QPoint>

using namespace std;

class Polygon{
private:
    vector<QPoint> vertices;
public:
    Polygon(){}
    Polygon(QPoint p){
        vertices.push_back(p);
    }
    int size(){
        return vertices.size();
    }

    QPoint* start(){
        return &vertices[0];
    }
    void addPoint(int x, int y){
        vertices.push_back( QPoint( x, y ));
    }
    void addPoint(QPoint p){
        vertices.push_back(p);
    }
    void delPoint(){
        vertices.pop_back();
    }
    QPoint getPoint(int index){
        return vertices[index];
    }
    bool isEmpty(){
        return vertices.empty();
    }
    QPoint getLastPoint(){
        return vertices.back();
    }
    vector<QPoint> getAll(){
        return vertices;
    }
};


#endif // TRANSFORMMEDIALBASED_H
