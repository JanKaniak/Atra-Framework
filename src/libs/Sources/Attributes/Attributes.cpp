#include "Attributes.h"

Attributes::Attributes()
{
    attributeDescs_ = std::make_unique<AttributeDescriptions>();
    attributeFactory_.registerPrototype<AttributeInt>();
    attributeFactory_.registerPrototype<AttributeDouble>();
    attributeFactory_.registerPrototype<AttributeFloat>();
}

/*void Attributes::addAttribute(std::string agentName,std::string attributeName, AttributeType type, AttributeTypeVariant minimum, AttributeTypeVariant maximum) {
            attributeDescs_->addDescription(agentName,attributeName,type,minimum,maximum);
            attributes_.push_back(attributeFactory_.createAttribute(type));
            attributes_.at(attributes_.size() - 1)->setDescription(attributeDescs_->getLast());


};*/

void Attributes::createAttributes()
{
    for (int i = 0; i < attributeDescs_->getSize(); i++)
    {
        AttributeDescription *desc = attributeDescs_->getDescription(i);
        attributes_.push_back(attributeFactory_.createAttribute(desc->getType()));
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

bool Attributes::contains(std::string attributeName, std::string agent)
{
    for (auto &object : attributes_)
    {
        if (object->getName().compare(attributeName) == 0 && object->getAgent().compare(agent) == 0)
        {
            return true;
        }
    }
    return false;
}
