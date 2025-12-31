#include "Mesh.h"
#include "stl_reader.h"
#include <limits>
#include <iostream>

bool Mesh::loadSTL(const std::string &filename)
{
    stl_reader::StlMesh<double, unsigned int> mesh(filename);

    if (mesh.num_tris() == 0)
    {
        std::cerr << "Failed to load STL or empty mesh\n";
        return false;
    };

    m_triangles.clear();
    m_triangles.reserve(mesh.num_tris());

    for (size_t i = 0; i < mesh.num_tris(); ++i)
    {
        const double *v0 = mesh.tri_corner_coords(i, 0);
        const double *v1 = mesh.tri_corner_coords(i, 1);
        const double *v2 = mesh.tri_corner_coords(i, 2);

        m_triangles.push_back({Point3(v0[0], v0[1], v0[2]),
                               Point3(v1[0], v1[1], v1[2]),
                               Point3(v2[0], v2[1], v2[2])});
    }

    computeBounds();
    return true;
}

void Mesh::computeBounds()
{
    double inf = std::numeric_limits<double>::infinity();

    double minx = inf, miny = inf, minz = inf;
    double maxx = -inf, maxy = -inf, maxz = -inf;

    for (const auto &tri : m_triangles)
    {
        const Point3 pts[3] = {tri.v0, tri.v1, tri.v2};
        for (const auto &p : pts)
        {
            minx = std::min(minx, p.x());
            miny = std::min(miny, p.y());
            minz = std::min(minz, p.z());
            maxx = std::max(maxx, p.x());
            maxy = std::max(maxy, p.y());
            maxz = std::max(maxz, p.z());
        }
    }

    m_min = Point3(minx, miny, minz);
    m_max = Point3(maxx, maxy, maxz);
}
