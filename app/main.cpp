#include <iostream>
#include "mesh/Mesh.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: openslicer model.stl\n";
        return 1;
    }

    Mesh mesh;
    if (!mesh.loadSTL(argv[1]))
    {
        return 1;
    }

    std::cout << "STL loaded successfully\n";
    std::cout << "Triangle count: " << mesh.triangles().size() << "\n";

    auto min = mesh.minBound();
    auto max = mesh.maxBound();

    std::cout << "Bounding box:\n";
    std::cout << "Min: (" << min.x() << ", " << min.y() << ", " << min.z() << ")\n";
    std::cout << "Max: (" << max.x() << ", " << max.y() << ", " << max.z() << ")\n";

    return 0;
}