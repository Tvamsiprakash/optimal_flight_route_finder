cmake_minimum_required(VERSION 3.10)
project(flight_optimizer)

set(CMAKE_CXX_STANDARD 17)

# Add include directory for headers
include_directories(include)

# Add executable from source files
add_executable(flight_optimizer
    source/main.cpp
    source/graph.cpp
    source/airport.cpp
    source/route.cpp
)
