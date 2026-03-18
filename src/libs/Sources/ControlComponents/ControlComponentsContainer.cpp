#include "ControlComponentsContainer.h"
#include "AttributesContainer.h"

std::string ControlComponentsContainer::getControlTypeByAttributeName(std::string attributeName)
{
    for (auto &component : components_)
    {
        if (!component->getType(attributeName).empty())
        {
            return component->getType(attributeName);
        }
    }
    return "";
}

bool ControlComponentsContainer::existControlType(std::string attributeName)
{
    for (auto &component : components_)
    {
        if (component->sameName(attributeName))
        {
            return true;
        }
    }
    return false;
}

int ControlComponentsContainer::positionOfComponentByAttributeName(std::string attributeName)
{
    for (int i = 0; i < components_.size(); ++i)
    {
        if (components_.at(i)->sameName(attributeName))
        {
            return i;
        }
    }
    return -1;
}

void ControlComponentsContainer::addControl(std::unique_ptr<ControlComponent> control, Attribute *attribute)
{
    if (control != nullptr)
    {
        components_.push_back(std::move(control));
    }

    if (attribute != nullptr)
    {
        components_.at(components_.size() - 1)->setAttribute(attribute);
    }
}
void ControlComponentsContainer::addControl(int position, std::unique_ptr<ControlComponent> control, Attribute *attribute)
{
    if (position < 0)
    {
        return;
    }
    if (position < components_.size())
    {
        components_.emplace(components_.begin() + position, std::move(control));
    }
    else
    {
        components_.emplace_back(std::move(control));
    }

    if (attribute != nullptr)
    {
        components_.at(components_.size() - 1)->setAttribute(attribute);
    }
}

bool ControlComponentsContainer::deleteControlComponent(Attribute *attribute)
{
    for (auto it = components_.begin(); it != components_.end(); ++it)
    {
        if (it->get()->getAttribute(attribute->getName()) != nullptr)
        {
            components_.erase(it);
            return true;
        }
    }
    return false;
}

void ControlComponentsContainer::deleteAttribute(Attribute *attribute, AttributesContainer *attributesContainer, std::vector<Message> &messageHistory)
{
    deleteControlComponent(attribute);
    if (!attributesContainer->deleteAttribute(attribute))
    {
        messageHistory.emplace_back(Message("Attribute does not exist!"));
    }
    else
    {

        messageHistory.emplace_back(Message("Attribute was deleted!"));
    }
}

