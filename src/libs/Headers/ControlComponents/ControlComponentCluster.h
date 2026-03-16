#pragma once
#include "ControlComponent.h"
#include <iostream>
#include <variant>
#include <format>

class Tree : public ControlComponentCluster<EditTypeCluster::TREE> {
    void draw(std::vector<Message> &messageHistory) override;
    std::unique_ptr<ControlComponent> clone() { return std::make_unique<Tree>(*this); }
};