#include "AttributesContainer.h"

Attributes::Attributes()
{
    attributeDescs_ = std::make_unique<AttributeDescriptionsContainer>();
    attributeFactory_ = AttributeFactory::getInstance();
}

bool Attributes::createAttributes(std::string &outputMessage)
{
    bool noChange = false;
    for (int i = 0; i < attributeDescs_->getSize(); i++)
    {
        if (contains(attributeDescs_->getDescription(i)->getName())) {
            continue;
        }
        noChange = true;
        AttributeDescription *desc = attributeDescs_->getDescription(i);
        std::unique_ptr<Attribute> tmpAttributePointer = attributeFactory_->createAttribute(desc->getType());
        if (tmpAttributePointer == nullptr) {
            outputMessage = "This attribute type does not exist, check if it is registered or correctness of name!";
            return false;
        }
        attributes_.push_back(std::move(tmpAttributePointer));
        attributes_.at(attributes_.size() - 1)->setDescription(desc);
        
    }
    return noChange;
}

bool Attributes::deleteAttribute(Attribute *attribute)
{
    for (auto it = attributes_.begin(); it != attributes_.end(); it++)
    {
        if (it->get() != attribute)
        {
            continue;
        }
        if (attributeDescs_->deleteDescription(it->get()->getDescription()))
        {
            attributes_.erase(it);
            return true;
        }
    }
    return false;
}

Attribute *Attributes::giveAttributeByName(std::string name)
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

bool Attributes::contains(std::string attributeName)
{
    for (auto &object : attributes_)
    {
        if (object->getName().compare(attributeName) == 0)
        {
            return true;
        }
    }
    return false;
}

int Attributes::getPosition(std::string attributeName) {
    for (int i = 0; i < attributes_.size(); ++i) {
        if (attributes_.at(i)->getName().compare(attributeName) == 0) {
            return i;
        }
    }
    return -1;
}
