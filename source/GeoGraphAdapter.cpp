#include "geolab/GeoGraphAdapter.h"
#include "geolab/RegistNodes.h"
#include "geolab/PinType.h"
#include "geolab/Node.h"

#include <blueprint/Node.h>
#include <blueprint/Pin.h>

#include <geograph/Component.h>

namespace geolab
{

void GeoGraphAdapter::UpdatePropBackFromFront(const bp::Node& front, geograph::Component& back,
                                        const Evaluator& eval)
{
    auto f_type = front.get_type();
    auto b_type = back.get_type();
    if (f_type.is_derived_from<Node>() &&
        b_type.is_derived_from<geograph::Component>())
    {
        for (auto& dst_prop : b_type.get_properties())
        {
            auto src_prop = f_type.get_property(dst_prop.get_name());
            assert(src_prop.is_valid());
            dst_prop.set_value(back, src_prop.get_value(front));
        }
    }
}

geograph::CompPtr GeoGraphAdapter::CreateBackFromFront(const bp::Node& node)
{
    auto type = node.get_type();
    auto src_type = type.get_name().to_string();
    std::string dst_type;
    std::string lib_str = "geograph";
    auto find_lib = src_type.find("geolab::");
    if (find_lib != std::string::npos) {
        dst_type = lib_str + "::" + src_type.substr(find_lib + strlen("geolab::"));
    }

    geograph::CompPtr dst = nullptr;

    if (!dst_type.empty())
    {
	    rttr::type t = rttr::type::get_by_name(dst_type);
        // fixme: specify node type
	    if (!t.is_valid())
        {
            assert(0);
	    }
        else
        {
            rttr::variant var = t.create();
            assert(var.is_valid());

            dst = var.get_value<std::shared_ptr<geograph::Component>>();
            assert(dst);
        }
    }

    if (node.get_type().is_derived_from<Node>()) {
        dst->SetName(static_cast<const Node&>(node).GetName());
    }

    return dst;
}


int GeoGraphAdapter::TypeBackToFront(geograph::ParamType type)
{
    int ret = -1;

    switch (type)
    {
        // geometry
    case geograph::ParamType::Point:
        ret = PIN_POINT;
        break;
    case geograph::ParamType::Vector:
        ret = PIN_VECTOR;
        break;
    case geograph::ParamType::Circle:
        ret = PIN_CIRCLE;
        break;
    case geograph::ParamType::Line:
        ret = PIN_LINE;
        break;
    case geograph::ParamType::Plane:
        ret = PIN_PLANE;
        break;

        // primitive
    case geograph::ParamType::Boolean:
        ret = PIN_BOOLEAN;
        break;
    case geograph::ParamType::Integer:
        ret = PIN_INTEGER;
        break;
    case geograph::ParamType::Number:
        ret = PIN_NUMBER;
        break;

    default:
        assert(0);
    }

    return ret;
}

}