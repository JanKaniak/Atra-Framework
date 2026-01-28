#pragma once
#include "json.hpp"
#include <string>
#include <variant>
#include <memory>

enum class AttributeType
{
    INT,
    DOUBLE,
    FLOAT,
    BOOL,
    CHAR
};


class AttributeDescription
{
protected:
    std::string name_;
    AttributeType type_;

public:
    AttributeDescription(AttributeType type) : type_(type) {};
    inline std::string getName() { return name_; };
    inline AttributeType getType() { return type_; };
    inline void setName(std::string name) { name_ = name; };

public:
    virtual ~AttributeDescription() {};
    virtual std::unique_ptr<AttributeDescription> clone() = 0;
    virtual bool jsonParse(nlohmann::ordered_json &json, std::string &outputMessage) = 0;
};




