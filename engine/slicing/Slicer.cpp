#include "Slicer.h"
#include <algorithm>
#include <iostream>

bool Slicer::intersectsPlane(const Triangle &tri, double z, Point3 &i0, Point3 &i1)
{
    // Collect vertices above/below plane
    std::vector<Point3> above, below;
    const Point3 pts[3] = {tri.v0, tri.v1, tri.v2};
    for (const auto &p : pts)
    {
        if (p.z() > z)
            above.push_back(p);
        else
            below.push_back(p);
    };

    if (above.empty() || below.empty())
        return false; // No intersection

    // Triangle intesects plane in a segment between two points
    auto intersectEdge = [&](const Point3 &p1, const Point3 &p2)
    {
        double t = (z - p1.z()) / (p2.z() - p1.z());
        double x = p1.x() + t * (p2.x() - p1.x());
        double y = p1.y() + t * (p2.y() - p1.y());
        return Point3(x, y, z);
    };

    // Find the two edges that cross the plane
    std::vector<Point3> cross_points;
    for (int i = 0; i < 3; i++)
    {
        const Point3 &p1 = pts[i];
        const Point3 &p2 = pts[(i + 1) % 3];
        if ((p1.z() - z) * (p2.z() - z) < 0)
        {
            cross_points.push_back(intersectEdge(p1, p2));
        }
    }

    if (cross_points.size() != 2)
        return false;

    i0 = cross_points[0];
    i1 = cross_points[1];
    return true;
}

std::vector<Layer> Slicer::sliceMesh(const Mesh &mesh)
{
    std::vector<Layer> layers;

    double minZ = mesh.minBound().z();
    double maxZ = mesh.maxBound().z();

    for (double z = minZ + m_layer_height; z <= maxZ; z += m_layer_height)
    {
        Layer layer;
        layer.z = z;

        for (const auto &tri : mesh.triangles())
        {
            Point3 i0, i1;
            if (intersectsPlane(tri, z, i0, i1))
            {
                layer.segments.push_back({Point2(i0.x(), i0.y()), Point2(i1.x(), i1.y())});
            }
        }

        layers.push_back(layer);
    }

    std::cout << "Total layers: " << layers.size() << "\n";
    return layers;
}