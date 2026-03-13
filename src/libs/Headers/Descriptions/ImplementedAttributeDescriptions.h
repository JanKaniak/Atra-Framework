#pragma once

#include "json.hpp"
#include "DescriptionFactory.h"
#include "AttributeDescriptionsContainer.h"

#include <string>
#include <variant>
#include <memory>
#include <iostream>

template <typename TypeT, AttributeType AttributeTypeEnumT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
class IntegerNumberBaseClass : public AttributeDescription
{
private:
    TypeT min_;
    TypeT max_;

public:
    IntegerNumberBaseClass(TypeT min, TypeT max, std::string category) : AttributeDescription(AttributeTypeEnumT), min_(min), max_(max)
    {
        category_ = category;
        dataType_ = ImGuiDataTypeT;
        assigned_ = false;
    }

    constexpr TypeT getMinimum() { return min_; }
    constexpr TypeT getMaximum() { return max_; }
    bool setLimit(TypeT minimum, TypeT maximum, std::vector<Message> &messagesHistory);
    bool jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) override;
    bool drawInputForChangingLimits(std::vector<Message> &messagesHistory) override;
    void addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type) override;
    AttributeDescriptionsContainer* getContainer(std::string_view descriptionName) override { return nullptr;}
};

template <typename TypeT, AttributeType AttributeTypeEnumT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
class DecimalNumberBaseClass : public AttributeDescription
{
private:
    TypeT min_;
    TypeT max_;

public:
    DecimalNumberBaseClass(TypeT min, TypeT max, std::string category) : AttributeDescription(AttributeTypeEnumT), min_(min), max_(max)
    {
        category_ = category;
        dataType_ = ImGuiDataTypeT;
        assigned_ = false;
    }

    constexpr TypeT getMinimum() { return min_; }
    constexpr TypeT getMaximum() { return max_; }
    bool setLimit(TypeT minimum, TypeT maximum, std::vector<Message> &messagesHistory);
    bool jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) override;
    bool drawInputForChangingLimits(std::vector<Message> &messagesHistory) override;
    void addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type) override;
    AttributeDescriptionsContainer* getContainer(std::string_view descriptionName) override { return nullptr;}
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

class AttributeDescription_int : public IntegerNumberBaseClass<int, AttributeType::INT, ImGuiDataType_S32, nlohmann::json::value_t::number_integer>
{
public:
    AttributeDescription_int() : IntegerNumberBaseClass(10, 50, "NUMERIC") {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterIntDescription : public AutoRegisterDescription<AttributeDescription_int>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescription_double : public DecimalNumberBaseClass<double, AttributeType::DOUBLE, ImGuiDataType_Double, nlohmann::json::value_t::number_float>
{
public:
    AttributeDescription_double() : DecimalNumberBaseClass(10, 50, "NUMERIC") {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterDoubleDescription : public AutoRegisterDescription<AttributeDescription_double>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescription_float : public DecimalNumberBaseClass<float, AttributeType::FLOAT, ImGuiDataType_Float, nlohmann::json::value_t::number_float>
{
public:
    AttributeDescription_float() : DecimalNumberBaseClass(10, 50, "NUMERIC") {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterFloatDescription : public AutoRegisterDescription<AttributeDescription_float>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescription_long : public IntegerNumberBaseClass<int, AttributeType::LONG, ImGuiDataType_S64, nlohmann::json::value_t::number_integer>
{
public:
    AttributeDescription_long() : IntegerNumberBaseClass(10, 50, "NUMERIC") {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterLongDescription : public AutoRegisterDescription<AttributeDescription_long>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescription_uint : public IntegerNumberBaseClass<uint, AttributeType::UINT, ImGuiDataType_U32, nlohmann::json::value_t::number_unsigned>
{
public:
    AttributeDescription_uint() : IntegerNumberBaseClass(10, 50, "NUMERIC") {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterUintDescription : public AutoRegisterDescription<AttributeDescription_uint>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescription_char : public IntegerNumberBaseClass<char, AttributeType::CHAR, ImGuiDataType_S8, nlohmann::json::value_t::number_integer>
{
private:
    int min_;
    int max_;

public:
    AttributeDescription_char() : IntegerNumberBaseClass(10, 50, "NUMERIC") {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterCharDescription : public AutoRegisterDescription<AttributeDescription_char>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescription_bool : public AttributeDescription
{
public:
    AttributeDescription_bool() : AttributeDescription(AttributeType::BOOL)
    {
        category_ = "LOGIC";
        assigned_ = false;
    }
    bool jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) override;
    std::unique_ptr<AttributeDescription> clone() override;
    void addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type) override;
    AttributeDescriptionsContainer* getContainer(std::string_view descriptionName) override { return nullptr;}

private:
    bool drawInputForChangingLimits(std::vector<Message> &messagesHistory) override { return false; }
};

struct AutoRegisterBoolDescription : public AutoRegisterDescription<AttributeDescription_bool>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescriptionCluster : public AttributeDescription
{
private:
    int min_;
    int max_;
    std::unique_ptr<AttributeDescriptionsContainer> descriptions_;

public:
    AttributeDescriptionCluster() : AttributeDescription(AttributeType::CLUSTER)
    {
        descriptions_ = std::make_unique<AttributeDescriptionsContainer>();
        category_ = "OTHER";
        assigned_ = false;
    }

    AttributeDescriptionCluster(const AttributeDescriptionCluster &descriptionCluster) : AttributeDescription(AttributeType::CLUSTER)
    {
        descriptions_ = std::make_unique<AttributeDescriptionsContainer>();
        category_ = descriptionCluster.category_;
        assigned_ = false;
    }

    int getMinimum() { return min_; }
    int getMaximum() { return max_; }
    AttributeDescriptionsContainer *getDescription()
    {
        if (descriptions_ == nullptr)
        {
            descriptions_ = std::make_unique<AttributeDescriptionsContainer>();
        }
        return descriptions_.get();
    }

public:
    std::unique_ptr<AttributeDescription> clone() override;
    bool jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) override;
    bool drawInputForChangingLimits(std::vector<Message> &messagesHistory) override;
    void addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type) override;
    AttributeDescriptionsContainer* getContainer(std::string_view descriptionName) override;
    ~AttributeDescriptionCluster() override;
};

struct AutoRegisterClusterDescription : public AutoRegisterDescription<AttributeDescriptionCluster>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};
