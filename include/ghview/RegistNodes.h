#pragma once

#include "ghview/Node.h"

namespace ghv
{

void nodes_regist_rttr();

namespace node
{

#define EXE_FILEPATH "ghview/node_def_gen.h"
#include "ghview/node_regist_cfg.h"
#undef EXE_FILEPATH

}

}