#pragma once
#include "ControlComponent.h"
#include <iostream>
#include <variant>
#include <format>

class CheckBox : public ControlComponentBool<EditTypeLogic::CHECKBOX>
{

private:
public:
    CheckBox() {
        minimumWidth_ = 100;
    };
    void draw(std::vector<Message> &messageHistory) override {
        if (ImGui::Checkbox(std::format("##{}",getName()).c_str(),&value_)) {
            attribute_->setValue(value_);
        }
        dimensions_ = ImGui::GetItemRectSize();
    }
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<CheckBox>(*this); };
};

class LogicButton : public ControlComponentBool<EditTypeLogic::BUTTON>
{

private:
public:
    LogicButton() {
        minimumWidth_ = 100;
    };
    void draw(std::vector<Message> &messageHistory) override {
        ImVec4 color;
        if (value_) {
            color = {0,1,0,1};
        } else {
            color = {1,0,0,1};
        }
        
        ImGui::PushStyleColor(ImGuiCol_Button,color);
        if (ImGui::Button(std::format("##{}",getName()).c_str(),ImVec2(50,30))) {
            value_ = !value_;
            attribute_->setValue(value_);
        }
        dimensions_ = ImGui::GetItemRectSize();
        ImGui::PopStyleColor();
    }
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<LogicButton>(*this); };
};