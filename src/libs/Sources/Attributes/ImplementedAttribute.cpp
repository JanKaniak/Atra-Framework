#include "ImplementedAttribute.h"
#include "AttributesContainer.h"
#include "Factory.h"
#include "ControlComponentsContainer.h"

Attribute::~Attribute() {}

template <typename TypeT, typename AttributeDescriptionT>
bool IntegerNumberBaseAttributeClass<TypeT, AttributeDescriptionT>::saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
{
    json.push_back(nlohmann::ordered_json::object_t::value_type("Attribute name", getName()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Minimum", getMinimum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Maximum", getMaximum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Value", getValue()));
    return true;
}

bool AttributeBool::saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
{
    json.push_back(nlohmann::ordered_json::object_t::value_type("Attribute name", getName()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Value", getValue()));
    return true;
}

bool AttributeCluster::saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) { return false; }

AttributeCluster::AttributeCluster()
{
    value_ = std::make_unique<AttributesContainer>();
}

AttributeCluster::AttributeCluster(const AttributeCluster &attributeCluster)
{
    value_ = std::make_unique<AttributesContainer>();
}

void AttributeCluster::setDescription(AttributeDescription *desc, std::vector<Message> &messagesHistory)
{
    if (dynamic_cast<AttributeDescriptionCluster *>(desc))
    {
        desc_ = dynamic_cast<AttributeDescriptionCluster *>(desc);
        value_->changeDescriptionContainer(desc_->getDescription());
        value_->createAttributes(messagesHistory);
    }
}

template <typename TypeT, typename AttributeDescriptionT>
void IntegerNumberBaseAttributeClass<TypeT, AttributeDescriptionT>::controlOptions(int position, ControlComponentsContainer *components, Config *config, std::vector<Message> &messagesHistory)
{
    std::string controlType;
    if (controlType.empty())
    {
        controlType = components->getControlTypeByAttributeName(desc_->getName());
    }
    ImGuiChildFlags flags;
    bool empty;
    if (controlType.empty())
    {
        empty = true;
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1, 0, 0, 1));
        flags = ImGuiChildFlags_Borders | ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysUseWindowPadding;
    }
    else
    {
        empty = false;
        flags = ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysUseWindowPadding;
    }

    if (ImGui::BeginChild(std::format("Border##{}", desc_->getID()).c_str(), ImVec2(0, 0), flags))
    {
        ImGui::SameLine();
        ImGui::Text("%s", desc_->getName().c_str());
        ImGui::SameLine();
        ImGui::Text("%s", AttributeTypeConverter::EnumToString(desc_->getType()).data());
        ImGui::SameLine();
        Factory *factory = config->getFactory(desc_->getType());
        if (ImGui::BeginCombo(std::format("Control Type##{}", std::format("{}{}", desc_->getName(), desc_->getTypeString())).c_str(), controlType.c_str()))
        {
            for (int j = 0; j < factory->getNameOfControlTypesVector().size(); ++j)
            {
                bool selected = (controlType.compare(factory->getNameOfControlTypesVector().at(j)) == 0);
                if (ImGui::Selectable(factory->getNameOfControlTypesVector().at(j).c_str(), selected))
                {
                    controlType = factory->getNameOfControlTypesVector().at(j);
                    components->swapControlComponent(components->positionOfComponentByAttributeName(desc_->getName()), factory->createEdit(controlType), this);
                }
                if (selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
        }
        ImGui::EndChild();
        if (empty)
        {
            ImGui::PopStyleColor();
            ImGui::Dummy(ImVec2(100, 30));
        } else {
            ImGui::Dummy(ImVec2(100, 35));
        }
        
    }
}

void AttributeBool::controlOptions(int position, ControlComponentsContainer *components, Config *config, std::vector<Message> &messagesHistory)
{
    std::string controlType;
    if (controlType.empty())
    {
        controlType = components->getControlTypeByAttributeName(desc_->getName());
    }
    ImGuiChildFlags flags;
    bool empty;
    if (!components->existControlType(desc_->getName()))
    {
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1, 0, 0, 1));
        flags = ImGuiChildFlags_Borders | ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysUseWindowPadding;
        empty = true;
    }
    else
    {
        empty = false;
        flags = ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysUseWindowPadding;
    }

    if (ImGui::BeginChild(std::format("Border##{}", desc_->getID()).c_str(), ImVec2(0, 0), flags))
    {
        ImGui::SameLine();
        ImGui::Text("%s", desc_->getName().c_str());
        ImGui::SameLine();
        ImGui::Text("%s", AttributeTypeConverter::EnumToString(desc_->getType()).data());
        ImGui::SameLine();
        Factory *factory = config->getFactory(desc_->getType());
        if (ImGui::BeginCombo(std::format("Control Type##{}", desc_->getName()).c_str(), controlType.c_str()))
        {
            for (int j = 0; j < factory->getNameOfControlTypesVector().size(); ++j)
            {
                bool selected = (controlType.compare(factory->getNameOfControlTypesVector().at(j)) == 0);
                if (ImGui::Selectable(factory->getNameOfControlTypesVector().at(j).c_str(), selected))
                {
                    controlType = factory->getNameOfControlTypesVector().at(j);
                    components->swapControlComponent(position, factory->createEdit(controlType), this);
                }
                if (selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
        }
        ImGui::EndChild();
        if (empty)
        {
            ImGui::PopStyleColor();
        }
        ImGui::Dummy(ImVec2(30, 30));
    }
}

void AttributeCluster::controlOptions(int position, ControlComponentsContainer *components, Config *config, std::vector<Message> &messagesHistory)
{
    std::string controlType;
    if (controlType.empty())
    {
        controlType = components->getControlTypeByAttributeName(desc_->getName());
    }
    ImGuiChildFlags flags;
    bool empty;
    if (controlType.empty())
    {
        empty = true;
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1, 0, 0, 1));
        flags = ImGuiChildFlags_Borders | ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysUseWindowPadding;
    }
    else
    {
        empty = false;
        flags = ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysUseWindowPadding;
    }

    if (ImGui::BeginChild(std::format("Border##{}", desc_->getID()).c_str(), ImVec2(0, 0), flags))
    {
        ImGui::SameLine();
        ImGui::Text("%s", desc_->getName().c_str());
        ImGui::SameLine();
        ImGui::Text("%s", AttributeTypeConverter::EnumToString(desc_->getType()).data());
        ImGui::SameLine();
        Factory *factory = config->getFactory(desc_->getType());
        if (ImGui::BeginCombo(std::format("Control Type##{}", desc_->getID()).c_str(), controlType.c_str()))
        {
            for (int j = 0; j < factory->getNameOfControlTypesVector().size(); ++j)
            {
                bool selected = (controlType.compare(factory->getNameOfControlTypesVector().at(j)) == 0);
                if (ImGui::Selectable(factory->getNameOfControlTypesVector().at(j).c_str(), selected))
                {
                    controlType = factory->getNameOfControlTypesVector().at(j);
                    components->swapControlComponent(components->positionOfComponentByAttributeName(desc_->getName()), factory->createEdit(controlType), this);
                }
                if (selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
        }
        ImGui::EndChild();
        if (empty)
        {
            ImGui::PopStyleColor();
        }
        ImGui::Dummy(ImVec2(30, 30));
    }

    for (int i = 0; i < components->getSize(); ++i)
    {
        if (components->getComponent(i)->getAttribute(desc_->getName()) == this)
        {

            value_->setControlTypes(components->getComponent(i)->getContainer(), config, messagesHistory);
            break;
        }
    }
}

std::unique_ptr<Attribute> AttributeCluster::clone() { return std::make_unique<AttributeCluster>(*this); }

struct AutoRegisterClusterAttribute : public AutoRegisterAttribute<AttributeCluster, AttributeType::CLUSTER>
{
    inline static bool registerClusterAttribute = []()
    {
        AutoRegisterAttribute::autoRegisterAttribute;
    };
};

AttributeCluster::~AttributeCluster()
{
    value_ = nullptr;
}

AttributesContainer *AttributeCluster::getAttributeContainer()
{
    return value_.get();
}