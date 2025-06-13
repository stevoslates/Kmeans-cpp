#include "cluster.h"
#include "point.h"
#include "kmeans.h"
#include <cassert>
#include <iostream>
#include <cmath>

// ------------ POINT TESTS ------------
void testPoint() {
    Point p1(0, {1.0, 1.0});
    Point p2(1, {2.0, 1.0});

    assert(p1.getPointId() == 0 && "Not Getting Correct PID");
    assert(p2.getPointId() == 1 && "Not Getting Correct PID");

    p1.setClusterId(5);
    assert(p1.getClusterId() == 5 && "Cluster ID assignment failed");

    const auto& coords = p1.getCoordinates();
    assert(coords[0] == 1.0 && coords[1] == 1.0 && "Coordinates incorrect");
}

// ------------ CLUSTER TESTS ------------
void testClusterBasic() {
    Cluster c1(0, {2.0, 3.0});
    Point p1(0, {1.0, 1.0});

    c1.addPoint(p1);
    auto pts = c1.getPoints();
    assert(pts.find(p1.getPointId()) != pts.end());

    c1.clearPoints();
    pts = c1.getPoints();
    assert(pts.find(p1.getPointId()) == pts.end());

    auto centroid = c1.getCentroid();
    assert(centroid[0] == 2.0 && centroid[1] == 3.0 && "Incorrect Centroid");
}

void testClusterClearEmpty() {
    Cluster c(0, {1.0, 1.0});
    c.clearPoints();
    assert(c.getPoints().empty());
}

// ------------ RUN TEST ------------
void testKmeansRun() {
    std::vector<Point> points = {
        Point(0, {1.0, 2.0}),
        Point(1, {1.5, 1.8}),
        Point(2, {5.0, 8.0}),
        Point(3, {6.0, 8.5}),
        Point(4, {1.2, 1.9}),
        Point(5, {5.5, 8.3})
    };

    Kmeans kmeans(2);
    kmeans.run(points);
    auto centroids = kmeans.getCentroids();

    constexpr double EPS = 0.2;

    std::vector<std::vector<double>> expected = {
        {1.233, 1.9},
        {5.5, 8.266}
    };

    for (const auto& centroid : centroids) {
        std::cout << "Centroid at: (";
        for (size_t i = 0; i < centroid.size(); ++i) {
            std::cout << centroid[i];
            if (i != centroid.size() - 1) std::cout << ", ";
        }
        std::cout << ")\n";
    }

    for (const auto& exp : expected) {
        bool match_found = false;
        for (const auto& centroid : centroids) {
            bool close = true;
            for (size_t i = 0; i < centroid.size(); ++i) {
                if (std::abs(centroid[i] - exp[i]) >= EPS) {
                    close = false;
                    break;
                }
            }
            if (close) {
                match_found = true;
                break;
            }
        }
        assert(match_found && "Centroid mismatch");
    }

    std::cout << "KMeans integration test passed.\n";
}

// ------------ MAIN ------------
int main() {
    testPoint();
    testClusterBasic();
    testClusterClearEmpty();
    testKmeansRun();

    std::cout << "All tests passed successfully.\n";
    return 0;
}
