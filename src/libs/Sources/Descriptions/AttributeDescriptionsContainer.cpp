#include "AttributesDescriptionsContainer.h"
#include "ImplementedAttributeDescriptions.h"
#include <format>

/// Construct the attribute description container and acquire singleton helpers.
AttributesDescriptionsContainer::AttributesDescriptionsContainer()
{
    descFactory_ = DescFactory::getInstance();
    lastId_ = GlobalLastIdOfObject::getInstance();
}

/// Add descriptions by type and JSON payload.
///
/// The JSON must contain one or more entries with "Attribute name" fields.
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

/// Create a new attribute description with the given name and type.
///
/// Returns false when the name is empty or already exists in this container.
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

/// Add a description into a nested cluster path.
///
/// The path is dot-separated and resolves through nested cluster descriptions.
bool AttributesDescriptionsContainer::addDescriptionByPath(std::string path, std::string attributeName, AttributeType type, std::vector<Message> *messagesHistory = nullptr)
{
    if (path.empty())
    {
        return addDescription(attributeName, type, messagesHistory);
    }
    int index = path.find_first_of(".", 0);
    std::string tmpName;
    std::string tmpPath;
    if (index != path.npos)
    {
        tmpName = path.substr(0, 0 + index).data();
        tmpPath = (index + 1 < path.length()) ? path.substr(index + 1, path.length()).data() : "";
    }
    else
    {
        return addDescription(attributeName, type, messagesHistory);
    }
    AttributeDescription *tmpDescription = getDescription(tmpName);
    if (tmpDescription->getType() != AttributeType::CLUSTER)
    {
        if (messagesHistory != nullptr)
            messagesHistory->emplace_back("Only cluster attribute descriptions can have descriptons!");
        return false;
    }
    if (tmpDescription->getContainer("", 0) == nullptr)
    {
        if (messagesHistory != nullptr)
            messagesHistory->emplace_back("Cluster attribute description does not have attached attribute descriptions container!");
        return false;
    }
    return tmpDescription->getContainer("", 0)->addDescriptionByPath(tmpPath, attributeName, type, messagesHistory);
}

/// Append an existing attribute description instance to this container.
///
/// Returns false if the description is null or a duplicate name already exists.
bool AttributesDescriptionsContainer::addDescription(std::unique_ptr<AttributeDescription> descriptionPtr)
{
    if (descriptionPtr != nullptr && !existsDescription(descriptionPtr->getName()))
    {
        attributeDescs_.push_back(std::move(descriptionPtr));
        return true;
    }
    return false;
}

/// Clone and add all descriptions from another container.
///
/// Existing descriptions are not checked for duplicates in this version.
bool AttributesDescriptionsContainer::addDescriptions(AttributesDescriptionsContainer *container, std::vector<Message> *messagesHistory)
{
    for (int i = 0; i < container->getSize(); ++i)
    {
        addDescription(container->getDescription(i)->clone());
    }
    return true;
}

/// Find a description by name within this container.
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

/// Return the most recently added description.
AttributeDescription *AttributesDescriptionsContainer::getLast()
{
    if (attributeDescs_.empty())
    {
        return nullptr;
    }
    return attributeDescs_.at(attributeDescs_.size() - 1).get();
}

/// Delete a description by pointer.
///
/// Resets the ID counter when the container becomes empty.
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

