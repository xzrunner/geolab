#pragma once

#include <ee0/typedef.h>

#include <dag/Graph.h>
#include <gh/ParamType.h>

namespace ghv
{

class PreviewBuilder
{
public:
    PreviewBuilder(const ee0::SubjectMgrPtr& sub_mgr,
        const dag::Graph<gh::ParamType>& eval);

    void Build();

private:
    ee0::SubjectMgrPtr m_sub_mgr;

    const dag::Graph<gh::ParamType>& m_eval;

}; // PreviewBuilder

}