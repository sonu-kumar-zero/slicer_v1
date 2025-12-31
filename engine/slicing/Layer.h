#pragma once
#include <vector>
#include <CGAL/Simple_cartesian.h>

using Kernel = CGAL::Simple_cartesian<double>;
using Point3 = Kernel::Point_3;
using Point2 = Kernel::Point_2;

struct Segment2D
{
    Point2 p0, p1;
};

struct Layer
{
    double z;
    std::vector<Segment2D> segments;
};
