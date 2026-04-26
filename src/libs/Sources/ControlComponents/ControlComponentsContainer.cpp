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
        updatedTable_ = true;
    }

    if (attribute != nullptr)
    {
        components_.at(components_.size() - 1)->setAttribute(attribute);
    }
}
void ControlComponentsContainer::addControl(int position, std::unique_ptr<ControlComponent> control, Attribute *attribute)
{
    if (position < 0 || control != nullptr)
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
    updatedTable_ = true;
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
            updatedTable_ = true;
            return true;
        }
    }
    return false;
}

bool ControlComponentsContainer::swapControlComponent(int position, std::unique_ptr<ControlComponent> control, Attribute *attribute)
{
    if (control == nullptr)
    {
        return false;
    }

    if (components_.empty() || position >= components_.size())
    {
        components_.emplace_back(std::move(control));
        components_.at(components_.size() - 1)->setAttribute(attribute);
        updatedTable_ = true;
        return true;
    }

    components_.at(position) = std::move(control);
    components_.at(position)->setAttribute(attribute);
    updatedTable_ = true;
    return true;
}

ControlComponent *ControlComponentsContainer::getControlComponentByAttribute(Attribute *attribute)
    {
        for (int i = 0; i < components_.size(); ++i)
        {
            if (components_.at(i)->getAttribute(attribute->getName()) != nullptr)
            {
                return components_.at(i).get();
            }
        }
        return nullptr;
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
        updatedTable_ = true;
    }
}

void ControlComponentsContainer::draw(std::vector<Message> &messageHistory)
{

    static bool drawed = false;
    static Attribute *chosenAttribute;
    static ImVec2 firstColumn = ImGui::CalcTextSize("Attribute name");
    static ImVec2 secondColumn = ImVec2((ImGui::CalcTextSize("Input").x * 1.5f), 0);
    static ImVec2 thirdColumn = ImGui::CalcTextSize("Attribute type");
    static ImVec2 fourthColumn = ImGui::CalcTextSize("Edit button");
    static ImVec2 fifthColumn = ImVec2(ImGui::CalcTextSize("Delete button").x * 1.5f, 0);

    ImGui::Text("%f", secondColumn.x);
    if (dimensions_.x < 0 && dimensions_.y < 0)
    {
        dimensions_.x = firstColumn.x + secondColumn.x + thirdColumn.x + fourthColumn.x + fifthColumn.x;
        dimensions_.y = firstColumn.y + secondColumn.y + thirdColumn.y + fourthColumn.y + fifthColumn.y;
    }
    if (ImGui::BeginTable("Attributes", 5, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersH | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoKeepColumnsVisible | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY, dimensions_))
    {
        float inputColumnsWidth[components_.size()];
        float columnHeight[components_.size()];
        ImGui::TableSetupColumn("Attribute name", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("Input", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("Attribute type", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("Edit button", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("Delete button", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableHeadersRow();
        for (int i = 0; i < components_.size(); ++i)
        {
            if (components_.at(i) == nullptr)
            {
                continue;
            }
            ImGui::TableNextColumn();
            ImGui::Text("%s", components_.at(i)->getName().c_str());
            if (ImGui::CalcTextSize(components_.at(i)->getName().c_str()).x > ImGui::CalcTextSize("Attribute name").x)
            {
                firstColumn = ImVec2((ImGui::CalcTextSize(components_.at(i)->getName().c_str()).x * 1.5f), 0);
            }
            else
            {
                firstColumn = ImGui::CalcTextSize("Attribute name");
            }
            ImGui::TableNextColumn();
            components_.at(i)->draw(messageHistory);
            inputColumnsWidth[i] = components_.at(i)->getDimensions().x;
            columnHeight[i] = components_.at(i)->getDimensions().y;
            ImGui::TableNextColumn();
            ImGui::Text("%s", AttributeTypeConverter::EnumToString(components_.at(i)->getAttribute(components_.at(i)->getName())->getType()).data());
            if (ImGui::CalcTextSize(AttributeTypeConverter::EnumToString(components_.at(i)->getAttribute(components_.at(i)->getName())->getType()).data()).x > ImGui::CalcTextSize("Attribute type").x)
            {
                thirdColumn = ImGui::CalcTextSize(AttributeTypeConverter::EnumToString(components_.at(i)->getAttribute(components_.at(i)->getName())->getType()).data());
            }
            else
            {
                thirdColumn = ImGui::CalcTextSize("Attribute type");
            }
            ImGui::TableNextColumn();
            if (ImGui::Button(std::format("Edit##{}", components_.at(i)->getAttribute(components_.at(i)->getName())->getDescription()->getID()).c_str(), ImVec2(65, 30)))
            {
                drawed = true;
                chosenAttribute = components_.at(i)->getAttribute(components_.at(i)->getName());
            }

            if (columnHeight[i] < ImGui::GetItemRectSize().y)
            {
                columnHeight[i] = ImGui::GetItemRectSize().y;
            }
            ImGui::TableNextColumn();
            if (ImGui::Button(std::format("Delete##{}", components_.at(i)->getAttribute(components_.at(i)->getName())->getDescription()->getID()).c_str(), ImVec2(65, 30)))
            {
                deleteAttribute(components_.at(i)->getAttribute(components_.at(i)->getName()), attributesContainer_, messageHistory);
            }
        }
        auto dimensionsX = *std::max_element(inputColumnsWidth, inputColumnsWidth + sizeof(inputColumnsWidth) / sizeof(inputColumnsWidth[0]));
        auto dimensionsY = *std::max_element(columnHeight, columnHeight + sizeof(columnHeight) / sizeof(columnHeight[0]));
        secondColumn = ImVec2(dimensionsX, dimensionsY);
        dimensions_.x = firstColumn.x + secondColumn.x + thirdColumn.x + fourthColumn.x + fifthColumn.x;
        dimensions_.y = firstColumn.y;
        for (int i = 0; i < components_.size(); ++i)
        {
            dimensions_.y += columnHeight[i];
        }
        dimensions_.y = dimensions_.y * 1.2f;
        ImGui::EndTable();
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

        if (ImGui::Button("Save", ImVec2(150, 30)))
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
        if (ImGui::Button("Edit description", ImVec2(150, 30)))
        {
            changingLimits = true;
        }
        ImGui::SameLine();
        if (changingLimits)
        {
            changingLimits = chosenAttribute->getDescription()->drawInputForChangingLimits(messageHistory);
            if (!changingLimits) {
                chosenAttribute->updateValue();
            }
        }
        if (ImGui::Button("Close", ImVec2(150, 30)))
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

void ControlComponentsContainer::deleteAllControlComponents(std::vector<Message> &messageHistory)
{
    if (components_.size() == 0)
    {
        return;
    }
    components_.clear();
    messageHistory.emplace_back("All control components were successfuly removed!");
}