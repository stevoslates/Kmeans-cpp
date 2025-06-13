cmake_minimum_required(VERSION 3.10)

project(KMeansProject)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include headers
include_directories(include)

# Source files (shared by all targets)
set(SOURCES
    src/main.cpp
    src/kmeans.cpp
    src/io.cpp
)

# Build main executable
add_executable(main ${SOURCES})

# Build test executable (reuse same sources, different entry point)
add_executable(test
    tests/test.cpp
    src/kmeans.cpp
    src/io.cpp
)
