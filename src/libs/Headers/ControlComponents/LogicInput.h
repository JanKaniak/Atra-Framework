#pragma once
#include "ControlComponent.h"
#include <iostream>
#include <variant>
#include <format>

/// Checkbox control for boolean attributes.
///
/// Displays a standard ImGui checkbox bound to an `AttributeBool`.
class CheckBox : public ControlComponentBool<EditTypeLogic::CHECKBOX>
{
public:
    CheckBox() {
        minimumWidth_ = 100;
    };

    /// Render the checkbox and update attribute state when toggled.
    void draw(std::vector<Message> &messageHistory) override {
        if (ImGui::Checkbox(std::format("##{}",getName()).c_str(),&value_)) {
            attribute_->setValue(value_);
        }
        dimensions_ = ImGui::GetItemRectSize();
    }

    /// Clone a new `CheckBox` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<CheckBox>(*this); };
};

/// Button control for boolean attributes.
///
/// Uses a colored push button to toggle the bound `AttributeBool` value.
class LogicButton : public ControlComponentBool<EditTypeLogic::BUTTON>
{
public:
    LogicButton() {
        minimumWidth_ = 100;
    };

    /// Render a toggle button that updates the boolean attribute.
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