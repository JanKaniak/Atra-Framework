#pragma once

#include "json.hpp"
#include "DescriptionFactory.h"
#include "AttributesDescriptionsContainer.h"

#include <string>
#include <variant>
#include <memory>
#include <iostream>

template <typename TypeT, AttributeType AttributeTypeEnumT, ImGuiDataType ImGuiDataTypeT, nlohmann::ordered_json::value_t TypeEnumT>
class IntegerNumberBaseClass : public AttributeDescription
{
private:
    TypeT min_;
    TypeT max_;

public:
    IntegerNumberBaseClass(TypeT min, TypeT max, Category category) : AttributeDescription(AttributeTypeEnumT), min_(min), max_(max)
    {
        category_ = category;
        dataType_ = ImGuiDataTypeT;
    }

    constexpr TypeT getMinimum() { return min_; }
    constexpr TypeT getMaximum() { return max_; }
    bool setLimit(TypeT minimum, TypeT maximum, std::vector<Message> &messagesHistory);
    bool jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) override;
    bool drawInputForChangingLimits(std::vector<Message> &messagesHistory) override;
    void addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type) override;
    AttributesDescriptionsContainer *getContainer(std::string_view descriptionName, uint64_t descriptionId) override { return nullptr; }
};

template <typename TypeT, AttributeType AttributeTypeEnumT, ImGuiDataType ImGuiDataTypeT, nlohmann::ordered_json::value_t TypeEnumT>
class DecimalNumberBaseClass : public AttributeDescription
{
private:
    TypeT min_;
    TypeT max_;

public:
    DecimalNumberBaseClass(TypeT min, TypeT max, Category category) : AttributeDescription(AttributeTypeEnumT), min_(min), max_(max)
    {
        category_ = category;
        dataType_ = ImGuiDataTypeT;
    }

    constexpr TypeT getMinimum() { return min_; }
    constexpr TypeT getMaximum() { return max_; }
    bool setLimit(TypeT minimum, TypeT maximum, std::vector<Message> &messagesHistory);
    bool jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) override;
    bool drawInputForChangingLimits(std::vector<Message> &messagesHistory) override;
    void addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type) override;
    AttributesDescriptionsContainer *getContainer(std::string_view descriptionName, uint64_t descriptionId) override { return nullptr; }
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

