#pragma once
#include "ImplementedAttributeDescriptions.h"




#include <string>
#include <limits.h>
#include <iostream>
#include <variant>
#include <stdexcept>
#include <memory>

struct ChosenControl {
    AttributeType type_;
    std::string controlType_;

    ChosenControl(AttributeType type,std::string controlType) : type_(type),controlType_(controlType) {}
};

class Config;
class ControlComponentsContainer;

class Attribute
{
public:
    virtual std::string getName() = 0;
    virtual AttributeType getType() = 0;
    virtual AttributeDescription *getDescription() = 0;
    virtual ~Attribute() = 0;
    virtual std::unique_ptr<Attribute> clone() = 0;
    virtual void setDescription(AttributeDescription *desc, std::vector<Message>& messagesHistory) = 0;
    virtual bool saveToJson(nlohmann::ordered_json &json, std::vector<Message>& messagesHistory) = 0;
    virtual void controlOptions(int position,ControlComponentsContainer *components, Config *config, std::vector<Message>& messagesHistory) = 0;
};

