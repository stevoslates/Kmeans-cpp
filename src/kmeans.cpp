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
std::vector<std::vector<double>> Kmeans::getCentroids() const {
    std::vector<std::vector<double>> centroids;
    for (const auto& cluster : clusters) {
        centroids.push_back(cluster.getCentroid());
    }
    return centroids;
}

void Kmeans::populateInitialClusters(const std::vector<Point>& points) {
    clusters.reserve(K); //we know K ahead of time -> we could maybe make this an array 

    std::unordered_set<int> selected_indices;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, points.size() - 1);

    int cid {};
    while (selected_indices.size() < K) {
        int idx = distrib(gen);
        if (selected_indices.insert(idx).second) {
            const Point& p = points[idx];
            clusters.emplace_back(++cid, p.getCoordinates());
        }
    }    
}

double Kmeans::calcDistance(const Point& pt, const Cluster& c) {
    const auto& p_coords = pt.getCoordinates();
    const auto& c_coords = c.getCentroid();

    double sum = 0.0;
    for (size_t i = 0; i < p_coords.size(); ++i) {
        double diff = p_coords[i] - c_coords[i];
        sum += diff * diff;
    }
    return sum;
}

Cluster& Kmeans::findClosestCluster(const Point& pt) {
    Cluster* closest {nullptr};
    double minDistance = std::numeric_limits<double>::max();
    for (auto& c : clusters) {
        double distance = calcDistance(pt, c);
        if (distance < minDistance) {
            minDistance = distance;
            closest = &c;
        }
    }
    return *closest;
}

void Kmeans::updateNewClusterCentroids(const std::vector<Point>& points) {
    for (auto& cluster : clusters) {
        std::vector<double> sum(cluster.getCentroid().size(), 0.0);
        int count = 0;
        for (int id : cluster.getPoints()) {
            const auto& coords = points[id].getCoordinates();
            for (size_t i = 0; i < coords.size(); ++i) {
                sum[i] += coords[i];
            }
            ++count;
        }
        for (double& val : sum) {
            val /= count;
        }
        cluster.updateCentroid(sum);
    }
}

bool Kmeans::hasConverged(const std::vector<std::vector<double>>& curClusters,
                           const std::vector<std::vector<double>>& oldClusters) 
{
    for (size_t i = 0; i < curClusters.size(); ++i) {
        for (size_t j = 0; j < curClusters[i].size(); ++j) {
            if (std::abs(curClusters[i][j] - oldClusters[i][j]) > Constants::EPSILON) {
                return false;
            }
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
    std::vector<std::vector<double>> oldClusters;

    for (const auto& c: clusters) {
        oldClusters.push_back(c.getCentroid());
    }

    while (true) {
        clearClusterAssignedPoints();
        for (auto& p : points) {
            Cluster& new_c = findClosestCluster(p);
            p.setClusterId(new_c.getClusterId());
            new_c.addPoint(p);
        }

        updateNewClusterCentroids(points);

        std::vector<std::vector<double>> curCentroids;
        for (const auto& c: clusters) {
            curCentroids.push_back(c.getCentroid());
        }

        if (iter != 1 && hasConverged(curCentroids, oldClusters)) {
            break;
        }

        oldClusters = curCentroids;
        ++iter;
    }
}
