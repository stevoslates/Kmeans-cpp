#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono> 
#include "point.h"
#include "kmeans.h"
#include "io.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: ./kmeans <input_file> <output_file> <K>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    int K = std::stoi(argv[3]);

    std::vector<Point> points;
    if (!io::populatePointsFromFile(inputFile, points)) {
        return 1;
    }

    if (K <= 0 || K > points.size()) {
        std::cerr << "Error: K must be between 1 and " << points.size() << std::endl;
        return 1;
    }

    Kmeans kmeans(K);
    kmeans.run(points);
    io::writeResultsToFile(outputFile, kmeans, points);

    return 0;
}