void ControlComponentsContainer::draw(std::vector<Message> &messageHistory)
{

    static bool drawed = false;
    static Attribute *chosenAttribute;
    static float firstColumnWidth = ImGui::CalcTextSize("Attribute name").x;
    static float secondColumnWidth = (ImGui::CalcTextSize("Input").x * 1.5f);
    static float thirdColumnWidth = ImGui::CalcTextSize("Attribute type").x;
    static float fourthColumnWidth = ImGui::CalcTextSize("Edit button").x;
    static float fifthColumnWidth = ImGui::CalcTextSize("Delete button").x;
    static float width = firstColumnWidth + secondColumnWidth + thirdColumnWidth + fourthColumnWidth + fifthColumnWidth;
    for (int i = 0; i < components_.size(); ++i)
    {
        if (components_.at(i) == nullptr)
        {
            continue;
        }
        if (ImGui::BeginTable("Attributes", 5, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_SizingFixedFit, ImVec2(width, 0)))
        {

            /*ImGui::TableSetupScrollFreeze(3,0);*/
            ImGui::TableSetupColumn("Attribute name", ImGuiTableColumnFlags_WidthFixed, firstColumnWidth);
            ImGui::TableSetupColumn("Input", ImGuiTableColumnFlags_WidthFixed, secondColumnWidth);
            ImGui::TableSetupColumn("Attribute type", ImGuiTableColumnFlags_WidthFixed, thirdColumnWidth);
            ImGui::TableSetupColumn("Edit button", ImGuiTableColumnFlags_WidthFixed, fourthColumnWidth);
            ImGui::TableSetupColumn("Delete button", ImGuiTableColumnFlags_WidthFixed, fifthColumnWidth);
            ImGui::TableHeadersRow();
            ImGui::TableNextColumn();
            ImGui::Text("%s", components_.at(i)->getName().c_str());
            if (ImGui::CalcTextSize(components_.at(i)->getName().c_str()).x > ImGui::CalcTextSize("Attribute name").x)
            {
                firstColumnWidth = ImGui::CalcTextSize(components_.at(i)->getName().c_str()).x;
            }
            else
            {
                firstColumnWidth = ImGui::CalcTextSize("Attribute name").x;
            }
            ImGui::TableNextColumn();
            components_.at(i)->draw(messageHistory);
            if (ImGui::GetItemRectSize().x > 100)
            {
                secondColumnWidth = ImGui::GetItemRectSize().x;
            }
            else
            {
                secondColumnWidth = (ImGui::CalcTextSize("Input").x * 1.5f);
            }
            ImGui::TableNextColumn();
            ImGui::Text("%s", AttributeTypeConverter::EnumToString(components_.at(i)->getAttribute(components_.at(i)->getName())->getType()).data());
            if (ImGui::CalcTextSize(AttributeTypeConverter::EnumToString(components_.at(i)->getAttribute(components_.at(i)->getName())->getType()).data()).x > ImGui::CalcTextSize("Attribute type").x)
            {
                thirdColumnWidth = ImGui::CalcTextSize(AttributeTypeConverter::EnumToString(components_.at(i)->getAttribute(components_.at(i)->getName())->getType()).data()).x;
            }
            else
            {
                thirdColumnWidth = ImGui::CalcTextSize("Attribute type").x;
            }
            ImGui::TableNextColumn();
            if (ImGui::Button("Edit", ImVec2(0, 30)))
            {
                drawed = true;
                chosenAttribute = components_.at(i)->getAttribute(components_.at(i)->getName());
            }
            if (ImGui::GetColumnWidth(-1) > 100)
            {
                fourthColumnWidth = ImGui::GetColumnWidth(-1);
            }
            else
            {
                fourthColumnWidth = ImGui::CalcTextSize("Edit button").x;
            }
            ImGui::TableNextColumn();
            if (ImGui::Button("Delete", ImVec2(0, 30)))
            {
                deleteAttribute(components_.at(i)->getAttribute(components_.at(i)->getName()), attributesContainer_, messageHistory);
            }
            if (ImGui::GetColumnWidth(-1) > 100)
            {
                fifthColumnWidth = ImGui::GetColumnWidth(-1);
            }
            else
            {
                fifthColumnWidth = ImGui::CalcTextSize("Delete button").x;
            }
            width = firstColumnWidth + secondColumnWidth + thirdColumnWidth + fourthColumnWidth + fifthColumnWidth;
            ImGui::EndTable();
        }
    }

    if (drawed)
    {
        ImGui::OpenPopup("Edit window");
        drawed = false;
    }

    static ControlComponent *component;
    static char editBuffer[40] = "";
    if (ImGui::BeginPopup("Edit window"))
    {
        static bool exist;
        static bool changingLimits = false;
        if (component == nullptr)
        {
            component = getControlComponentByAttribute(chosenAttribute);
        }
        if (editBuffer[0] == '\0')
        {
            strcpy(editBuffer, chosenAttribute->getName().c_str());
        }
        ImGui::InputText("Attribute name", editBuffer, sizeof(editBuffer));
        if (exist)
        {
            ImGui::Text("%s", "Attribute with this name already exists!");
        }
        ImGui::Text("Attribute type: %s", AttributeTypeConverter::EnumToString(chosenAttribute->getType()).data());

        if (ImGui::Button("Save", ImVec2(0, 30)))
        {
            if (attributesContainer_->giveAttributeByName(chosenAttribute->getName()) == chosenAttribute)
            {
                exist = false;
            }
            else
            {
                exist = (attributesContainer_->giveAttributeByName(editBuffer) == nullptr) ? false : true;
            }

            if (!exist)
            {
                exist = false;
                attributesContainer_->giveAttributeByName(chosenAttribute->getName())->getDescription()->setName(editBuffer);
                component = nullptr;
                ImGui::CloseCurrentPopup();
            }
            else
            {
                exist = true;
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Edit description"))
        {
            changingLimits = true;
        }
        ImGui::SameLine();
        if (changingLimits)
        {
            changingLimits = chosenAttribute->getDescription()->drawInputForChangingLimits(messageHistory);
        }
        if (ImGui::Button("Close", ImVec2(0, 30)))
        {
            component = nullptr;
            ImGui::CloseCurrentPopup();
            std::memset(editBuffer, 0, sizeof(editBuffer[0]));
        }
        else
        {
            if (component != nullptr)
            {
                component->updateLimitValues();
            }
        }
        ImGui::EndPopup();
    }

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsPopupOpen("Edit window"))
    {
        component = nullptr;
        std::memset(editBuffer, 0, sizeof(editBuffer[0]));
    }
}
