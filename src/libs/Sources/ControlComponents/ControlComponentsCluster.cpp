#include "ControlComponent.h"
#include "ControlComponentsContainer.h"

void ControlComponentCluster::draw()
{

    if (ImGui::Button(std::format("Expand##{}", attributecluster_->getName()).c_str()))
    {
        ImGui::OpenPopup(std::format("Attributes##{}", attributecluster_->getName()).c_str());
    }

    
    ImGui::SetNextWindowSize(showAttributesWindowSize_);
    if (ImGui::BeginPopup(std::format("Attributes##{}",attributecluster_->getName()).c_str(), ImGuiWindowFlags_NoCollapse))
    {
        bool tableCreated = false;
        for (int i = 0; i < components_->getSize(); ++i)
        {
            if (components_->getComponent(i) == nullptr)
            {
                continue;
            }
            ImVec2 avaiableSpace = ImGui::GetContentRegionAvail();
            if (ImGui::BeginTable("Attributes", 5, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_ScrollX, ImVec2(0, ImGui::GetFrameHeight() + 5 * (ImGui::GetTextLineHeight() + ImGui::GetStyle().CellPadding.y * 1.5f))))
            {
                ImGui::TableSetupColumn("Attribute name", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("Input", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("Attribute type", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("EditButton", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("DeleteButton", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableHeadersRow();
                ImGui::TableNextColumn();
                ImGui::Text("%s", components_->getComponent(i)->getName().c_str());
                ImGui::TableNextColumn();
                components_->getComponent(i)->draw();
                ImGui::TableNextColumn();
                ImGui::Text("%s", AttributeTypeConverter::EnumToString(components_->getComponent(i)->getAttribute(components_->getComponent(i)->getName())->getType()).data());
                ImGui::TableNextColumn();
                if (ImGui::Button("Edit", ImVec2(0, 30)))
                {
                    drawed = true;
                    
                }
                ImGui::TableNextColumn();
                if (ImGui::Button("Delete", ImVec2(0, 30)))
                {
                    
                }
                ImGui::EndTable();
            }
        }
        ImGui::EndPopup();
    }
}

bool ControlComponentCluster::sameName(std::string name)
{
    if (attributecluster_->getName().compare(name) == 0)
    {
        return true;
    }
    return false;
}

std::string ControlComponentCluster::getType(std::string_view name)
{
    if (!name.empty() && sameName(name.data()))
    {
        return "DEFAULT";
    }
    return components_->getControlTypeByAttributeName(name.data());
}

void ControlComponentCluster::setAttribute(Attribute *attribute)
{
    if (dynamic_cast<AttributeCluster *>(attribute))
    {
        attributecluster_ = dynamic_cast<AttributeCluster *>(attribute);
        components_ = new ControlComponentsContainer();
    }
}

void ControlComponentCluster::updateLimitValues()
    {
        for (int i = 0; i < components_->getSize();++i) {
            components_->getComponent(i)->updateLimitValues();
        }
    }