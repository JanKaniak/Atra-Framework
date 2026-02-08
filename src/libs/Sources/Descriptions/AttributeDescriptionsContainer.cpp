#include "AttributeDescriptionsContainer.h"
#include <format>

AttributeDescriptionsContainer::AttributeDescriptionsContainer()
{
    descFactory_ = DescFactory::getInstance();
}

bool AttributeDescriptionsContainer::addDescriptions(AttributeType type, nlohmann::ordered_json &json, std::string &outputMessage)
{
    for (auto descIt = json.begin(); descIt != json.end(); ++descIt)
    {
        if (descIt.value().find("Attribute name") == descIt.value().end())
        {
            time_t now = time(NULL);
            struct tm *t = localtime(&now);
            char buffer[100];
            strftime(buffer, sizeof(buffer), "%H:%M:%S", t);
            outputMessage = std::format("{}   Incorrect json format!", buffer);
            return false;
        }
        AttributeDescription *desc = getDescription(descIt.value()["Attribute name"].get<std::string>());
        if (desc != nullptr)
        {
            attributeDescs_.clear();
            outputMessage = "Attribute already exists!";
            return false;
        }
        std::unique_ptr<AttributeDescription> tmpDescription = descFactory_->createDesc(type);
        if (tmpDescription == nullptr) {
            outputMessage = "This attribute description does not exist, check if it is registered or correctness of name!";
            return false;
        }
        attributeDescs_.push_back(std::move(tmpDescription));
        desc = getLast();
        if (!desc->jsonParse(descIt.value(), outputMessage))
        {
            attributeDescs_.clear();
            return false;
        }
    }
    return true;
}

bool AttributeDescriptionsContainer::addDescriptions(std::string attributeName, AttributeType type, std::string &outputMessage)
{
    if (getDescription(attributeName) != nullptr)
    {
        outputMessage = "Attribute with this name already exists!";
        return false;
    }

    attributeDescs_.push_back(descFactory_->createDesc(type));
    getLast()->setName(attributeName);
    return true;
}

AttributeDescription *AttributeDescriptionsContainer::getDescription(std::string name)
{
    for (auto &desc : attributeDescs_)
    {
        if (desc->getName().compare(name) == 0)
        {
            return desc.get();
        }
    }
    return nullptr;
}

bool AttributeDescriptionsContainer::deleteDescription(AttributeDescription *description)
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