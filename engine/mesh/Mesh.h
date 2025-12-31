#pragma once
#include <vector>
#include <CGAL/Simple_cartesian.h>

using Kernel = CGAL::Simple_cartesian<double>;
using Point3 = Kernel::Point_3;

struct Triangle
{
    Point3 v0, v1, v2;
};

class Mesh
{
public:
    bool loadSTL(const std::string &filename);

    const std::vector<Triangle> &triangles() const
    {
        return m_triangles;
    }

    Point3 minBound() const { return m_min; }
    Point3 maxBound() const { return m_max; }

private:
    std::vector<Triangle> m_triangles;
    Point3 m_min, m_max;

    void computeBounds();
};