#include <iostream>
#include "../engine/mesh/Mesh.h"
#include "../engine/slicing/Slicer.h"
#include "../engine/slicing/SVGExporter.h"

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

    Slicer slicer(0.2); // layer height 0.2mm
    auto layers = slicer.sliceMesh(mesh);

    for (size_t i = 0; i < layers.size(); ++i)
    {
        std::string file_name = "layer_" + std::to_string(i) + ".svg";
        SVGExporter::exportLayer(layers[i], file_name);
    }

    std::cout << "SVG export done\n";

    return 0;
}