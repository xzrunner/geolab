#pragma once

#include <gh/typedef.h>
#include <gh/ParamType.h>

namespace gh { class Component; }
namespace bp { class Node; class Pin; }

namespace ghv
{

class Evaluator;

class GhAdapter
{
public:
    static void UpdatePropBackFromFront(const bp::Node& front,
        gh::Component& back, const Evaluator& eval);

    static gh::CompPtr CreateBackFromFront(const bp::Node& front);

    static int TypeBackToFront(gh::ParamType type);

}; // SOP

}