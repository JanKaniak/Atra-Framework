#include "AttributeDescriptionsContainer.h"
#include <format>

AttributeDescriptionsContainer::AttributeDescriptionsContainer()
{
    descFactory_ = DescFactory::getInstance();
}

bool AttributeDescriptionsContainer::addDescriptions(AttributeType type, nlohmann::ordered_json &json, std::vector<Message>& messagesHistory)
{
    if (type == AttributeType::NOTATYPE) {
        messagesHistory.emplace_back(Message("Incorrect attribute type name!"));
        return false;
    }
    for (auto descIt = json.begin(); descIt != json.end(); ++descIt)
    {
        if (descIt.value().find("Attribute name") == descIt.value().end())
        {
            messagesHistory.emplace_back(Message("Incorrect json format!"));
            return false;
        }
        AttributeDescription *desc = getDescription(descIt.value()["Attribute name"].get<std::string>());
        if (desc != nullptr)
        {
            continue;
        }
        std::unique_ptr<AttributeDescription> tmpDescription = descFactory_->createDesc(type);
        if (tmpDescription == nullptr) {
            messagesHistory.emplace_back(Message(std::format("The {} attribute description does not exist, check if it is registered or correctness of name!",AttributeTypeConverter::EnumToString(type))));
            return false;
        }
        attributeDescs_.push_back(std::move(tmpDescription));
        desc = getLast();
        if (!desc->jsonParse(descIt.value(), messagesHistory))
        {
            attributeDescs_.clear();
            return false;
        }
    }
    return true;
}

bool AttributeDescriptionsContainer::addDescriptions(std::string attributeName, AttributeType type, std::vector<Message>& messagesHistory)
{
    if (getDescription(attributeName) != nullptr)
    {
        messagesHistory.emplace_back(Message("Attribute with this name already exists!"));
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

bool AttributeDescriptionsContainer::deleteLastDescription(std::vector<Message>& messagesHistory) {
    if (attributeDescs_.empty()) {
        messagesHistory.emplace_back(Message("There are no attribute descriptions to remove!"));
        return false;
    }

    if (attributeDescs_.rbegin()->get()->isAssigned()) {
        messagesHistory.emplace_back(Message("Can't remove assigned attribute description!"));
        return false;
    }

    attributeDescs_.erase(attributeDescs_.end()-1);
    messagesHistory.emplace_back(Message("Attribute description successfuly removed!"));
    return true;

    
}

void AttributeDescriptionsContainer::findDescriptionsByType(std::vector<AttributeDescription*>& vector,AttributeType type) {
    for (auto it = attributeDescs_.begin(); it != attributeDescs_.end(); ++it) {
        it->get()->addItselfToVectorByCondition(vector,type);
    }
}