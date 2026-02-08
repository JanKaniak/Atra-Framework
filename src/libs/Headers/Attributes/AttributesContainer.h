#pragma once
#include "ImplementedAttribute.h"
#include <vector>
#include <memory>
#include <map>


//------------------------------------------

class Attributes
{
private:
    std::unique_ptr<AttributeDescriptionsContainer> attributeDescs_;
    std::vector<std::unique_ptr<Attribute>> attributes_;
    AttributeFactory* attributeFactory_;

public:
    Attributes();
    bool addDescriptions(AttributeType type, nlohmann::ordered_json &json, std::string &outputMessage) { return attributeDescs_->addDescriptions(type,json,outputMessage);}
    bool addDescriptions(std::string attributeName, AttributeType type, std::string &outputMessage) { return attributeDescs_->addDescriptions(attributeName, type,outputMessage);}
    bool createAttributes(std::string &outputMessage);
    void setAttributeValue(std::string name, AttributeType type, AttributeTypeVariant value);
    inline Attribute *getLast() { return attributes_.at(attributes_.size() - 1).get(); }
    inline int getSize() { return attributes_.size(); }
    inline int getNumberOfDescriptions() {return attributeDescs_->getSize();}
    inline Attribute *giveAttribute(int rank) { return attributes_.at(rank).get(); }
    Attribute *giveAttributeByName(std::string name);
    bool contains(std::string attributeName);
    bool deleteAttribute(Attribute* attribute);
    void reverseOrder() { std::reverse(attributes_.begin(),attributes_.end());}
    inline std::vector<AttributeTypeC> getRegisteredDescriptionsTypes() { return attributeDescs_->getRegisteredDescriptionsTypes();}
    int getPosition(std::string attributeName);
};