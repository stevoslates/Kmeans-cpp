#include "io.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace io {

    bool populatePointsFromFile(const std::string& filename, std::vector<Point>& points) {
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "Error: Cannot open file: " << filename << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(infile, line)) {
            if (line.empty()) continue;

            std::istringstream iss(line);
            double x, y;
            if (!(iss >> x >> y)) {
                std::cerr << "Error: Malformed line: " << line << std::endl;
                return false;
            }

            Point p{static_cast<int>(points.size()), x, y};
            points.push_back(p);
        }

        if (points.empty()) {
            std::cerr << "Error: No valid points found in file." << std::endl;
            return false;
        }

        return true;
    }

    void writeResultsToFile(const std::string& filename, const Kmeans& kmeans, const std::vector<Point>& points) {
        std::ofstream outfile(filename);
        if (!outfile.is_open()) {
            std::cerr << "Error: Cannot open output file: " << filename << std::endl;
            return;
        }

        outfile << "Point Assignments:\n";
        for (const auto& p : points) {
            outfile << "Point ID: " << p.getPointId() 
                    << " assigned to Cluster: " << p.getClusterId() << "\n";
        }

        outfile << "\nCluster Centroids:\n";
        auto centroids = kmeans.getCentroids();
        for (size_t i = 0; i < centroids.size(); ++i) {
            outfile << "Cluster " << (i + 1) << " Centroid: (" 
                    << centroids[i].first << ", " << centroids[i].second << ")\n";
        }
    }

}
