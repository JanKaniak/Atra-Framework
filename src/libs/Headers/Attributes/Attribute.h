#pragma once
#include "ImplementedAttributeDescriptions.h"
#include <string>
#include <limits.h>
#include <iostream>
#include <variant>
#include <stdexcept>
#include <memory>

using AttributeTypeVariant = std::variant<int, double, char>;

class Attribute
{
protected:
public:
    // AtributeType type_;
    virtual std::string getName() = 0;
    virtual AttributeType getType() = 0;
    virtual AttributeDescription *getDescription() = 0;
    virtual ~Attribute() {};
    virtual std::unique_ptr<Attribute> clone() = 0;
    virtual void setDescription(AttributeDescription *desc) = 0;
    virtual bool saveToJson(nlohmann::ordered_json &json, std::string &outputMessage) = 0;
};

