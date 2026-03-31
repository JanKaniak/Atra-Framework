#pragma once
#include "ImplementedAttribute.h"
#include "AttributesDescriptionsContainer.h"
#include <vector>
#include <memory>
#include <map>

//------------------------------------------



class AttributesContainer
{
private:
    AttributesDescriptionsContainer* attributeDescs_;
    std::vector<std::unique_ptr<Attribute>> attributes_;
    AttributeFactory *attributeFactory_;

public:
    AttributesContainer();
    AttributesContainer(AttributesDescriptionsContainer* attributeDescs);
    ~AttributesContainer();
    bool addDescription(AttributeType type, nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) { return attributeDescs_->addDescription(type, json, messagesHistory); }
    bool addDescription(std::string attributeName, AttributeType type, std::vector<Message> &messagesHistory) { return attributeDescs_->addDescription(attributeName, type, messagesHistory); }
    bool createAttributes(std::vector<Message> &messagesHistory);
    inline Attribute *getLast() { return attributes_.at(attributes_.size() - 1).get(); }
    inline int getSize() { return attributes_.size(); }
    inline int getNumberOfDescriptions() { return attributeDescs_->getSize(); }
    inline Attribute *giveAttribute(int rank) { return attributes_.at(rank).get(); }
    Attribute *giveAttributeByName(std::string name);
    bool contains(std::string attributeName);
    bool deleteAttribute(Attribute *attribute);
    void reverseOrder() { std::reverse(attributes_.begin(), attributes_.end()); }
    inline std::vector<AttributeTypeC> getRegisteredDescriptionsTypes() { return attributeDescs_->getRegisteredDescriptionsTypes(); }
    int getPosition(std::string attributeName);
    AttributeDescription *getDescription(int rank) { return attributeDescs_->getDescription(rank); }
    bool deleteLastDescription(std::vector<Message> &messagesHistory) { return attributeDescs_->deleteLastDescription(messagesHistory); }
    void changeDescriptionContainer(AttributesDescriptionsContainer *descs) { attributeDescs_ = descs; }
    void setControlTypes(ControlComponentsContainer *components, Config *config, std::vector<Message> &messagehistory);
    bool existDescription(std::string_view name) { return attributeDescs_->existsDescription(name); }
    void findDescriptionsByType(std::vector<AttributeDescription *> &vector, AttributeType type)
    {
        attributeDescs_->findDescriptionsByType(vector, type);
    }
    
    
};