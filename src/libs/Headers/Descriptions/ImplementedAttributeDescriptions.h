#pragma once

#include "json.hpp"
#include "DescriptionFactory.h"
#include <string>
#include <variant>
#include <memory>


#define Attribute_descriptions \
    X(AttributeDescription_int, int, INT, 10, 50, "NUMERIC", ImGuiDataType_S32, Int) \
    X(AttributeDescription_double, double, DOUBLE, 10, 50, "NUMERIC", ImGuiDataType_Double, Double) \
    X(AttributeDescription_float, float, FLOAT, 10, 50, "NUMERIC", ImGuiDataType_Float, Float) \
    X(AttributeDescription_long, long, LONG, 10, 50, "NUMERIC", ImGuiDataType_S64, Long) \
    X(AttributeDescription_u_int, uint, UINT, 10, 50, "NUMERIC", ImGuiDataType_U32, Uint)

#define X(className, type, attributeTypeEnum, minimumP, maximumP, categoryP, imguiDataType, attributeTypeName) \
class className : public AttributeDescription \
{ \
private: \
    type min_; \
    type max_; \
 \
public: \
    className() : AttributeDescription(AttributeType::attributeTypeEnum) { \
        min_ = minimumP; \
        max_ = maximumP; \
        category_ = categoryP; \
        dataType_ = imguiDataType; \
    } \
    inline type getMin() { return min_;} \
    inline type getMax() { return max_;} \
    std::unique_ptr<AttributeDescription> clone() override; \
    void setLimit(type minimu, type maximum); \
    bool jsonParse(nlohmann::ordered_json &json, std::string &outputMessage) override; \
}; \
\
struct AutoRegister##attributeTypeName##Description { \
    inline static bool register##attributeTypeName##Description = [] () { \
        DescFactory::getInstance()->registerPrototype(std::make_unique<className>()); \
        return true; \
    }(); \
};
Attribute_descriptions
#undef X














/*class AttributeDescription_int : public AttributeDescription
{
private:
    int min_;
    int max_;
    

public:
    AttributeDescription_int() : AttributeDescription(AttributeType::INT) {
        min_ = 10;
        max_ = 50;
        category_ = "NUMERIC";
        dataType_ = ImGuiDataType_S32;
    }
    inline int getMin() { return min_; }
    inline int getMax() { return max_; }
    std::unique_ptr<AttributeDescription> clone() override;
    void setLimit(int minimum, int maximum);
    bool jsonParse(nlohmann::ordered_json &json, std::string &outputMessage) override;
};

struct AutoRegisterIntDescription {
    inline static bool registerIntDescription = [] () {
        DescFactory::getInstance()->registerPrototype(std::make_unique<AttributeDescription_int>());
        return true;
    }();
};



class AttributeDescription_double : public AttributeDescription
{
private:
    double min_;
    double max_;

public:
    AttributeDescription_double() : AttributeDescription(AttributeType::DOUBLE) {
        min_ = 10;
        max_ = 50;
        category_ = "NUMERIC";
        dataType_ = ImGuiDataType_Double;
    }
    inline double getMin() { return min_; }
    inline double getMax() { return max_; }
    std::unique_ptr<AttributeDescription> clone() override;
    void setLimit(double minimum, double maximum);
    bool jsonParse(nlohmann::ordered_json &json, std::string &outputMessage) override;
};

struct AutoRegisterDoubleDescription {
    inline static bool registerDoubleDescription = [] () {
        DescFactory::getInstance()->registerPrototype(std::make_unique<AttributeDescription_double>());
        return true;
    }();
};



class AttributeDescription_float : public AttributeDescription
{
private:
    float min_;
    float max_;

public:
    AttributeDescription_float() : AttributeDescription(AttributeType::FLOAT) {
        min_ = 10;
        max_ = 50;
        category_ = "NUMERIC";
        dataType_ = ImGuiDataType_Float;
    }
    inline float getMin() { return min_; }
    inline float getMax() { return max_; }
    void setLimit(float minimum, float maximum);


    std::unique_ptr<AttributeDescription> clone() override;
    bool jsonParse(nlohmann::ordered_json &json, std::string &outputMessage) override;
};

struct AutoRegisterFloatDescription {
    inline static bool registerFloatDescription = [] () {
        DescFactory::getInstance()->registerPrototype(std::make_unique<AttributeDescription_float>());
        return true;
    }();
};

class AttributeDescription_long : public AttributeDescription
{
private:
    long min_;
    long max_;

public:
    AttributeDescription_long() : AttributeDescription(AttributeType::LONG) {
        min_ = 10;
        max_ = 50;
        category_ = "NUMERIC";
        dataType_ = ImGuiDataType_S64;
    }
    inline long getMin() { return min_; }
    inline long getMax() { return max_; }
    void setLimit(long minimum, long maximum);


    std::unique_ptr<AttributeDescription> clone() override;
    bool jsonParse(nlohmann::ordered_json &json, std::string &outputMessage) override;
};

struct AutoRegisterLongDescription {
    inline static bool registerLongDescription = [] () {
        DescFactory::getInstance()->registerPrototype(std::make_unique<AttributeDescription_long>());
        return true;
    }();
};

class AttributeDescription_u_int : public AttributeDescription
{
private:
    uint min_;
    uint max_;

public:
    AttributeDescription_u_int() : AttributeDescription(AttributeType::U_INT) {
        min_ = 10;
        max_ = 50;
        category_ = "NUMERIC";
        dataType_ = ImGuiDataType_U32;
    }
    inline uint getMin() { return min_; }
    inline uint getMax() { return max_; }
    void setLimit(uint minimum, uint maximum);


    std::unique_ptr<AttributeDescription> clone() override;
    bool jsonParse(nlohmann::ordered_json &json, std::string &outputMessage) override;
};

struct AutoRegisterUintDescription {
    inline static bool registerUintDescription = [] () {
        DescFactory::getInstance()->registerPrototype(std::make_unique<AttributeDescription_u_int>());
        return true;
    }();
};*/

class AttributeDescription_char : public AttributeDescription
{
private:
    int min_;
    int max_;

public:
    AttributeDescription_char() : AttributeDescription(AttributeType::CHAR) {
        min_ = 0;
        max_ = 1;
        category_ = "TEXT";
        dataType_ = ImGuiDataType_S8;
    }
    inline float getMin() { return min_; }
    inline float getMax() { return max_; }
    void setLimit(int minimum);

    std::unique_ptr<AttributeDescription> clone() override;
    bool jsonParse(nlohmann::ordered_json &json, std::string &outputMessage) override;
};

struct AutoRegisterCharDescription {
    inline static bool registerFloatDescription = [] () {
        DescFactory::getInstance()->registerPrototype(std::make_unique<AttributeDescription_char>());
        return true;
    }();
};