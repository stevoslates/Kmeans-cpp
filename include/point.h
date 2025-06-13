#ifndef POINT_H
#define POINT_H

#include <vector>

class Point {

private:
    //double x;
    //double y;
    std::vector<double> coordinates;
    int pointId;
    int clusterId = -1; //Dummy ClusterID Upon Construction

public:
    //Point(int pointId, double x, double y): pointId(pointId), x(x), y(y) {}
    Point(int id, const std::vector<double>& coords)
        : pointId(id), coordinates(coords) {}
    int getPointId() const {return pointId;};
    //int getX() const {return x;};
    //int getY() const {return y;};
    const std::vector<double>& getCoordinates() const { return coordinates; }
    int getClusterId() const {return clusterId;};
    void setClusterId(int id) {clusterId=id;};
};

#endif