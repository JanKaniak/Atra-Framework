#pragma once
#include "ControlComponent.h"
#include "imgui.h"
#include <iostream>
#include <tuple>
#include <variant>



class TextField : public ControlComponentChar<EditTypeChar::TEXT> {
    public:
        TextField() {
            minimumWidth_ = 100;
        }

        void draw(std::vector<Message> &messageHistory) override {
            ImGui::InputText(attributechar_->getName().c_str(),&value_,sizeof(value_));
        }
        std::unique_ptr<ControlComponent> clone() override { return std::make_unique<TextField>(*this); };

};