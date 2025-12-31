cmake_minimum_required(VERSION 3.16)
project(OpenSlicer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CGAL REQUIRED)

include_directories(
    third_party/stl_reader
    engine
)

add_executable(openslicer
    app/main.cpp
    engine/mesh/Mesh.cpp
    engine/slicing/Slicer.cpp
    engine/slicing/SVGExporter.cpp
)

target_link_libraries(openslicer CGAL::CGAL)