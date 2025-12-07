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

    void setAttributeValue(std::string name, AttributeType type, AttributeTypeVariant value);

    int giveInt(std::string name);

    inline Attribute *getLast() { return attributes_.at(attributes_.size() - 1).get(); }

    inline int getSize() { return attributes_.size(); }

    inline Attribute *giveAttribute(int rank) { return attributes_.at(rank).get(); }
    inline Attribute *giveAttributeByName(std::string name)
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

    void setValueOfLast(AttributeType type, AttributeTypeVariant value)
    {
        attributes_.at(attributes_.size() - 1)->setValue(value);
    }

    bool contains(std::string attributeName,std::string agent) {
        for (auto &object : attributes_) {
            if (object->getName().compare(attributeName) == 0 && object->getAgent().compare(agent) == 0) {
                return true;
            }
        }
        return false;
    }
};