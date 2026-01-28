    #pragma once
#include "json.hpp"
#include "DescriptionFactory.h"
#include <string>
#include <variant>
#include <memory>


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

struct AutoRegisterIntDescription {
    inline static bool registerIntDescription = [] () {
        DescFactory::getInstance().registerPrototype(std::make_unique<AttributeDescription_int>());
        return true;
    }();
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

struct AutoRegisterDoubleDescription {
    inline static bool registerDoubleDescription = [] () {
        DescFactory::getInstance().registerPrototype(std::make_unique<AttributeDescription_double>());
        return true;
    }();
};



class AttributeDescription_float : public AttributeDescription
{
private:
    float min_ = 10;
    float max_ = 50;

public:
    AttributeDescription_float() : AttributeDescription(AttributeType::FLOAT) {}
    inline float getMin() { return min_; }
    inline float getMax() { return max_; }
    std::unique_ptr<AttributeDescription> clone() override;
    void setLimit(float minimum, float maximum);
    bool jsonParse(nlohmann::ordered_json &json, std::string &outputMessage) override;
};

struct AutoRegisterFloatDescription {
    inline static bool registerFloatDescription = [] () {
        DescFactory::getInstance().registerPrototype(std::make_unique<AttributeDescription_float>());
        return true;
    }();
};