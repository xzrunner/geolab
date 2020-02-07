#include "ghview/RegistNodes.h"

#include <ee0/ReflectPropTypes.h>

#include <js/RTTR.h>

RTTR_REGISTRATION
{

// base

rttr::registration::class_<ghv::Node>("ghv::node")
.property("name", &ghv::Node::GetName, &ghv::Node::SetName)
(
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Name"))
)
;

#define EXE_FILEPATH "ghview/node_rttr_gen.h"
#include "ghview/node_regist_cfg.h"
#undef EXE_FILEPATH

}

namespace ghv
{

void nodes_regist_rttr()
{
}

}