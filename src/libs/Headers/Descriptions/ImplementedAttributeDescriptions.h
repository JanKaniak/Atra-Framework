#pragma once

#include "json.hpp"
#include "DescriptionFactory.h"
#include <string>
#include <variant>
#include <memory>

/*template <typenate TypeT, typenate EnumID, int Min, int Max, typename ValueT>
class Primitve_Number : public AttributeDescription {
public:
    Primitve_Number() : m_min(0), m_:max(0) {}

    TypeT getMin() constexpr { return m_min; }
    TypeT getMax() constexpr { return m_max; }
private
    TypeT m_min;
    TypeT m_max;
};
*/
//class AttributeDescription_int : public Primitve_Number<int, INT, 10, 50, ImGuiDataType_S32> {};



template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
class IntegerNumberBaseClass : public AttributeDescription
{
private:
    TypeT min_;
    TypeT max_;
public:
    IntegerNumberBaseClass(TypeT min, TypeT max, AttributeType attributeType, std::string category) : AttributeDescription(attributeType), min_(min), max_(max) {
        category_ = category;
        dataType_ = ImGuiDataTypeT;
    }

    constexpr TypeT getMinimum() { return min_; }
    constexpr TypeT getMaximum() { return max_; }
    void setLimit(TypeT minimum, TypeT maximum);
    bool jsonParse(nlohmann::ordered_json &json, std::string &outputMessage) override;
};


template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
class DecimalNumberBaseClass : public AttributeDescription
{
private:
    TypeT min_;
    TypeT max_;
public:
    DecimalNumberBaseClass(TypeT min, TypeT max, AttributeType attributeType, std::string category) : AttributeDescription(attributeType), min_(min), max_(max) {
        category_ = category;
        dataType_ = ImGuiDataTypeT;
    }

    constexpr TypeT getMinimum() { return min_; }
    constexpr TypeT getMaximum() { return max_; }
    void setLimit(TypeT minimum, TypeT maximum);
    bool jsonParse(nlohmann::ordered_json &json, std::string &outputMessage) override;
};

template <typename AttributeDescriptionType>
struct AutoRegisterDescription {
    inline static bool autoRegister = [] () {
        DescFactory::getInstance()->registerPrototype(std::make_unique<AttributeDescriptionType>());
        return true;
    } ();
};








class AttributeDescription_int : public IntegerNumberBaseClass<int, ImGuiDataType_S32, nlohmann::json::value_t::number_integer>
 {
public:
    AttributeDescription_int() : IntegerNumberBaseClass(10,50,AttributeType::INT, "NUMERIC") {}
    std::unique_ptr<AttributeDescription> clone() override;
 };

 struct AutoRegisterIntDescription : public AutoRegisterDescription<AttributeDescription_int>
{
    inline static bool registerDescription = [] () { AutoRegisterDescription::autoRegister; };
};


class AttributeDescription_double : public DecimalNumberBaseClass<double, ImGuiDataType_Double, nlohmann::json::value_t::number_float>
 {
public:
    AttributeDescription_double() : DecimalNumberBaseClass(10,50,AttributeType::DOUBLE, "NUMERIC") {}
    std::unique_ptr<AttributeDescription> clone() override;
 };

 struct AutoRegisterDoubleDescription : public AutoRegisterDescription<AttributeDescription_double>
{
    inline static bool registerDescription = [] () { AutoRegisterDescription::autoRegister; };
};


class AttributeDescription_float : public DecimalNumberBaseClass<float, ImGuiDataType_Float, nlohmann::json::value_t::number_float>
 {
public:
    AttributeDescription_float() : DecimalNumberBaseClass(10,50,AttributeType::FLOAT, "NUMERIC") {}
    std::unique_ptr<AttributeDescription> clone() override;
 };

 struct AutoRegisterFloatDescription : public AutoRegisterDescription<AttributeDescription_float>
{
    inline static bool registerDescription = [] () { AutoRegisterDescription::autoRegister; };
};


class AttributeDescription_long : public IntegerNumberBaseClass<int, ImGuiDataType_S64, nlohmann::json::value_t::number_integer>
 {
public:
    AttributeDescription_long() : IntegerNumberBaseClass(10,50,AttributeType::LONG, "NUMERIC") {}
    std::unique_ptr<AttributeDescription> clone() override;
 };

 struct AutoRegisterLongDescription : public AutoRegisterDescription<AttributeDescription_long>
{
    inline static bool registerDescription = [] () { AutoRegisterDescription::autoRegister; };
};


class AttributeDescription_uint : public IntegerNumberBaseClass<uint, ImGuiDataType_U32, nlohmann::json::value_t::number_unsigned>
 {
public:
    AttributeDescription_uint() : IntegerNumberBaseClass(10,50,AttributeType::UINT, "NUMERIC") {}
    std::unique_ptr<AttributeDescription> clone() override;
 };

 struct AutoRegisterUintDescription : public AutoRegisterDescription<AttributeDescription_uint>
{
    inline static bool registerDescription = [] () { AutoRegisterDescription::autoRegister; };
};







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
    inline float getMinimum() { return min_; }
    inline float getMaximum() { return max_; }
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
