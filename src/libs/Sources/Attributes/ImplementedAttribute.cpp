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

bool AttributeCharText::saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
{
    json.push_back(nlohmann::ordered_json::object_t::value_type("Attribute name", getName()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Minimum", getMinimum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Maximum", getMaximum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Value", (char)getValue()));
    return true;
}

bool AttributeBool::saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
{
    json.push_back(nlohmann::ordered_json::object_t::value_type("Attribute name", getName()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Value", getValue()));
    return true;
}

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

bool AttributeString::saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
{
    json.push_back(nlohmann::ordered_json::object_t::value_type("Attribute name", getName()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Minimum", getMinimum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Maximum", getMaximum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Value", getValue()));
    return true;
}

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
    
    ImGui::TableNextColumn();
    ImGui::Text("%s", desc_->getName().c_str());
    ImGui::TableNextColumn();
    ImGui::Text("%s", AttributeTypeConverter::EnumToString(desc_->getType()).data());
    ImGui::TableNextColumn();
    Factory *factory = config->getFactory(desc_->getType());
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

void AttributeCharText::controlOptions(int position, ControlComponentsContainer *components, Config *config, std::vector<Message> &messagesHistory)
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
    Factory *factory = config->getFactory(desc_->getType());
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


void AttributeBool::controlOptions(int position, ControlComponentsContainer *components, Config *config, std::vector<Message> &messagesHistory)
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
    Factory *factory = config->getFactory(desc_->getType());
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

void AttributeCluster::controlOptions(int position, ControlComponentsContainer *components, Config *config, std::vector<Message> &messagesHistory)
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
    Factory *factory = config->getFactory(desc_->getType());
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


void AttributeString::controlOptions(int position, ControlComponentsContainer *components, Config *config, std::vector<Message> &messagesHistory)
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
    Factory *factory = config->getFactory(desc_->getType());
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