#include "geolab/PinCallback.h"
#include "geolab/PinType.h"

#include <painting0/Color.h>
#include <blueprint/Pin.h>

#include <string>

#include <assert.h>

namespace
{

const pt0::Color COL_DEFAULT = pt0::Color(255, 255, 255);

// geometry
const pt0::Color COL_POINT  = pt0::Color(132, 228, 231);
const pt0::Color COL_VECTOR = pt0::Color(154, 239, 146);
const pt0::Color COL_CIRCLE = pt0::Color(246, 255, 154);
const pt0::Color COL_LINE   = pt0::Color(251, 203, 244);
const pt0::Color COL_PLANE  = pt0::Color(255, 139, 139);

// primitive
const pt0::Color COL_BOOLEAN = pt0::Color(148, 129, 230);
const pt0::Color COL_INTEGER = pt0::Color(148, 239, 230);
const pt0::Color COL_NUMBER  = pt0::Color(230, 148, 239);

// primitive

std::string get_desc_func(const std::string& name, int type)
{
    std::string ret = name;
    switch (type)
    {
        // geometry
    case geolab::PIN_POINT:
        ret += "(P)";
        break;
    case geolab::PIN_VECTOR:
        ret += "(V)";
        break;
    case geolab::PIN_CIRCLE:
        ret += "(C)";
        break;
    case geolab::PIN_LINE:
        ret += "(L)";
        break;
    case geolab::PIN_PLANE:
        ret += "(P)";
        break;

        // primitive
    case geolab::PIN_BOOLEAN:
        ret += "(b)";
        break;
    case geolab::PIN_INTEGER:
        ret += "(i)";
        break;
    case geolab::PIN_NUMBER:
        ret += "(f)";
        break;

    default:
        assert(0);
    }
    return ret;
}

const pt0::Color& get_color_func(int type)
{
    switch (type)
    {
        // geometry
    case geolab::PIN_POINT:
        return COL_POINT;
    case geolab::PIN_VECTOR:
        return COL_VECTOR;
    case geolab::PIN_CIRCLE:
        return COL_CIRCLE;
    case geolab::PIN_LINE:
        return COL_LINE;
    case geolab::PIN_PLANE:
        return COL_PLANE;

        // primitive
    case geolab::PIN_BOOLEAN:
        return COL_BOOLEAN;
    case geolab::PIN_INTEGER:
        return COL_INTEGER;
    case geolab::PIN_NUMBER:
        return COL_NUMBER;

    default:
        return COL_DEFAULT;
    }
}

bool can_type_cast_func(int type_from, int type_to)
{
    if (type_from == type_to) {
        return true;
    }
    if (type_from == bp::PIN_ANY_VAR ||
        type_to == bp::PIN_ANY_VAR) {
        return true;
    }

    return false;
}

}

namespace geolab
{

void InitPinCallback()
{
    bp::Pin::SetExtendFuncs({
        get_desc_func,
        get_color_func,
        can_type_cast_func
    });
}

}