#pragma once

#include "geolab/PreviewBuilder.h"

#include <ee0/typedef.h>
#include <blueprint/typedef.h>

#include <dag/Graph.h>
#include <geograph/ParamType.h>
#include <geograph/typedef.h>
#include <node0/typedef.h>

#include <boost/noncopyable.hpp>

#include <vector>
#include <unordered_map>

namespace bp { class Connecting; }

namespace geolab
{

class Evaluator : boost::noncopyable
{
public:
    Evaluator(const ee0::SubjectMgrPtr& sub_mgr);

    // update nodes
    void OnAddNode(const bp::Node& node, const n0::SceneNodePtr& snode,
        bool need_update = true);
    void OnRemoveNode(const bp::Node& node);
    void OnClearAllNodes();

    // update node prop
    void OnNodePropChanged(const bp::NodePtr& node);

    // update node conn
    void OnConnected(const bp::Connecting& conn);
    void OnDisconnecting(const bp::Connecting& conn);
    void OnRebuildConnection();

    auto& GetEval() const { return m_eval; }

    geograph::CompPtr QueryBackNode(const bp::Node& front_node) const;

private:
    void Update();

private:
    dag::Graph<geograph::ParamType> m_eval;

    PreviewBuilder m_preview_builder;

    std::unordered_map<const bp::Node*, geograph::CompPtr> m_front2back;

}; // Evaluator

}