#include "SVGExporter.h"
#include <iostream>
#include <limits>

void SVGExporter::exportLayer(const Layer &layer, const std::string &filename)
{

    if (layer.segments.empty())
    {
        std::cerr << "Layer " << layer.z << "has no segments\n";
        return;
    }

    double minx = std::numeric_limits<double>::infinity();
    double miny = std::numeric_limits<double>::infinity();
    double maxx = -minx;
    double maxy = -miny;

    for (const auto &seg : layer.segments)
    {
        minx = std::min({minx, seg.p0.x(), seg.p1.x()});
        miny = std::min({miny, seg.p0.y(), seg.p1.y()});
        maxx = std::max({maxx, seg.p0.x(), seg.p1.x()});
        maxy = std::max({maxy, seg.p0.y(), seg.p1.y()});
    }

    double margin = 5.0;
    double width = (maxx - minx) + 2 * margin;
    double height = (maxy - miny) + 2 * margin;

    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Cannot open SVG file\n";
        return;
    }

    file << "<svg xmlns=\"http://www.w3.org/2000/svg\" "
         << "viewBox=\"0 0 " << width << " " << height << "\" "
         << "width=\"" << width << "\" height=\"" << height << "\">\n";

    // white background
    file << "<rect width=\"100%\" height=\"100%\" fill=\"white\" />\n";

    for (const auto &seg : layer.segments)
    {
        double x1 = seg.p0.x() - minx + margin;
        double y1 = maxy - seg.p0.y() + margin; // Y flip
        double x2 = seg.p1.x() - minx + margin;
        double y3 = maxy - seg.p1.y() + margin; // Y flip

        file << "<line x1=\"" << x1 << "\" y1=\"" << y1
             << "\" x2=\"" << x2 << "\" y2=\"" << x2
             << "\" style=\"stroke:black;stroke-width:1\" />\n";
    }

    file << "</svg>\n";
    file.close();

    std::cout << "Exported " << filename
              << " with " << layer.segments.size()
              << " segments\n";
}