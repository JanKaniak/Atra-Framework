#pragma once
#include "json.hpp"

#include <string>
#include <variant>
#include <memory>

enum class AttributeType
{
    INT,
    DOUBLE,
    BOOL,
    CHAR
};

using AttributeTypeVariant = std::variant<int, double, char>;

class AttributeDescription
{
protected:
    std::string name_;
    AttributeType type_;
    std::string agent_;

public:
    AttributeDescription(AttributeType type) : type_(type) {};
    inline std::string getName() { return name_; };
    inline AttributeType getType() { return type_; };
    inline void setName(std::string name) { name_ = name; };
    inline std::string getAgent() { return agent_; }
    void setAgent(std::string agent) { agent_ = agent; }

public:
    virtual ~AttributeDescription() {};
    virtual std::unique_ptr<AttributeDescription> clone() = 0;
    virtual bool jsonParse(nlohmann::ordered_json &json, std::string &outputMessage) = 0;
};

class AttributeDescription_int : public AttributeDescription
{
private:
    int min_ = 10;
    int max_ = 50;

public:
    AttributeDescription_int() : AttributeDescription(AttributeType::INT) {}
    inline int getMin() { return min_; }
    inline int getMax() { return max_; }
    std::unique_ptr<AttributeDescription> clone() override;
    void setLimit(int minimum, int maximum);
    bool jsonParse(nlohmann::ordered_json &json, std::string &outputMessage) override;
};

class AttributeDescription_double : public AttributeDescription
{
private:
    double min_ = 10;
    double max_ = 50;

public:
    AttributeDescription_double() : AttributeDescription(AttributeType::DOUBLE) {}
    inline double getMin() { return min_; }
    inline double getMax() { return max_; }
    std::unique_ptr<AttributeDescription> clone() override;
    void setLimit(double minimum, double maximum);
    bool jsonParse(nlohmann::ordered_json &json, std::string &outputMessage) override;
};