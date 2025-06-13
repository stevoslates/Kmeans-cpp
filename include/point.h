#ifndef POINT_H
#define POINT_H

class Point {

private:
    double x;
    double y;
    int pointId;
    int clusterId = -1; //Dummy ClusterID Upon Construction

public:
    Point(int pointId, double x, double y): pointId(pointId), x(x), y(y) {} 
    int getPointId() const {return pointId;};
    int getX() const {return x;};
    int getY() const {return y;};
    int getClusterId() const {return clusterId;};
    void setClusterId(int id) {clusterId=id;};
};

#endif