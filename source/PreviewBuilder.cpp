#include "ghv/PreviewBuilder.h"

#include <ee0/SubjectMgr.h>
#include <ee0/MessageID.h>
#include <ee0/MsgHelper.h>

#include <gh/Evaluator.h>
#include <gh/ParamImpl.h>
#include <gh/component/Line.h>
#include <ns/NodeFactory.h>
#include <node0/SceneNode.h>
#include <node3/CompShape.h>
#include <geoshape/Line3D.h>

namespace ghv
{

PreviewBuilder::PreviewBuilder(const ee0::SubjectMgrPtr& sub_mgr, const gh::Evaluator& eval)
    : m_sub_mgr(sub_mgr)
    , m_eval(eval)
{
}

void PreviewBuilder::Build()
{
    m_sub_mgr->NotifyObservers(ee0::MSG_SCENE_NODE_CLEAR);
    auto& comps = m_eval.GetAllComps();
    for (auto& pair : comps)
    {
        auto& comp = pair.second;

        auto type = comp->get_type();
        if (type == rttr::type::get<gh::comp::Line>())
        {
            auto param = comp->GetValue(static_cast<size_t>(gh::comp::Line::OutputID::L));
            assert(param && param->Type() == gh::ParamType::Line);
            auto line_param = std::static_pointer_cast<gh::LineParam>(param);
            auto& lines = line_param->GetLines();

            std::vector<std::shared_ptr<gs::Shape3D>> shapes;
            for (auto& line : lines) {
                shapes.push_back(std::make_shared<gs::Line3D>(
                    line.begin, line.end
                ));
            }
            auto node = ns::NodeFactory::Create3D();
            auto& cshape = node->AddUniqueComp<n3::CompShape>();
            cshape.SetShapes(shapes);
            ee0::MsgHelper::InsertNode(*m_sub_mgr, node);
        }
    }
}

}