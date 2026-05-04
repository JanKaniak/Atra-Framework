#pragma once
#include "ControlComponent.h"
#include <iostream>
#include <variant>
#include <format>

/// Tree-based control component for editing nested cluster attributes.
///
/// This component renders a hierarchical view for an `AttributeCluster`
/// using the cluster control type `TREE`.
class Tree : public ControlComponentCluster<EditTypeCluster::TREE> {
public:
    /// Default construct a tree cluster control.
    Tree();

    /// Render the cluster tree UI and propagate nested attribute updates.
    void draw(std::vector<Message> &messageHistory) override;

    /// Clone a new `Tree` component.
    std::unique_ptr<ControlComponent> clone() { return std::make_unique<Tree>(*this); }
};