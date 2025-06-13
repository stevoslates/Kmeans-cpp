#ifndef KMEANS_H
#define KMEANS_H

#include "cluster.h"

class Kmeans {

private:
    int K;
    std::vector<Cluster> clusters;
    //maybe need output file?

    void populateInitialClusters(const std::vector<Point>& points);
    Cluster& findClosestCluster(const Point& pt);
    void clearClusterAssignedPoints();
    double calcDistance(const Point& pt, const Cluster& c);
    bool hasConverged(const std::vector<std::pair<double,double>>&,
                    const std::vector<std::pair<double,double>>& oldClusters);
    void updateNewClusterCentroids(const std::vector<Point>& points);


public:
    explicit Kmeans(int k): K(k) {}
    void run(std::vector<Point>& points);
    std::vector<std::pair<double, double>> getCentroids() const;

    
};

#endif