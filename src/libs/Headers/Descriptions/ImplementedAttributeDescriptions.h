#pragma once

#include "json.hpp"
#include "DescriptionFactory.h"
#include "AttributesDescriptionsContainer.h"

#include <string>
#include <variant>
#include <memory>
#include <iostream>

/// Base class for integer-based attribute descriptions.
///
/// Provides minimum and maximum limits, JSON parsing, and filtering by type.
template <typename TypeT, AttributeType AttributeTypeEnumT,ImGuiDataType ImGuiDataTypeT ,nlohmann::ordered_json::value_t TypeEnumT>
class IntegerNumberBaseClass : public AttributeDescription
{
private:
    TypeT min_;
    TypeT max_;

public:
    /// Construct an integer attribute description with default min/max and category.
    IntegerNumberBaseClass(TypeT min, TypeT max, Category category) : AttributeDescription(AttributeTypeEnumT), min_(min), max_(max)
    {
        dataType_ = ImGuiDataTypeT;
        category_ = category;
    }

    /// Get the current minimum limit.
    TypeT getMinimum() { return min_; }

    /// Get the current maximum limit.
    TypeT getMaximum() { return max_; }

    /// Update the numeric limits and record any validation messages.
    bool setLimit(TypeT minimum, TypeT maximum, std::vector<Message> *messagesHistory);

    /// Parse this attribute from JSON and report parse errors.
    bool jsonParse(nlohmann::ordered_json &json, std::vector<Message> *messagesHistory) override;

    /// Add this description to the provided collection when the type matches.
    void addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type) override;

    /// Integer-based attributes do not provide a nested container.
    AttributesDescriptionsContainer *getContainer(std::string_view descriptionName, uint64_t descriptionId) override { return nullptr; }

    /// Draw ImGui inputs for changing limits and return whether anything changed.
    bool drawInputForChangingLimits(std::vector<Message> *messagesHistory) override;
};

/// Base class for decimal-based attribute descriptions.
///
/// Provides floating-point limits, JSON parsing, and type-based filtering.
template <typename TypeT, AttributeType AttributeTypeEnumT,ImGuiDataType ImGuiDataTypeT ,nlohmann::ordered_json::value_t TypeEnumT>
class DecimalNumberBaseClass : public AttributeDescription
{
private:
    TypeT min_;
    TypeT max_;

public:
    /// Construct a decimal attribute description with default min/max and category.
    DecimalNumberBaseClass(TypeT min, TypeT max, Category category) : AttributeDescription(AttributeTypeEnumT), min_(min), max_(max)
    {
        dataType_ = ImGuiDataTypeT;
        category_ = category;
    }

    /// Get the current minimum limit.
    TypeT getMinimum() { return min_; }

    /// Get the current maximum limit.
    TypeT getMaximum() { return max_; }

    /// Update the numeric limits and record any validation messages.
    bool setLimit(TypeT minimum, TypeT maximum, std::vector<Message> *messagesHistory);

    /// Parse this attribute from JSON and report parse errors.
    bool jsonParse(nlohmann::ordered_json &json, std::vector<Message> *messagesHistory) override;

    /// Add this description to the provided collection when the type matches.
    void addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type) override;

    /// Decimal-based attributes do not provide a nested container.
    AttributesDescriptionsContainer *getContainer(std::string_view descriptionName, uint64_t descriptionId) override { return nullptr; }

    /// Draw ImGui inputs for changing limits and return whether anything changed.
    bool drawInputForChangingLimits(std::vector<Message> *messagesHistory) override;
};

/// Helper used to automatically register attribute description prototypes.
///
/// When instantiated, this struct registers one prototype with the global DescFactory.
template <typename AttributeDescriptionType>
struct AutoRegisterDescription
{
    inline static bool autoRegister = []()
    {
        DescFactory::getInstance()->registerPrototype(std::make_unique<AttributeDescriptionType>());
        return true;
    }();
};

