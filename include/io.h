#ifndef IO_H
#define IO_H

#include <string>
#include <vector>
#include "point.h"
#include "kmeans.h"

namespace io {

    bool populatePointsFromFile(const std::string& filename, std::vector<Point>& points);

    void writeResultsToFile(const std::string& filename, const Kmeans& kmeans, const std::vector<Point>& points);

}

#endif
