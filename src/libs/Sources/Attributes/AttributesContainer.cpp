#include "AttributesContainer.h"
#include "ControlComponentsContainer.h"

/// Default constructor initializing the attribute factory.
AttributesContainer::AttributesContainer()
{
    attributeFactory_ = AttributeFactory::getInstance();
}

// Constructor initializing the container with a given description store.
AttributesContainer::AttributesContainer(AttributesDescriptionsContainer *attributeDescs) {
    attributeFactory_ = AttributeFactory::getInstance();
    attributeDescs_ = attributeDescs;
}

/// Create attribute instances for all descriptions that are not yet assigned.
bool AttributesContainer::AttributesContainer::createAttributes(std::vector<Message> &messagesHistory)
{
    bool noChange = false;
    for (int i = 0; i < attributeDescs_->getSize(); i++)
    {
        if (attributeDescs_->getDescription(i)->isAssigned())
        {
            if (giveAttributeByName(attributeDescs_->getDescription(i)->getName())->getType() == AttributeType::CLUSTER)
            {
                dynamic_cast<AttributeCluster *>(giveAttributeByName(attributeDescs_->getDescription(i)->getName()))->getAttributeContainer()->createAttributes(messagesHistory);
            }
            continue;
        }
        noChange = true;
        AttributeDescription *desc = attributeDescs_->getDescription(i);
        std::unique_ptr<Attribute> tmpAttributePointer = attributeFactory_->createAttribute(desc->getType());
        if (tmpAttributePointer == nullptr)
        {
            messagesHistory.emplace_back(Message("This attribute type does not exist, check if it is registered or correctness of name!"));
            return false;
        }
        attributes_.push_back(std::move(tmpAttributePointer));
        attributes_.at(attributes_.size() - 1)->setDescription(desc, messagesHistory);
        desc->setAssigned(true);
    }
    return noChange;
}

/// Delete the given attribute instance and its associated description.
bool AttributesContainer::deleteAttribute(Attribute *attribute)
{
    for (auto it = attributes_.begin(); it != attributes_.end(); ++it)
    {
        if (it->get() != attribute)
        {
            continue;
        }
        AttributeDescription *desc = it->get()->getDescription();
        attributes_.erase(it);
        return attributeDescs_->deleteDescription(desc);
    }
    return false;
}

/// Delete an attribute by its name and its associated description.
bool AttributesContainer::deleteAttribute(std::string_view name)
{
    for (auto it = attributes_.begin(); it != attributes_.end(); ++it)
    {
        if (it->get()->getName().compare(name.data()) == 0)
        {
            AttributeDescription *desc = it->get()->getDescription();
            attributes_.erase(it);
            return attributeDescs_->deleteDescription(desc);
        }
    }
    return false;
}

/// Delete an attribute by a dotted path through nested clusters.
bool AttributesContainer::deleteAttributeByPath(std::string path)
{
    if (path.empty())
    {
        return false;
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
        deleteAttribute(path);
    }
    AttributeCluster *tmpAttribute = dynamic_cast<AttributeCluster *>(giveAttributeByName(tmpName));
    if (tmpAttribute == nullptr || tmpAttribute->getAttributeContainer() == nullptr)
    {
        return false;
    }
    return tmpAttribute->getAttributeContainer()->deleteAttributeByPath(tmpPath);
}

/// Find an attribute by its name.
Attribute *AttributesContainer::giveAttributeByName(std::string name)
{
    for (auto &object : attributes_)
    {
        if (object->getName().compare(name) == 0)
        {
            return object.get();
        }
    }
    return nullptr;
}

/// Check whether the container has an attribute with the given name.
bool AttributesContainer::contains(std::string attributeName)
{
    for (int i = 0; i < attributes_.size(); ++i)
    {
        if (attributes_.at(i)->getName().compare(attributeName) == 0)
        {
            return true;
        }
    }
    return false;
}

/// Return the index of an attribute by name, or -1 if not found.
int AttributesContainer::getPosition(std::string attributeName)
{
    for (int i = 0; i < attributes_.size(); ++i)
    {
        if (attributes_.at(i)->getName().compare(attributeName) == 0)
        {
            return i;
        }
    }
    return -1;
}

/// Assign control components to every contained attribute.
///
/// This iterates through all attributes and invokes their `controlOptions` handlers.
void AttributesContainer::setControlTypes(ControlComponentsContainer *components, std::vector<Message> &messagehistory)
{
    for (int i = 0; i < attributes_.size(); ++i)
    {
        ImGui::TableNextRow();
        attributes_.at(i)->controlOptions(i, components, components->getMasterFactory(), messagehistory);
    }
}

/// Destructor clearing the description container reference.
AttributesContainer::~AttributesContainer()
{
    attributeDescs_ = nullptr;
}

/// Remove all attributes from this container.
void AttributesContainer::deleteAllAttributes(std::vector<Message> &messageHistory)
{
    if (attributes_.size() == 0)
    {
        return;
    }
    attributes_.clear();
    messageHistory.emplace_back("All attributes were successfuly removed!");
}

/// Lookup an attribute by a dotted path through nested clusters.
Attribute *AttributesContainer::getAttributeByPath(std::string path)
{
    if (path.empty())
    {
        return nullptr;
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
        return giveAttributeByName(path.data());
    }
    Attribute *tmpAttribute = giveAttributeByName(tmpName);
    if (!tmpPath.empty() && dynamic_cast<AttributeCluster *>(tmpAttribute))
    {
        return dynamic_cast<AttributeCluster *>(tmpAttribute)->getAttributeContainer()->getAttributeByPath(tmpPath);
    }
    return tmpAttribute;
}

const std::vector<Attribute *> AttributesContainer::getAttributes() const
{
    std::vector<Attribute *> tmpVector;
    tmpVector.resize(attributes_.size());
    for (auto &attribute : attributes_)
    {
        tmpVector.push_back(attribute.get());
    }
    return tmpVector;
}
