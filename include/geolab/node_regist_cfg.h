#ifndef EXE_FILEPATH
#error "You must define EXE_FILEPATH macro before include this file"
#endif

// params

#define PARM_FILEPATH geograph/component/param/Point.parm.h
#define PARM_NODE_CLASS ParamPoint
#define PARM_NODE_NAME param_point
#include EXE_FILEPATH
#undef PARM_FILEPATH

// curve

#define PARM_NODE_CLASS Line
#define PARM_NODE_NAME line
#include EXE_FILEPATH
