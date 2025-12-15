#include "AttributeDescriptions.h"

AttributeDescriptions::AttributeDescriptions()
{
    descFactory_.registerPrototype<AttributeDescription_int>();
    descFactory_.registerPrototype<AttributeDescription_double>();
    // descFactory_.registerPrototype<AtributeDescription_char>();
}

/*void AttributeDescriptions::addDescription(std::string agentName, std::string attributeName, AttributeType type, AttributeTypeVariant minimum, AttributeTypeVariant maximum)/
{
    attributeDescs_.push_back(descFactory_.createDesc(type));
    getLast()->setName(attributeName);
    getLast()->setAgent(agentName);
    getLast()->setLimit(minimum, maximum);
}*/

bool AttributeDescriptions::addDescriptions(AttributeType type, nlohmann::ordered_json &json, std::string agentName, std::string &outputMessage)
{
    for (auto descIt = json.begin(); descIt != json.end(); descIt++)
    {
        AttributeDescription* desc = getDescription(descIt.value()["Attribute name"].get<std::string>(), agentName);
        if (desc != nullptr)
        {
            attributeDescs_.clear();
            outputMessage = "Attribute already exists!";
            return false;
        }
        attributeDescs_.push_back(descFactory_.createDesc(type));
        desc = getLast();
        desc->setAgent(agentName);
        if (!desc->jsonParse(descIt.value(), outputMessage)) {
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
    for (auto it = attributeDescs_.begin(); it != attributeDescs_.end(); it++)
    {
        if (it->get() == description)
        {
            attributeDescs_.erase(it);
            return true;
        }
    }
    return false;
}