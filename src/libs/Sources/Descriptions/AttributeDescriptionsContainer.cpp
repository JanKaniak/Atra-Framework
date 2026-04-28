#include "AttributesDescriptionsContainer.h"
#include <format>

AttributesDescriptionsContainer::AttributesDescriptionsContainer()
{
    descFactory_ = DescFactory::getInstance();
    lastId_ = GlobalLastIdOfObject::getInstance();
}

bool AttributesDescriptionsContainer::addDescription(AttributeType type, nlohmann::ordered_json &json, std::vector<Message> *messagesHistory = nullptr)
{
    if (type == AttributeType::NOTATYPE)
    {
        messagesHistory->emplace_back(Message("Incorrect attribute type name!"));
        return false;
    }
    for (auto descIt = json.begin(); descIt != json.end(); ++descIt)
    {
        if (descIt.value().find("Attribute name") == descIt.value().end())
        {
            if (messagesHistory != nullptr)
                messagesHistory->emplace_back(Message("Incorrect json format!"));
            return false;
        }
        AttributeDescription *desc = getDescription(descIt.value()["Attribute name"].get<std::string>());
        if (desc != nullptr)
        {
            continue;
        }
        std::unique_ptr<AttributeDescription> tmpDescription = descFactory_->createDesc(type);
        if (tmpDescription == nullptr)
        {
            if (messagesHistory != nullptr)
                messagesHistory->emplace_back(Message(std::format("The {} attribute description does not exist, check if it is registered or correctness of name!", AttributeTypeConverter::EnumToString(type))));
            return false;
        }
        attributeDescs_.push_back(std::move(tmpDescription));
        desc = getLast();
        desc->setID(lastId_->getNewId());
        if (!desc->jsonParse(descIt.value(), messagesHistory))
        {
            attributeDescs_.clear();
            return false;
        }
    }
    return true;
}

bool AttributesDescriptionsContainer::addDescription(std::string attributeName, AttributeType type, std::vector<Message> *messagesHistory = nullptr)
{
    if (getDescription(attributeName) != nullptr)
    {
        if (messagesHistory != nullptr)
            messagesHistory->emplace_back(Message("Attribute with this name already exists!"));
        return false;
    }

    if (attributeName.empty())
    {
        if (messagesHistory != nullptr)
            messagesHistory->emplace_back("Attribute name cannot be empty!");
        return false;
    }
    attributeDescs_.push_back(descFactory_->createDesc(type));
    getLast()->setName(attributeName);
    getLast()->setID(lastId_->getNewId());
    return true;
}

bool AttributesDescriptionsContainer::addDescription(std::unique_ptr<AttributeDescription> descriptionPtr)
{
    if (descriptionPtr != nullptr && !existsDescription(descriptionPtr->getName()))
    {
        attributeDescs_.push_back(std::move(descriptionPtr));
        return true;
    }
    return false;
}

bool AttributesDescriptionsContainer::addDescriptions(AttributesDescriptionsContainer *container, std::vector<Message> *messagesHistory)
{
    for (int i = 0; i < container->getSize(); ++i)
    {
        addDescription(container->getDescription(i)->clone());
    }
    return true;
}

AttributeDescription *AttributesDescriptionsContainer::getDescription(std::string name)
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

AttributeDescription *AttributesDescriptionsContainer::getLast()
{
    if (attributeDescs_.empty())
    {
        return nullptr;
    }
    return attributeDescs_.at(attributeDescs_.size() - 1).get();
}

bool AttributesDescriptionsContainer::deleteDescription(AttributeDescription *description)
{
    for (auto it = attributeDescs_.begin(); it != attributeDescs_.end(); it++)
    {
        if (it->get() == description)
        {
            attributeDescs_.erase(it);
            if (attributeDescs_.empty())
            {
                lastId_->resetIdCounter();
            }
            return true;
        }
    }
    return false;
}

bool AttributesDescriptionsContainer::deleteLastDescription(std::vector<Message> *messagesHistory = nullptr)
{
    if (attributeDescs_.empty())
    {
        if (messagesHistory != nullptr)
            messagesHistory->emplace_back(Message("There are no attribute descriptions to remove!"));
        return false;
    }

    if (attributeDescs_.rbegin()->get()->isAssigned())
    {
        if (messagesHistory != nullptr)
            messagesHistory->emplace_back(Message("Can't remove assigned attribute description!"));
        return false;
    }

    attributeDescs_.erase(attributeDescs_.end() - 1);
    if (messagesHistory != nullptr)
        messagesHistory->emplace_back(Message("Attribute description successfuly removed!"));
    if (attributeDescs_.empty())
    {
        lastId_->resetIdCounter();
    }
    return true;
}

bool AttributesDescriptionsContainer::existsDescription(std::string_view name)
{
    for (int i = 0; i < attributeDescs_.size(); ++i)
    {
        if (attributeDescs_.at(i)->getName().compare(name) == 0)
        {
            return true;
        }
    }
    return false;
}

void AttributesDescriptionsContainer::findDescriptionsByType(std::vector<AttributeDescription *> &vector, AttributeType type)
{
    for (auto it = attributeDescs_.begin(); it != attributeDescs_.end(); ++it)
    {
        it->get()->addItselfToVectorByCondition(vector, type);
    }
}

AttributesDescriptionsContainer *AttributesDescriptionsContainer::findDescriptionContainer(std::string_view descriptionName, uint64_t descriptionId)
{
    for (int i = 0; i < attributeDescs_.size(); ++i)
    {
        AttributesDescriptionsContainer *container = attributeDescs_.at(i)->getContainer(descriptionName, descriptionId);
        if (container != nullptr)
        {
            return container;
        }
    }
    return this;
}

void AttributesDescriptionsContainer::deleteAllDescriptions(std::vector<Message> *messagesHistory)
{
    if (attributeDescs_.size() == 0)
    {
        return;
    }
    attributeDescs_.clear();
    if (messagesHistory != nullptr)
        messagesHistory->emplace_back("All attribute descriptions were successfuly removed!");
}

AttributesDescriptionsContainer::~AttributesDescriptionsContainer()
{
    descFactory_ = nullptr;
    attributeDescs_.clear();
}

AttributesDescriptionsContainer *AttributesDescriptionsContainer::getDescriptionContainer(std::string_view descriptionName, uint64_t descriptionId)
{
    if (descriptionName.empty() || (descriptionName.compare("NULL") == 0 && descriptionId == 0))
    {
        return this;
    }
    return findDescriptionContainer(descriptionName, descriptionId);
}

TemplateAttributesDescriptionContainer *TemplateAttributesDescriptionContainer::instance_ = nullptr;

TemplateAttributesDescriptionContainer *TemplateAttributesDescriptionContainer::getInstance()
{
    if (instance_ == nullptr)
    {
        instance_ = new TemplateAttributesDescriptionContainer();
    }
    return instance_;
}