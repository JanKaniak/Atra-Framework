#pragma once

#include "json.hpp"
#include "DescriptionFactory.h"


#include <string>
#include <variant>
#include <memory>
#include <iostream>

template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
class IntegerNumberBaseClass : public AttributeDescription
{
private:
    TypeT min_;
    TypeT max_;


public:
    IntegerNumberBaseClass(TypeT min, TypeT max, AttributeType attributeType, std::string category) : AttributeDescription(attributeType), min_(min), max_(max)
    {
        category_ = category;
        dataType_ = ImGuiDataTypeT;
    }

    constexpr TypeT getMinimum() { return min_; }
    constexpr TypeT getMaximum() { return max_; }
    bool setLimit(TypeT minimum, TypeT maximum, std::vector<Message>& messagesHistory);
    bool jsonParse(nlohmann::ordered_json &json, std::vector<Message>& messagesHistory) override;
    void drawInputForChangingLimits(std::vector<Message>& messagesHistory) override;
};

template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
class DecimalNumberBaseClass : public AttributeDescription
{
private:
    TypeT min_;
    TypeT max_;

public:
    DecimalNumberBaseClass(TypeT min, TypeT max, AttributeType attributeType, std::string category) : AttributeDescription(attributeType), min_(min), max_(max)
    {
        category_ = category;
        dataType_ = ImGuiDataTypeT;
    }

    constexpr TypeT getMinimum() { return min_; }
    constexpr TypeT getMaximum() { return max_; }
    bool setLimit(TypeT minimum, TypeT maximum, std::vector<Message>& messagesHistory);
    bool jsonParse(nlohmann::ordered_json &json, std::vector<Message>& messagesHistory) override;
    void drawInputForChangingLimits(std::vector<Message>& messagesHistory) override;
};

template <typename AttributeDescriptionType>
struct AutoRegisterDescription
{
    inline static bool autoRegister = []()
    {
        DescFactory::getInstance()->registerPrototype(std::make_unique<AttributeDescriptionType>());
        return true;
    }();
};

class AttributeDescription_int : public IntegerNumberBaseClass<int, ImGuiDataType_S32, nlohmann::json::value_t::number_integer>
{
public:
    AttributeDescription_int() : IntegerNumberBaseClass(10, 50, AttributeType::INT, "NUMERIC") {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterIntDescription : public AutoRegisterDescription<AttributeDescription_int>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescription_double : public DecimalNumberBaseClass<double, ImGuiDataType_Double, nlohmann::json::value_t::number_float>
{
public:
    AttributeDescription_double() : DecimalNumberBaseClass(10, 50, AttributeType::DOUBLE, "NUMERIC") {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterDoubleDescription : public AutoRegisterDescription<AttributeDescription_double>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescription_float : public DecimalNumberBaseClass<float, ImGuiDataType_Float, nlohmann::json::value_t::number_float>
{
public:
    AttributeDescription_float() : DecimalNumberBaseClass(10, 50, AttributeType::FLOAT, "NUMERIC") {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterFloatDescription : public AutoRegisterDescription<AttributeDescription_float>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescription_long : public IntegerNumberBaseClass<int, ImGuiDataType_S64, nlohmann::json::value_t::number_integer>
{
public:
    AttributeDescription_long() : IntegerNumberBaseClass(10, 50, AttributeType::LONG, "NUMERIC") {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterLongDescription : public AutoRegisterDescription<AttributeDescription_long>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescription_uint : public IntegerNumberBaseClass<uint, ImGuiDataType_U32, nlohmann::json::value_t::number_unsigned>
{
public:
    AttributeDescription_uint() : IntegerNumberBaseClass(10, 50, AttributeType::UINT, "NUMERIC") {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterUintDescription : public AutoRegisterDescription<AttributeDescription_uint>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescription_char : public IntegerNumberBaseClass<char,ImGuiDataType_S8,nlohmann::json::value_t::number_integer>
{
private:
    int min_;
    int max_;

public:
    AttributeDescription_char() : IntegerNumberBaseClass(10,50,AttributeType::CHAR, "NUMERIC") {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterCharDescription : public AutoRegisterDescription<AttributeDescription_char>
{
    inline static bool registerDescription = []()
    {
        AutoRegisterDescription::autoRegister; };
};

class AttributeDescription_bool : public AttributeDescription {
    public:
        AttributeDescription_bool() : AttributeDescription(AttributeType::BOOL) {
            category_ = "LOGIC";
        }
        bool jsonParse(nlohmann::ordered_json &json, std::vector<Message>& messagesHistory) override;
        std::unique_ptr<AttributeDescription> clone() override;

    private:
        void drawInputForChangingLimits(std::vector<Message>& messagesHistory) override {}
};

struct AutoRegisterBoolDescription : public AutoRegisterDescription<AttributeDescription_bool>
{
    inline static bool registerDescription = []()
    {
        AutoRegisterDescription::autoRegister; };
};
