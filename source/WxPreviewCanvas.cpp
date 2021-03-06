#include "geolab/WxPreviewCanvas.h"
#include "geolab/PreviewPage.h"
#include "geolab/Node.h"
#include "geolab/WxGraphPage.h"
#include "geolab/PreviewRender.h"

#include <ee0/WxStagePage.h>
#include <ee0/SubjectMgr.h>
#include <blueprint/Node.h>
#include <blueprint/CompNode.h>

#include <node0/SceneNode.h>
#include <unirender/RenderState.h>
#include <painting2/RenderSystem.h>
#include <painting3/MaterialMgr.h>
#include <painting3/Blackboard.h>
#include <painting3/WindowContext.h>
#include <painting3/PerspCam.h>
#include <node3/RenderSystem.h>

namespace
{

const float    NODE_RADIUS = 10;
const uint32_t LIGHT_SELECT_COLOR = 0x88000088;

}

namespace geolab
{

WxPreviewCanvas::WxPreviewCanvas(const ur::Device& dev, ee0::WxStagePage* stage,
                                 ECS_WORLD_PARAM const ee0::RenderContext& rc)
    : ee3::WxStageCanvas(dev, stage, ECS_WORLD_VAR &rc, nullptr, true)
{
}

void WxPreviewCanvas::DrawBackground3D() const
{
    ee3::WxStageCanvas::DrawBackgroundGrids(10.0f, 0.2f);
//    ee3::WxStageCanvas::DrawBackgroundCross();
}

void WxPreviewCanvas::DrawForeground3D() const
{
    pt0::RenderContext rc;
    rc.AddVar(
        pt3::MaterialMgr::PositionUniforms::light_pos.name,
        pt0::RenderVariant(sm::vec3(0, 2, -4))
    );
    if (m_camera->TypeID() == pt0::GetCamTypeID<pt3::PerspCam>())
    {
        auto persp = std::static_pointer_cast<pt3::PerspCam>(m_camera);
        rc.AddVar(
            pt3::MaterialMgr::PositionUniforms::cam_pos.name,
            pt0::RenderVariant(persp->GetPos())
        );
    }
    //auto& wc = pt3::Blackboard::Instance()->GetWindowContext();
    //assert(wc);
    //rc.AddVar(
    //    pt3::MaterialMgr::PosTransUniforms::view.name,
    //    pt0::RenderVariant(wc->GetViewMat())
    //);
    //rc.AddVar(
    //    pt3::MaterialMgr::PosTransUniforms::projection.name,
    //    pt0::RenderVariant(wc->GetProjMat())
    //);

    auto cam_mat = m_camera->GetProjectionMat() * m_camera->GetViewMat();
    PreviewRender pr(GetViewport(), cam_mat);

    m_stage->Traverse([&](const ee0::GameObj& obj)->bool {
        pr.DrawNode(m_dev, *GetRenderContext().ur_ctx, rc, *obj);
        return true;
    });

    ur::RenderState rs;
    pt2::RenderSystem::DrawPainter(m_dev, *GetRenderContext().ur_ctx, rs, pr.GetPainter());
}

void WxPreviewCanvas::DrawForeground2D() const
{
}

}
