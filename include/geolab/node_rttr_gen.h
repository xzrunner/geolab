#define XSTR(s) STR(s)
#define STR(s) #s

#ifndef PARM_NODE_CLASS
#error "You must define PARM_NODE_CLASS macro before include this file"
#endif

#ifndef PARM_NODE_NAME
#error "You must define PARM_NODE_NAME macro before include this file"
#endif

#ifndef PARM_FILEPATH
#define PARM_FILEPATH geograph/component/##PARM_NODE_CLASS##.parm.h
#endif

#define RTTR_NAME geolab::##PARM_NODE_NAME

rttr::registration::class_<geolab::node::PARM_NODE_CLASS>(XSTR(RTTR_NAME))
.constructor<>()

#define PARAM_INFO(id, type, name, member, default_val)        \
.property(#name, &geolab::node::##PARM_NODE_CLASS::member)      \
(                                                              \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo(#id)) \
)
#include XSTR(PARM_FILEPATH)
#undef  PARAM_INFO

;

#undef PARM_NODE_NAME
#undef PARM_NODE_CLASS
#undef PARM_FILEPATH