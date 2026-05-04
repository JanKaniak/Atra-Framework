#include "ImplementedAttribute.h"
#include "AttributesContainer.h"
#include "Factory.h"
#include "ControlComponentsContainer.h"

/// Virtual base destructor for all attribute types.
Attribute::~Attribute() {}

/// Serialize integer attribute metadata and current value.
///
/// This writes the attribute name, bounds, and active value into JSON.
template <typename TypeT, typename AttributeDescriptionT>
bool IntegerNumberBaseAttributeClass<TypeT, AttributeDescriptionT>::saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
{
    json.push_back(nlohmann::ordered_json::object_t::value_type("Attribute name", getName()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Minimum", getMinimum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Maximum", getMaximum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Value", getValue()));
    return true;
}

/// Serialize decimal attribute metadata and current value.
///
/// Writes the attribute name, bounds, and current numeric value into JSON.
template <typename TypeT, typename AttributeDescriptionT>
bool DecimalNumberBaseAttributeClass<TypeT, AttributeDescriptionT>::saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
{
    json.push_back(nlohmann::ordered_json::object_t::value_type("Attribute name", getName()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Minimum", getMinimum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Maximum", getMaximum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Value", getValue()));
    return true;
}


/// Serialize a char-text attribute into JSON.
///
/// Stores the name, bounds, and the current character value.
bool AttributeCharText::saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
{
    json.push_back(nlohmann::ordered_json::object_t::value_type("Attribute name", getName()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Minimum", getMinimum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Maximum", getMaximum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Value", (char)getValue()));
    return true;
}

/// Serialize a boolean attribute into JSON.
///
/// Only the attribute name and current boolean state are saved.
bool AttributeBool::saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
{
    json.push_back(nlohmann::ordered_json::object_t::value_type("Attribute name", getName()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Value", getValue()));
    return true;
}

/// Serialize a nested cluster attribute into JSON.
///
/// This creates a JSON array of contained attributes and delegates serialization to each child.
bool AttributeCluster::saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
{
    json.push_back(nlohmann::ordered_json::object_t::value_type("Attribute name", getName()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Attribute descriptions", nlohmann::ordered_json::array()));
    if (json.find("Attribute descriptions") == json.end())
    {
        messagesHistory.emplace_back("There has been an error while saving attribute to file!");
        return false;
    }
    for (int i = 0; i < value_->getSize(); ++i)
    {
        json.find("Attribute descriptions").value().push_back(nlohmann::ordered_json::object());
        json.find("Attribute descriptions").value().at(json.find("Attribute descriptions").value().size() - 1)[AttributeTypeConverter::EnumToFileString(value_->giveAttribute(i)->getType())] = nlohmann::ordered_json::array();
        auto jsonObject = json.find("Attribute descriptions").value().at(json.find("Attribute descriptions").value().size() - 1).find(AttributeTypeConverter::EnumToFileString(value_->giveAttribute(i)->getType()));
        jsonObject.value().push_back(nlohmann::ordered_json::object());
        value_->giveAttribute(i)->saveToJson(jsonObject.value()[jsonObject.value().size() - 1], messagesHistory);
    }
    return true;
}

/// Serialize a string attribute into JSON.
///
/// Writes the attribute name, length bounds, and the current string value.
bool AttributeString::saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
{
    json.push_back(nlohmann::ordered_json::object_t::value_type("Attribute name", getName()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Minimum", getMinimum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Maximum", getMaximum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Value", getValue()));
    return true;
}

/// Create an empty cluster attribute holding a nested container.
AttributeCluster::AttributeCluster()
{
    value_ = std::make_unique<AttributesContainer>();
}

/// Copy constructor allocates a fresh nested container for the cloned cluster.
AttributeCluster::AttributeCluster(const AttributeCluster &attributeCluster)
{
    value_ = std::make_unique<AttributesContainer>();
}

/// Assign the cluster description and initialize contained attributes.
void AttributeCluster::setDescription(AttributeDescription *desc, std::vector<Message> &messagesHistory)
{
    if (dynamic_cast<AttributeDescriptionCluster *>(desc))
    {
        desc_ = dynamic_cast<AttributeDescriptionCluster *>(desc);
        value_->changeDescriptionContainer(desc_->getDescription());
        value_->createAttributes(messagesHistory);
    }
}

/// Build ImGui controls for an integer attribute.
///
/// This allows the user to choose a control type and displays the attribute metadata.
template <typename TypeT, typename AttributeDescriptionT>
void IntegerNumberBaseAttributeClass<TypeT, AttributeDescriptionT>::controlOptions(int position, ControlComponentsContainer *components, ControlComponentsFactoriesContainer *controlComponentsFactories, std::vector<Message> &messagesHistory)
{
    std::string controlType;
    if (controlType.empty())
    {
        controlType = components->getControlTypeByAttributeName(desc_->getName());
    }
    
    ImGui::TableNextColumn();
    ImGui::Text("%s", desc_->getName().c_str());
    ImGui::TableNextColumn();
    ImGui::Text("%s", AttributeTypeConverter::EnumToString(desc_->getType()).data());
    ImGui::TableNextColumn();
    Factory *factory = controlComponentsFactories->getFactory(desc_->getType());
    if (ImGui::BeginCombo(std::format("##Control Type##{}", std::format("{}{}", desc_->getName(), desc_->getTypeString())).c_str(), controlType.c_str()))
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
    
}

/// Build ImGui controls for a decimal attribute.
///
/// Displays the attribute label and lets the user select a control type for editing.
template <typename TypeT, typename AttributeDescriptionT>
void DecimalNumberBaseAttributeClass<TypeT, AttributeDescriptionT>::controlOptions(int position, ControlComponentsContainer *components, ControlComponentsFactoriesContainer *controlComponentsFactories, std::vector<Message> &messagesHistory)
{
    std::string controlType;
    if (controlType.empty())
    {
        controlType = components->getControlTypeByAttributeName(desc_->getName());
    }
    
    ImGui::TableNextColumn();
    ImGui::Text("%s", desc_->getName().c_str());
    ImGui::TableNextColumn();
    ImGui::Text("%s", AttributeTypeConverter::EnumToString(desc_->getType()).data());
    ImGui::TableNextColumn();
    Factory *factory = controlComponentsFactories->getFactory(desc_->getType());
    if (ImGui::BeginCombo(std::format("##Control Type##{}", std::format("{}{}", desc_->getName(), desc_->getTypeString())).c_str(), controlType.c_str()))
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
    
}

/// Build ImGui controls for a character text attribute.
///
/// Uses description metadata to render the control selection UI.
void AttributeCharText::controlOptions(int position, ControlComponentsContainer *components, ControlComponentsFactoriesContainer *controlComponentsFactories, std::vector<Message> &messagesHistory)
{
    std::string controlType;
    if (controlType.empty())
    {
        controlType = components->getControlTypeByAttributeName(desc_->getName());
    }
    ImGui::TableNextColumn();
    ImGui::Text("%s", desc_->getName().c_str());
    ImGui::TableNextColumn();
    ImGui::Text("%s", AttributeTypeConverter::EnumToString(desc_->getType()).data());
    ImGui::TableNextColumn();
    Factory *factory = controlComponentsFactories->getFactory(desc_->getType());
    if (ImGui::BeginCombo(std::format("##Control Type##{}", std::format("{}{}", desc_->getName(), desc_->getTypeString())).c_str(), controlType.c_str()))
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
}


/// Build ImGui controls for a boolean attribute.
///
/// Presents the attribute name and lets the user choose an input component.
void AttributeBool::controlOptions(int position, ControlComponentsContainer *components, ControlComponentsFactoriesContainer *controlComponentsFactories, std::vector<Message> &messagesHistory)
{
    std::string controlType;
    if (controlType.empty())
    {
        controlType = components->getControlTypeByAttributeName(desc_->getName());
    }
    ImGui::TableNextColumn();
    ImGui::Text("%s", desc_->getName().c_str());
    ImGui::TableNextColumn();
    ImGui::Text("%s", AttributeTypeConverter::EnumToString(desc_->getType()).data());
    ImGui::TableNextColumn();
    Factory *factory = controlComponentsFactories->getFactory(desc_->getType());
    if (ImGui::BeginCombo(std::format("##Control Type##{}", std::format("{}{}", desc_->getName(), desc_->getTypeString())).c_str(), controlType.c_str()))
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
}

/// Build ImGui controls for a nested cluster attribute.
///
/// Exposes the cluster container and propagates control type selection to child attributes.
void AttributeCluster::controlOptions(int position, ControlComponentsContainer *components, ControlComponentsFactoriesContainer *controlComponentsFactories, std::vector<Message> &messagesHistory)
{
    std::string controlType;
    if (controlType.empty())
    {
        controlType = components->getControlTypeByAttributeName(desc_->getName());
    }
    ImGui::TableNextColumn();
    ImGui::Text("%s", desc_->getName().c_str());
    ImGui::TableNextColumn();
    ImGui::Text("%s", AttributeTypeConverter::EnumToString(desc_->getType()).data());
    ImGui::TableNextColumn();
    Factory *factory = controlComponentsFactories->getFactory(desc_->getType());
    if (ImGui::BeginCombo(std::format("##Control Type##{}", std::format("{}{}", desc_->getName(), desc_->getTypeString())).c_str(), controlType.c_str()))
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

    for (int i = 0; i < components->getSize(); ++i)
    {
        if (components->getComponent(i)->getAttribute(desc_->getName()) == this)
        {

            value_->setControlTypes(components->getComponent(i)->getContainer(), messagesHistory);
            break;
        }
    }
}

/// Clone this cluster attribute, including its nested container state.
std::unique_ptr<Attribute> AttributeCluster::clone() { return std::make_unique<AttributeCluster>(*this); }

struct AutoRegisterClusterAttribute : public AutoRegisterAttribute<AttributeCluster, AttributeType::CLUSTER>
{
    inline static bool registerClusterAttribute = []()
    {
        AutoRegisterAttribute::autoRegisterAttribute;
    };
};

/// Destroy the cluster attribute and release its nested container.
AttributeCluster::~AttributeCluster()
{
    value_ = nullptr;
}

/// Access the nested attribute container for this cluster.
AttributesContainer *AttributeCluster::getAttributeContainer()
{
    return value_.get();
}

/// Build ImGui controls for a string attribute.
///
/// Displays the attribute name and lets the user choose the editor component.
void AttributeString::controlOptions(int position, ControlComponentsContainer *components, ControlComponentsFactoriesContainer *controlComponentsFactories, std::vector<Message> &messagesHistory)
{
    std::string controlType;
    if (controlType.empty())
    {
        controlType = components->getControlTypeByAttributeName(desc_->getName());
    }
    ImGui::TableNextColumn();
    ImGui::Text("%s", desc_->getName().c_str());
    ImGui::TableNextColumn();
    ImGui::Text("%s", AttributeTypeConverter::EnumToString(desc_->getType()).data());
    ImGui::TableNextColumn();
    Factory *factory = controlComponentsFactories->getFactory(desc_->getType());
    if (ImGui::BeginCombo(std::format("##Control Type##{}", std::format("{}{}", desc_->getName(), desc_->getTypeString())).c_str(), controlType.c_str()))
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
}