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
    void draw() override {
        if (ImGui::Checkbox(std::format("##{}",getName()).c_str(),&value_)) {
            attributebool_->setValue(value_);
        }
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
    void draw() override {
        ImVec4 color;
        if (value_) {
            color = {0,1,0,1};
        } else {
            color = {1,0,0,1};
        }
        
        if (ImGui::ColorButton(std::format("##{}",getName()).c_str(),color)) {
            value_ = !value_;
            attributebool_->setValue(value_);
        }
    }
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<LogicButton>(*this); };
};