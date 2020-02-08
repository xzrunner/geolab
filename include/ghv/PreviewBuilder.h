#pragma once

#include <ee0/typedef.h>

namespace gh { class Evaluator; }

namespace ghv
{

class PreviewBuilder
{
public:
    PreviewBuilder(const ee0::SubjectMgrPtr& sub_mgr,
        const gh::Evaluator& eval);

    void Build();

private:
    ee0::SubjectMgrPtr m_sub_mgr;

    const gh::Evaluator& m_eval;

}; // PreviewBuilder

}