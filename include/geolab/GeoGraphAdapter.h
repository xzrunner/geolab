#pragma once

#include <geograph/typedef.h>
#include <geograph/ParamType.h>

namespace geograph { class Component; }
namespace bp { class Node; class Pin; }

namespace geolab
{

class Evaluator;

class GeoGraphAdapter
{
public:
    static void UpdatePropBackFromFront(const bp::Node& front,
        geograph::Component& back, const Evaluator& eval);

    static geograph::CompPtr CreateBackFromFront(const bp::Node& front);

    static int TypeBackToFront(geograph::ParamType type);

}; // SOP

}