/// Delete a description by name from this container.
///
/// Resets the ID counter when the container becomes empty.
bool AttributesDescriptionsContainer::deleteDescription(std::string_view name)
{
    for (auto it = attributeDescs_.begin(); it != attributeDescs_.end(); it++)
    {
        if (it->get()->getName().compare(name) == 0)
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

/// Delete the last added description, if it is not assigned.
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

/// Check whether a description name already exists in this container.
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

/// Append descriptions matching the requested type to the provided vector.
void AttributesDescriptionsContainer::findDescriptionsByType(std::vector<AttributeDescription *> &vector, AttributeType type)
{
    for (auto it = attributeDescs_.begin(); it != attributeDescs_.end(); ++it)
    {
        it->get()->addItselfToVectorByCondition(vector, type);
    }
}

/// Search nested descriptions for the container matching the given description name and ID.
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

/// Remove all descriptions owned by this container.
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

/// Retrieve a description by path and name, navigating nested clusters.
AttributeDescription *AttributesDescriptionsContainer::getDescriptionByPath(std::string path, std::string descriptionName, std::vector<Message> &messagesHistory)
{
    if (path.empty())
    {
        return getDescription(descriptionName);
    }
    int index = path.find_first_of(".", 0);
    std::string tmpName;
    std::string tmpPath;
    if (index != path.npos)
    {
        tmpName = path.substr(0, 0 + index).data();
        tmpPath = (index + 1 < path.length()) ? path.substr(index + 1, path.length()).data() : "";
    }
    else
    {
        return getDescription(path);
    }
    AttributeDescription *tmpDescription = getDescription(tmpName);
    if (tmpDescription->getType() != AttributeType::CLUSTER)
    {
        messagesHistory.emplace_back("Only cluster attribute descriptions can have descriptons!");
        return nullptr;
    }
    if (tmpDescription->getContainer("", 0) == nullptr)
    {
        messagesHistory.emplace_back("Cluster attribute description does not have attached attribute descriptions container!");
        return nullptr;
    }
    return tmpDescription->getContainer("", 0)->getDescriptionByPath(tmpPath, descriptionName, messagesHistory);
}

/// Delete a description by path and name, navigating nested clusters.
bool AttributesDescriptionsContainer::deleteDescriptionByPath(std::string path, std::string name)
{
    if (name.empty())
    {
        return deleteDescription(name);
    }
    int index = path.find_first_of(".", 0);
    std::string tmpName;
    std::string tmpPath;
    if (index != path.npos)
    {
        tmpName = path.substr(0, 0 + index).data();
        tmpPath = (index + 1 < path.length()) ? path.substr(index + 1, path.length()).data() : "";
    }
    else
    {
        return deleteDescription(name);
    }
    AttributeDescription *tmpDescription = getDescription(tmpName);
    if (tmpDescription->getType() != AttributeType::CLUSTER)
    {
        return false;
    }
    if (tmpDescription->getContainer("", 0) == nullptr)
    {
        return false;
    }
    return tmpDescription->getContainer("", 0)->deleteDescriptionByPath(tmpPath, name);
}

/// Destructor clears owned descriptions but does not destroy shared factories.
AttributesDescriptionsContainer::~AttributesDescriptionsContainer()
{
    descFactory_ = nullptr;
    attributeDescs_.clear();
}

/// Return this container or a nested container matching name and ID.
AttributesDescriptionsContainer *AttributesDescriptionsContainer::getDescriptionContainer(std::string_view descriptionName, uint64_t descriptionId)
{
    if (descriptionName.empty() || (descriptionName.compare("NULL") == 0 && descriptionId == 0))
    {
        return this;
    }
    return findDescriptionContainer(descriptionName, descriptionId);
}

TemplateAttributesDescriptionContainer *TemplateAttributesDescriptionContainer::instance_ = nullptr;

/// Return the singleton instance managing template attribute description containers.
TemplateAttributesDescriptionContainer *TemplateAttributesDescriptionContainer::getInstance()
{
    if (instance_ == nullptr)
    {
        instance_ = new TemplateAttributesDescriptionContainer();
    }
    return instance_;
}

// TemplateAttributesDescriptionContainer

/// Add a new template description with a unique name.
bool TemplateAttributesDescriptionContainer::addTemplateDescription(std::string_view name, std::vector<Message> *messageHistory)
{
    if (name.empty())
    {
        messageHistory->emplace_back("Name cannot be empty!");
        return false;
    }

    if (templateExists(name))
    {
        messageHistory->emplace_back("Names must be unique!");
        return false;
    }

    templateDescriptions_.emplace_back(std::make_unique<TemplateAttributesDescription>(name.data()));
    return true;
}

/// Check if a template with the given name already exists.
bool TemplateAttributesDescriptionContainer::templateExists(std::string_view name)
{
    if (name.empty())
    {
        return true;
    }
    for (int i = 0; i < templateDescriptions_.size(); ++i)
    {
        if (templateDescriptions_.at(i)->getName().compare(name) == 0)
        {
            return true;
        }
    }
    return false;
}

/// Retrieve the attribute descriptions container for a named template.
AttributesDescriptionsContainer *TemplateAttributesDescriptionContainer::getContainer(std::string_view name)
{
    if (name.empty())
    {
        return nullptr;
    }

    for (int i = 0; i < templateDescriptions_.size(); ++i)
    {
        if (templateDescriptions_.at(i)->getName().compare(name) == 0)
        {
            return templateDescriptions_.at(i)->getContainer();
        }
    }

    return nullptr;
}

/// Get the name of the template at the specified position.
std::string TemplateAttributesDescriptionContainer::getNameByPosition(int position)
{
    if (position > templateDescriptions_.size() || position < 0)
    {
        return "";
    }
    return templateDescriptions_.at(position)->getName();
}

/// Get the template object at the specified position.
TemplateAttributesDescription *TemplateAttributesDescriptionContainer::getTemplateByPosition(int position)
{
    if (position > templateDescriptions_.size() || position < 0)
    {
        return nullptr;
    }
    return templateDescriptions_.at(position).get();
}

/// Remove a template by its pointer.
bool TemplateAttributesDescriptionContainer::removeTemplateDescription(TemplateAttributesDescription *templateDescription)
{
    if (templateDescription == nullptr)
    {
        return false;
    }
    for (auto it = templateDescriptions_.begin(); it != templateDescriptions_.end(); ++it)
    {
        if (it->get() == templateDescription)
        {
            templateDescriptions_.erase(it);
            return true;
        }
    }
    return false;
}

/// Remove a template by its name.
bool TemplateAttributesDescriptionContainer::removeTemplateDescription(std::string_view name)
{
    if (name.empty())
    {
        return false;
    }
    for (auto it = templateDescriptions_.begin(); it != templateDescriptions_.end(); ++it)
    {
        if (it->get()->getName().compare(name) == 0)
        {
            templateDescriptions_.erase(it);
            return true;
        }
    }
    return false;
}