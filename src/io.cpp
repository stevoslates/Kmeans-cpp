#include "io.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace io {

    bool populatePointsFromFile(const std::string& filename, std::vector<Point>& points) {
        /*
        TO DO: Need to add a check ensuring they are all the same dimension!
        */


        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "Error: Cannot open file: " << filename << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(infile, line)) {
            if (line.empty()) continue;

            std::istringstream iss(line);
            std::vector<double> coords;
            double value;
            while (iss >> value) {
                coords.push_back(value);
            }

            if (coords.empty()) {
                std::cerr << "Error: Malformed or empty line: " << line << std::endl;
                return false;
            }

            // pointId simply based on size (zero-based IDs)
            Point p{static_cast<int>(points.size()), coords};
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
            outfile << "Cluster " << (i + 1) << " Centroid: (";
            const auto& coords = centroids[i];
            for (size_t j = 0; j < coords.size(); ++j) {
                outfile << coords[j];
                if (j != coords.size() - 1) outfile << ", ";
            }
            outfile << ")\n";
        }
    }

}
