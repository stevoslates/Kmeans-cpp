#ifndef CLUSTER_H
#define CLUSTER_H

#include <unordered_set>
#include "point.h"
#include <utility>

class Cluster {

public:
    int clusterId;
    double centroid_x;
    double centroid_y;
    std::unordered_set<int> assignedPoints;

    //Constructor to be called when intialising for first time with random point
    Cluster(int c_id, double c_x, double c_y): clusterId(c_id), centroid_x(c_x), centroid_y(c_y) {} 

    //Point Funcs
    void clearPoints() {assignedPoints.clear();}
    void addPoint(const Point& pt) { assignedPoints.insert(pt.getPointId()); }
    std::unordered_set<int> getPoints() const {return assignedPoints;}
    
    int getClusterId() const {return clusterId;}
    //CentroidFuncs
    //maybe change so we pass in a pair
    void updateCentroid(double new_cx, double new_cy) {centroid_x=new_cx; centroid_y=new_cy;}
    std::pair<double, double> getCentroid() const {return {centroid_x, centroid_y};} 


};

#endif