#pragma once
#include "Layer.h"
#include <string>
#include <vector>
#include <fstream>

class SVGExporter
{
public:
    static void exportLayer(const Layer &layer, const std::string &filename);
};