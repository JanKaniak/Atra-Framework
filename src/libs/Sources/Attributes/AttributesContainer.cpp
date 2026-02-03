#include "AttributesContainer.h"

Attributes::Attributes()
{
    attributeDescs_ = std::make_unique<AttributeDescriptionsContainer>();
    attributeFactory_ = AttributeFactory::getInstance();
}

void Attributes::createAttributes()
{
    for (int i = 0; i < attributeDescs_->getSize(); i++)
    {
        if (contains(attributeDescs_->getDescription(i)->getName())) {
            continue;
        }
        AttributeDescription *desc = attributeDescs_->getDescription(i);
        attributes_.push_back(attributeFactory_->createAttribute(desc->getType()));
        attributes_.at(attributes_.size() - 1)->setDescription(desc);
    }
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