class AttributeDescription_int : public IntegerNumberBaseClass<int, AttributeType::INT, ImGuiDataType_S32, nlohmann::ordered_json::value_t::number_integer>
{
public:
    AttributeDescription_int() : IntegerNumberBaseClass(10, 50, Category::NUMERIC) {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterIntDescription : public AutoRegisterDescription<AttributeDescription_int>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescription_double : public DecimalNumberBaseClass<double, AttributeType::DOUBLE, ImGuiDataType_Double, nlohmann::ordered_json::value_t::number_float>
{
public:
    AttributeDescription_double() : DecimalNumberBaseClass(10, 50, Category::NUMERIC) {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterDoubleDescription : public AutoRegisterDescription<AttributeDescription_double>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescription_float : public DecimalNumberBaseClass<float, AttributeType::FLOAT, ImGuiDataType_Float, nlohmann::ordered_json::value_t::number_float>
{
public:
    AttributeDescription_float() : DecimalNumberBaseClass(10, 50, Category::NUMERIC) {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterFloatDescription : public AutoRegisterDescription<AttributeDescription_float>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescription_long : public IntegerNumberBaseClass<long, AttributeType::LONG, ImGuiDataType_S64, nlohmann::ordered_json::value_t::number_integer>
{
public:
    AttributeDescription_long() : IntegerNumberBaseClass(10, 50, Category::NUMERIC) {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterLongDescription : public AutoRegisterDescription<AttributeDescription_long>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescription_uint : public IntegerNumberBaseClass<uint32_t, AttributeType::UINT, ImGuiDataType_U32, nlohmann::ordered_json::value_t::number_unsigned>
{
public:
    AttributeDescription_uint() : IntegerNumberBaseClass(10, 50, Category::NUMERIC) {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterUintDescription : public AutoRegisterDescription<AttributeDescription_uint>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescriptionCharNumber : public IntegerNumberBaseClass<char, AttributeType::CHARN, ImGuiDataType_S8, nlohmann::ordered_json::value_t::number_integer>
{

public:
    AttributeDescriptionCharNumber() : IntegerNumberBaseClass(10, 50, Category::NUMERIC) {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterCharNumberDescription : public AutoRegisterDescription<AttributeDescriptionCharNumber>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescription_bool : public AttributeDescription
{
public:
    AttributeDescription_bool() : AttributeDescription(AttributeType::BOOL)
    {
        category_ = Category::LOGIC;
    }
    bool jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) override;
    std::unique_ptr<AttributeDescription> clone() override;
    void addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type) override;
    AttributesDescriptionsContainer *getContainer(std::string_view descriptionName, uint64_t descriptionId) override { return nullptr; }

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
    uint32_t min_;
    uint32_t max_;
    std::unique_ptr<AttributesDescriptionsContainer> descriptions_;

public:
    AttributeDescriptionCluster() : AttributeDescription(AttributeType::CLUSTER)
    {
        descriptions_ = std::make_unique<AttributesDescriptionsContainer>();
        category_ = Category::OTHER;
    }

    AttributeDescriptionCluster(const AttributeDescriptionCluster &descriptionCluster) : AttributeDescription(AttributeType::CLUSTER)
    {
        category_ = Category::OTHER;
        descriptions_ = std::make_unique<AttributesDescriptionsContainer>();
        for (int i = 0; i < descriptionCluster.descriptions_.get()->getSize(); ++i)
        {
            if (descriptionCluster.descriptions_->getDescription(i) != nullptr)
                descriptions_->addDescription(descriptionCluster.descriptions_->getDescription(i)->clone());
        }
    }

    uint32_t getMinimum() { return min_; }
    uint32_t getMaximum() { return max_; }
    AttributesDescriptionsContainer *getDescription()
    {
        if (descriptions_ == nullptr)
        {
            descriptions_ = std::make_unique<AttributesDescriptionsContainer>();
        }
        return descriptions_.get();
    }

public:
    std::unique_ptr<AttributeDescription> clone() override;
    bool jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) override;
    bool drawInputForChangingLimits(std::vector<Message> &messagesHistory) override;
    void addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type) override;
    AttributesDescriptionsContainer *getContainer(std::string_view descriptionName, uint64_t descriptionId) override;
    ~AttributeDescriptionCluster() override;
};

struct AutoRegisterClusterDescription : public AutoRegisterDescription<AttributeDescriptionCluster>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescriptionCharText : public AttributeDescription
{
private:
    uint8_t min_;
    uint8_t max_;

public:
    AttributeDescriptionCharText() : AttributeDescription(AttributeType::CHART)
    {
        category_ = Category::TEXT;
        dataType_ = ImGuiDataType_U8;
    }
    char getMinimum() { return min_; }
    char getMaximum() { return max_; }
    std::unique_ptr<AttributeDescription> clone() override;
    bool setLimit(uint8_t minimum, uint8_t maximum, std::vector<Message> &messagesHistory);
    bool jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) override;
    bool drawInputForChangingLimits(std::vector<Message> &messagesHistory) override;
    void addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type) override;
    AttributesDescriptionsContainer *getContainer(std::string_view descriptionName, uint64_t descriptionId) override { return nullptr; }
};

struct AutoRegisterCharTextDescription : public AutoRegisterDescription<AttributeDescriptionCharText>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescriptionString : public AttributeDescription
{
private:
    uint32_t min_;
    uint32_t max_;

public:
    AttributeDescriptionString() : AttributeDescription(AttributeType::STRING)
    {
        category_ = Category::TEXT;
        dataType_ = ImGuiDataType_U32;
    }
    uint32_t getMinimum() { return min_; }
    uint32_t getMaximum() { return max_; }
    std::unique_ptr<AttributeDescription> clone() override;
    bool setLimit(uint32_t minimum, uint32_t maximum, std::vector<Message> &messagesHistory);
    bool jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) override;
    bool drawInputForChangingLimits(std::vector<Message> &messagesHistory) override;
    void addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type) override;
    AttributesDescriptionsContainer *getContainer(std::string_view descriptionName, uint64_t descriptionId) override { return nullptr; }
};

struct AutoRegisterStringDescription : public AutoRegisterDescription<AttributeDescriptionString>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};