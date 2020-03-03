#pragma once

#include "geolab/Node.h"

namespace geolab
{

void nodes_regist_rttr();

namespace node
{

#define EXE_FILEPATH "geolab/node_def_gen.h"
#include "geolab/node_regist_cfg.h"
#undef EXE_FILEPATH

}

}