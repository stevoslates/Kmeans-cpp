#include <random>
#include <unordered_set>
#include <iostream>
#include "kmeans.h"
#include "cluster.h"
#include "point.h"

namespace Constants {
    constexpr double EPSILON = 1e-6;
}

//public - used for testing and also exposes the clusters 
std::vector<std::pair<double, double>> Kmeans::getCentroids() const {
    std::vector<std::pair<double, double>> centroids;
    for (const auto& cluster : clusters) {
        centroids.push_back(cluster.getCentroid());
    }
    return centroids;
}

void Kmeans::populateInitialClusters(const std::vector<Point>& points) {
    clusters.reserve(K);

    //Rand Selection of K points (TO DO: Wont Select same index twice)
    std::unordered_set<int> selected_indices;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, points.size() - 1);

    int cid {};
    while (selected_indices.size() < K) {
        int idx = distrib(gen);
        if (selected_indices.insert(idx).second) { //second tells us if we have entered it before or not
            const Point& p = points[idx];
            clusters.emplace_back(++cid, p.getX(), p.getY());
        }
    }    
}

double Kmeans::calcDistance(const Point& pt, const Cluster& c) {
    auto [x, y] = c.getCentroid();

    double dx = pt.getX() - x;
    double dy = pt.getY() - y;

    //return std::sqrt(dx * dx + dy * dy);
    return dx * dx + dy * dy;
}

Cluster& Kmeans::findClosestCluster(const Point& pt) { //returns reference to the closest cluster
    //use euclidean distance
    Cluster* closest {nullptr}; //try and avoid the use of a nullptr here 
    double minDistance = std::numeric_limits<double>::max();
    for (auto& c : clusters) {
        double distance = calcDistance(pt, c);
        if (distance < minDistance) {
            minDistance = distance;
            closest = &c;
        }
    }
    return *closest; //will return an &Cluster
} 

void Kmeans::updateNewClusterCentroids(const std::vector<Point>& points) {
    /*Loops through each cluster and with its assigned points calculates its new centroid */
    for (auto& cluster : clusters) {
        double sum_x = 0.0, sum_y = 0.0;
        int count = 0;
        for (int id : cluster.getPoints()) {
            const Point& p = points[id];  // correct for 1-based IDs //WAS -1 on the index
            sum_x += p.getX();
            sum_y += p.getY();
            ++count;
        }
        cluster.updateCentroid(sum_x / count, sum_y / count);
    }
}

bool Kmeans::hasConverged(const std::vector<std::pair<double,double>>& curClusters, const std::vector<std::pair<double,double>>& oldClusters) {
    //Need to account for floating point precision problems (using Global Epsilon)
    for (size_t i = 0; i < curClusters.size(); ++i) {
        double dx = std::abs(curClusters[i].first - oldClusters[i].first);
        double dy = std::abs(curClusters[i].second - oldClusters[i].second);
        if (dx > Constants::EPSILON || dy > Constants::EPSILON) {
            return false;  // centroids have moved too much
        }
    }
    return true;
}

void Kmeans::clearClusterAssignedPoints() {
    for (auto& c : clusters) {
        c.clearPoints();
    }
}

void Kmeans::run(std::vector<Point>& points) {

    populateInitialClusters(points);
    
    
    int iter {1};
    std::vector<std::pair<double,double>> oldClusters;

    //populate oldClusters for first iteration
    for (const auto& c: clusters) {
        oldClusters.push_back(c.getCentroid());
    }

    while (true) {
        clearClusterAssignedPoints();
        for (auto& p : points) {
            Cluster& new_c = findClosestCluster(p); //if this wanst a reference we would be copying it (remeber return by ref doesnt keep it)

            p.setClusterId(new_c.getClusterId()); //TO SET TO THAT CLUSTERS ID
            new_c.addPoint(p);
        }

        //here we need to update new cluster centroids
        updateNewClusterCentroids(points);
        
        std::vector<std::pair<double, double>> curCentroids;
        for (const auto& c: clusters) {
            curCentroids.push_back(c.getCentroid());
        }

        if (iter != 1 && hasConverged(curCentroids, oldClusters)) {
            break;
        }

        oldClusters = curCentroids;  // prepare for next iteration
        ++iter;
    }

    /*
    std::cout << "Number of Iterations: " << iter << "\n";
    for (const auto& cluster : clusters) {
        auto [cx, cy] = cluster.getCentroid();
        std::cout << "Cluster " << cluster.getClusterId() << " Centroid: (" << cx << ", " << cy << ")\n";
        std::cout << "Assigned Points: ";
        for (int id : cluster.getPoints()) {
            std::cout << id << " ";
        }
        std::cout << "\n\n";
    }
    */
}