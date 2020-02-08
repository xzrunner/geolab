#pragma once

#include "ghv/Node.h"

namespace ghv
{

void nodes_regist_rttr();

namespace node
{

#define EXE_FILEPATH "ghv/node_def_gen.h"
#include "ghv/node_regist_cfg.h"
#undef EXE_FILEPATH

}

}