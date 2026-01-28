#pragma once
#include "AttributeDescriptions.h"
#include "Attribute.h"
#include <vector>
#include <memory>
#include <map>

using AttributeUptr = std::unique_ptr<Attribute>;
using AttributeTypeVariant = std::variant<int, double, char>;

class AttributeFactory
{
private:
    std::map<AttributeType, AttributeUptr> prototypes_;

public:
    inline AttributeUptr createAttribute(AttributeType type) { return prototypes_[type]->clone(); }

    template <typename AttributeTypeT>
    void registerPrototype()
    {
        AttributeUptr prototype = std::make_unique<AttributeTypeT>();
        prototypes_[prototype->getType()] = std::move(prototype);
    }
};

//------------------------------------------

class Attributes
{
private:
    std::unique_ptr<AttributeDescriptions> attributeDescs_;
    std::vector<std::unique_ptr<Attribute>> attributes_;
    AttributeFactory attributeFactory_;

public:
    Attributes();

    void addAttribute(std::string agentName,std::string attributeName, AttributeType type, AttributeTypeVariant minimum, AttributeTypeVariant maximum);
    bool addDescriptions(AttributeType type, nlohmann::ordered_json &json, std::string agentName, std::string &outputMessage) { return attributeDescs_->addDescriptions(type,json,agentName,outputMessage);}
    void createAttributes();
    void setAttributeValue(std::string name, AttributeType type, AttributeTypeVariant value);
    inline Attribute *getLast() { return attributes_.at(attributes_.size() - 1).get(); }
    inline int getSize() { return attributes_.size(); }
    inline Attribute *giveAttribute(int rank) { return attributes_.at(rank).get(); }
    Attribute *giveAttributeByName(std::string name);
    bool contains(std::string attributeName,std::string agent);
    bool deleteAttribute(Attribute* attribute);
    void reverseOrder() { std::reverse(attributes_.begin(),attributes_.end());}
    void vypis() { attributeDescs_.get()->vypis();}
};