#pragma once
#include "../mesh/Mesh.h"
#include "Layer.h"
#include <vector>

class Slicer
{
public:
    Slicer(double layer_height) : m_layer_height(layer_height) {}

    std::vector<Layer> sliceMesh(const Mesh &mesh);

private:
    double m_layer_height;
    bool intersectsPlane(const Triangle &tri, double z, Point3 &i0, Point3 &i1);
};