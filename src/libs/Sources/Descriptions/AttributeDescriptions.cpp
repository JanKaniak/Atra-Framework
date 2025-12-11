#include "AttributeDescriptions.h"

AttributeDescriptions::AttributeDescriptions()
{
    descFactory_.registerPrototype<AttributeDescription_int>();
    // descFactory_.registerPrototype<AtributeDescription_double>();
    // descFactory_.registerPrototype<AtributeDescription_char>();
}

void AttributeDescriptions::addDescription(std::string agentName, std::string attributeName, AttributeType type, AttributeTypeVariant minimum, AttributeTypeVariant maximum)
{
    attributeDescs_.push_back(descFactory_.createDesc(type));
    getLast()->setName(attributeName);
    getLast()->setAgent(agentName);
    getLast()->setLimit(minimum, maximum);
}

bool AttributeDescriptions::addDescriptions(AttributeType type, nlohmann::json &json, std::string agentName, std::string &outputMessage)
{
    for (auto &it : json)
    {
        AttributeDescription* desc = getDescription(it["Attribute name"].get<std::string>(), agentName);
        if (desc != nullptr)
        {
            attributeDescs_.clear();
            outputMessage = "Attribute already exists!";
            return false;
        }
        attributeDescs_.push_back(descFactory_.createDesc(type));
        desc = getLast();
        desc->setAgent(agentName);
        if (!desc->jsonParse(it, outputMessage)) {
            attributeDescs_.clear();
            return false;
        }
    }
    return true;
}

AttributeDescription *AttributeDescriptions::getDescription(std::string name, std::string agentName)
{
    for (auto &desc : attributeDescs_)
    {
        if (desc->getName().compare(name) == 0 && desc->getAgent().compare(agentName) == 0)
        {
            return desc.get();
        }
    }
    return nullptr;
}

bool AttributeDescriptions::deleteDescription(AttributeDescription *description)
{
    for (int i = 0; i < attributeDescs_.size(); i++)
    {
        if (attributeDescs_.at(i).get() == description)
        {
            attributeDescs_.erase(attributeDescs_.begin() + i);
            return true;
        }
    }
    return false;
}