/// Concrete INT attribute description with numeric limits and cloning support.
class AttributeDescriptionInt : public IntegerNumberBaseClass<int, AttributeType::INT,ImGuiDataType_S32,nlohmann::ordered_json::value_t::number_integer>
{
public:
    AttributeDescriptionInt() : IntegerNumberBaseClass(10, 50, Category::NUMERIC) {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterIntDescription : public AutoRegisterDescription<AttributeDescriptionInt>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescriptionDouble : public DecimalNumberBaseClass<double, AttributeType::DOUBLE,ImGuiDataType_Double,nlohmann::ordered_json::value_t::number_float>
{
public:
    AttributeDescriptionDouble() : DecimalNumberBaseClass(10, 50, Category::NUMERIC) {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterDoubleDescription : public AutoRegisterDescription<AttributeDescriptionDouble>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescriptionFloat : public DecimalNumberBaseClass<float, AttributeType::FLOAT,ImGuiDataType_Float ,nlohmann::ordered_json::value_t::number_float>
{
public:
    AttributeDescriptionFloat() : DecimalNumberBaseClass(10, 50, Category::NUMERIC) {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterFloatDescription : public AutoRegisterDescription<AttributeDescriptionFloat>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescriptionLong : public IntegerNumberBaseClass<long, AttributeType::LONG,ImGuiDataType_S64 ,nlohmann::ordered_json::value_t::number_integer>
{
public:
    AttributeDescriptionLong() : IntegerNumberBaseClass(10, 50, Category::NUMERIC) {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterLongDescription : public AutoRegisterDescription<AttributeDescriptionLong>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescriptionUint : public IntegerNumberBaseClass<uint32_t, AttributeType::UINT,ImGuiDataType_U32 ,nlohmann::ordered_json::value_t::number_unsigned>
{
public:
    AttributeDescriptionUint() : IntegerNumberBaseClass(10, 50, Category::NUMERIC) {}
    std::unique_ptr<AttributeDescription> clone() override;
};

struct AutoRegisterUintDescription : public AutoRegisterDescription<AttributeDescriptionUint>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};

class AttributeDescriptionCharNumber : public IntegerNumberBaseClass<char, AttributeType::CHARN,ImGuiDataType_U8 ,nlohmann::ordered_json::value_t::number_integer>
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

/// Concrete BOOL attribute description used for logical values.
class AttributeDescriptionBool : public AttributeDescription
{
public:
    AttributeDescriptionBool() : AttributeDescription(AttributeType::BOOL)
    {
        category_ = Category::LOGIC;
    }

    /// Parse a boolean attribute from JSON.
    bool jsonParse(nlohmann::ordered_json &json, std::vector<Message> *messagesHistory) override;

    /// Clone this boolean attribute description.
    std::unique_ptr<AttributeDescription> clone() override;

    /// Add this description to the provided collection when the type matches.
    void addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type) override;

    /// BOOL attributes do not provide a nested container.
    AttributesDescriptionsContainer *getContainer(std::string_view descriptionName, uint64_t descriptionId) override { return nullptr; }

    /// No limit-changing UI for boolean attributes.
    bool drawInputForChangingLimits(std::vector<Message> *messagesHistory) override { return false; }
    
};

struct AutoRegisterBoolDescription : public AutoRegisterDescription<AttributeDescriptionBool>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};






/// Concrete CLUSTER attribute description containing nested attribute descriptions.
class AttributeDescriptionCluster : public AttributeDescription
{
private:
    std::unique_ptr<AttributesDescriptionsContainer> descriptions_;

public:
    AttributeDescriptionCluster() : AttributeDescription(AttributeType::CLUSTER)
    {
        descriptions_ = std::make_unique<AttributesDescriptionsContainer>();
        category_ = Category::OTHER;
    }

    /// Deep copy constructor for nested descriptions.
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

    /// Ensure the nested description container exists and return it.
    AttributesDescriptionsContainer *getDescription()
    {
        if (descriptions_ == nullptr)
        {
            descriptions_ = std::make_unique<AttributesDescriptionsContainer>();
        }
        return descriptions_.get();
    }

public:
    /// Clone this cluster attribute description including its nested descriptions.
    std::unique_ptr<AttributeDescription> clone() override;

    /// Parse a cluster from JSON and populate nested descriptions.
    bool jsonParse(nlohmann::ordered_json &json, std::vector<Message> *messagesHistory) override;

    /// Add this description to the provided collection when the type matches.
    void addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type) override;

    /// Return a nested container by description name and identifier.
    AttributesDescriptionsContainer *getContainer(std::string_view descriptionName, uint64_t descriptionId) override;

    /// Clean up the cluster container.
    ~AttributeDescriptionCluster() override;

    /// Add a new child description by type and name.
    AttributeDescription* addDescription(std::string attributeName, AttributeType type);

    /// Add an existing child description to this cluster.
    AttributeDescription* addDescription(std::unique_ptr<AttributeDescription> attributeDescription);

    /// No limit-changing UI for cluster descriptions.
    bool drawInputForChangingLimits(std::vector<Message> *messagesHistory) override { return false; }
};

struct AutoRegisterClusterDescription : public AutoRegisterDescription<AttributeDescriptionCluster>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};





/// Concrete CHAR TEXT attribute description with character limit support.
class AttributeDescriptionCharText : public AttributeDescription
{
private:
    uint8_t min_;
    uint8_t max_;

public:
    AttributeDescriptionCharText() : AttributeDescription(AttributeType::CHART)
    {
        category_ = Category::TEXT;
    }

    /// Get the minimum character count.
    char getMinimum() { return min_; }

    /// Get the maximum character count.
    char getMaximum() { return max_; }

    /// Clone this character text description.
    std::unique_ptr<AttributeDescription> clone() override;

    /// Update the min/max limits and record validation messages.
    bool setLimit(uint8_t minimum, uint8_t maximum, std::vector<Message> *messagesHistory);

    /// Parse this char text description from JSON.
    bool jsonParse(nlohmann::ordered_json &json, std::vector<Message> *messagesHistory) override;

    /// Add this description to the provided collection when the type matches.
    void addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type) override;

    /// CHAR TEXT attributes do not provide a nested container.
    AttributesDescriptionsContainer *getContainer(std::string_view descriptionName, uint64_t descriptionId) override { return nullptr; }

    /// Draw ImGui inputs for changing the character limits.
    bool drawInputForChangingLimits(std::vector<Message> *messagesHistory) override;
};

struct AutoRegisterCharTextDescription : public AutoRegisterDescription<AttributeDescriptionCharText>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};






/// Concrete STRING attribute description with string length limits.
class AttributeDescriptionString : public AttributeDescription
{
private:
    uint32_t min_;
    uint32_t max_;

public:
    AttributeDescriptionString() : AttributeDescription(AttributeType::STRING)
    {
        category_ = Category::TEXT;
    }

    /// Get the minimum string length.
    uint32_t getMinimum() { return min_; }

    /// Get the maximum string length.
    uint32_t getMaximum() { return max_; }

    /// Clone this string attribute description.
    std::unique_ptr<AttributeDescription> clone() override;

    /// Update the string length limits and record validation messages.
    bool setLimit(uint32_t minimum, uint32_t maximum, std::vector<Message> *messagesHistory);

    /// Parse this string description from JSON.
    bool jsonParse(nlohmann::ordered_json &json, std::vector<Message> *messagesHistory) override;

    /// Add this description to the provided collection when the type matches.
    void addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type) override;

    /// STRING attributes do not provide a nested container.
    AttributesDescriptionsContainer *getContainer(std::string_view descriptionName, uint64_t descriptionId) override { return nullptr; }

    /// Draw ImGui inputs for changing the string length limits.
    bool drawInputForChangingLimits(std::vector<Message> *messagesHistory) override;
};

struct AutoRegisterStringDescription : public AutoRegisterDescription<AttributeDescriptionString>
{
    inline static bool registerDescription = []()
    { AutoRegisterDescription::autoRegister; };
};





