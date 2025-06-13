# KMeans C++

## Overview
This is a standalone C++ implementation of the K-Means clustering algorithm. 


## Build Instructions

This project uses CMake for building.

```bash
mkdir build
cd build
cmake ..
make
```

## Usage 

The program accepts 3 command-line arguments:

```bash
./main <input_file> <output_file> <K>
```

## Input Format
The input (.txt) file should contain 2D points, one per line:

Example:

```bash
1.0 2.0
3.5 4.2
5.0 8.0
```

## Output Format
The output file will contain both the cluster assignments and the final centroids.

Example output:

```bash
Point Assignments:
Point ID: 0 assigned to Cluster: 1
Point ID: 1 assigned to Cluster: 2
Point ID: 2 assigned to Cluster: 1

Cluster Centroids:
Cluster 1 Centroid: (1.25, 2.75)
Cluster 2 Centroid: (5.0, 8.0)
```

## Currently Improving 
- Kmeans++ Initalisation 
- Parralelise Computations