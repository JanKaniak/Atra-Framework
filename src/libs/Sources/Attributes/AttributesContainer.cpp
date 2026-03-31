#include "AttributesContainer.h"

AttributesContainer::AttributesContainer() {
    attributeFactory_ = AttributeFactory::getInstance();
}

AttributesContainer::AttributesContainer(AttributesDescriptionsContainer* attributeDesc) {
    attributeDescs_ = attributeDesc;
    attributeFactory_ = AttributeFactory::getInstance();
    
}

bool AttributesContainer::createAttributes(std::vector<Message>& messagesHistory)
{
    bool noChange = false;
    for (int i = 0; i < attributeDescs_->getSize(); i++)
    {
        if (attributeDescs_->getDescription(i)->isAssigned()) {
            if (giveAttributeByName(attributeDescs_->getDescription(i)->getName())->getType() == AttributeType::CLUSTER) {
                dynamic_cast<AttributeCluster*>(giveAttributeByName(attributeDescs_->getDescription(i)->getName()))->getAttributeContainer()->createAttributes(messagesHistory);
            }
            continue;
        }
        noChange = true;
        AttributeDescription *desc = attributeDescs_->getDescription(i);
        std::unique_ptr<Attribute> tmpAttributePointer = attributeFactory_->createAttribute(desc->getType());
        if (tmpAttributePointer == nullptr) {
            messagesHistory.emplace_back(Message("This attribute type does not exist, check if it is registered or correctness of name!"));
            return false;
        }
        attributes_.push_back(std::move(tmpAttributePointer));
        attributes_.at(attributes_.size() - 1)->setDescription(desc,messagesHistory);
        desc->setAssigned(true);     
    }
    return noChange;
}

bool AttributesContainer::deleteAttribute(Attribute *attribute)
{
    for (auto it = attributes_.begin(); it != attributes_.end(); ++it)
    {
        if (it->get() != attribute)
        {
            continue;
        }
        AttributeDescription* desc = it->get()->getDescription();
        attributes_.erase(it);
        if (attributeDescs_->deleteDescription(desc))
        {
            
            return true;
        }
    }
    return false;
}

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

bool AttributesContainer::contains(std::string attributeName)
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

int AttributesContainer::getPosition(std::string attributeName) {
    for (int i = 0; i < attributes_.size(); ++i) {
        if (attributes_.at(i)->getName().compare(attributeName) == 0) {
            return i;
        }
    }
    return -1;
}

void AttributesContainer::setControlTypes(ControlComponentsContainer *components, Config *config, std::vector<Message>& messagehistory) {
    for (int i = 0; i < attributes_.size();++i) {
        ImGui::TableNextRow();
        attributes_.at(i)->controlOptions(i,components,config,messagehistory);
    }
}

AttributesContainer::~AttributesContainer() {
    attributeDescs_ = nullptr;

}















