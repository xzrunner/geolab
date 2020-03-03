#include "geolab/RegistNodes.h"

#include <ee0/ReflectPropTypes.h>

#include <js/RTTR.h>

RTTR_REGISTRATION
{

// base

rttr::registration::class_<geolab::Node>("geolab::node")
.property("name", &geolab::Node::GetName, &geolab::Node::SetName)
(
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Name"))
)
;

#define EXE_FILEPATH "geolab/node_rttr_gen.h"
#include "geolab/node_regist_cfg.h"
#undef EXE_FILEPATH

}

namespace geolab
{

void nodes_regist_rttr()
{
}

}