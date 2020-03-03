#include "geolab/PreviewBuilder.h"

#include <ee0/SubjectMgr.h>
#include <ee0/MessageID.h>
#include <ee0/MsgHelper.h>

#include <geograph/ParamImpl.h>
#include <geograph/component/Line.h>
#include <ns/NodeFactory.h>
#include <node0/SceneNode.h>
#include <node3/CompShape.h>
#include <geoshape/Line3D.h>

namespace geolab
{

PreviewBuilder::PreviewBuilder(const ee0::SubjectMgrPtr& sub_mgr,
                               const dag::Graph<geograph::ParamType>& eval)
    : m_sub_mgr(sub_mgr)
    , m_eval(eval)
{
}

void PreviewBuilder::Build()
{
    m_sub_mgr->NotifyObservers(ee0::MSG_SCENE_NODE_CLEAR);
    auto& comps = m_eval.GetAllNodes();
    for (auto& pair : comps)
    {
        auto& comp = pair.second;

        auto type = comp->get_type();
        if (type == rttr::type::get<geograph::comp::Line>())
        {
            auto param = std::static_pointer_cast<geograph::Component>(comp)->GetValue(static_cast<size_t>(geograph::comp::Line::OutputID::L));
            assert(param && param->Type() == geograph::ParamType::Line);
            auto line_param = std::static_pointer_cast<geograph::LineParam>(param);
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