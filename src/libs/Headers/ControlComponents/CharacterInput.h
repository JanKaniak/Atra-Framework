#pragma once
#include "ControlComponent.h"
#include "imgui.h"
#include <iostream>
#include <tuple>
#include <variant>

class CharTextField : public ControlComponentCharText<EditTypeCharText::TEXT>
{
public:
    CharTextField()
    {
        minimumWidth_ = 100;
    }

    void draw(std::vector<Message> &messageHistory) override
    {
        ImGui::PushItemWidth(40);
        ImGui::InputText(std::format("##{}", attribute_->getName()).c_str(), value_, 2, ImGuiInputTextFlags_CharsNoBlank);
        ImVec2 tmpControlTypeDimensions = ImGui::GetItemRectSize();
        ImGui::PopItemWidth();
        if (ImGui::IsItemDeactivatedAfterEdit())
        {
            if (!attribute_->setValue(value_[0]))
            {
                value_[0] = attribute_->getValue();
            }
        }
        ImGui::SameLine();
        if (ImGui::BeginChild("##Values", ImVec2(0, 0), ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY))
        {
            ImGui::Text("Symbol: %c", value_[0]);
            ImGui::EndChild();
        }
        ImVec2 tmpDimensions = ImGui::GetItemRectSize();
        dimensions_.x = tmpControlTypeDimensions.x + (tmpDimensions.x * 1.2f);
        dimensions_.y = tmpDimensions.y + (tmpDimensions.y * 1.2f);
    }
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<CharTextField>(*this); };
};

class StringTextField : public ControlComponentString<EditTypeString::TEXT>
{
public:
    StringTextField()
    {
        minimumWidth_ = 100;
        maximumWidth_ = 200;
    }

    void draw(std::vector<Message> &messageHistory) override
    {
        if ((maximum_ * 10) <= maximumWidth_ && ((maximum_ * 10)) >= minimumWidth_)
        {
            ImGui::PushItemWidth((maximum_ * 10));
        }
        else
        {
            ImGui::PushItemWidth(minimumWidth_);
        }
        ImGui::InputText(std::format("##{}", attribute_->getName()).c_str(), buffer, maximum_, ImGuiInputTextFlags_CharsNoBlank);
        dimensions_ = ImGui::GetItemRectSize();
        ImGui::PopItemWidth();
        if (ImGui::IsItemDeactivatedAfterEdit())
        {
            if (!attribute_->setValue(buffer))
            {
                if (sizeof(buffer) < attribute_->getValue().length())
                {
                    updateLimitValues();
                }
                std::string_view tmpValue = attribute_->getValue();
                for (int i = 0; i < maximum_ && i < tmpValue.length(); ++i)
                {
                    buffer[i] = tmpValue.at(i);
                }
            }
        }
    }
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<StringTextField>(*this); };
};