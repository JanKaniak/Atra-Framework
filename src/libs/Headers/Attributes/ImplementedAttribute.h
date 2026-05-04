#pragma once
#include "AttributeFactory.h"

#include <format>

/// Base attribute class for integral values with min/max bounds.
///
/// Uses an attribute description to determine valid bounds and serialization behavior.
template <typename TypeT, typename AttributeDescriptionT>
class IntegerNumberBaseAttributeClass : public Attribute
{
private:
    TypeT value_;
    AttributeDescriptionT *desc_;

public:
    IntegerNumberBaseAttributeClass() {}
    std::string getName() override { return desc_->getName(); }
    AttributeType getType() override { return desc_->getType(); }
    AttributeDescription *getDescription() override { return desc_; }
    inline const TypeT getMinimum() { return desc_->getMinimum(); }
    inline const TypeT getMaximum() { return desc_->getMaximum(); }

    /// Set the current integer value if it is within description bounds.
    bool setValue(TypeT value)
    {
        if (value >= getMinimum() && value <= getMaximum())
        {
            value_ = value;
            return true;
        }
        return false;
    }

    /// Assign a description to this attribute and initialize the value.
    void setDescription(AttributeDescription *desc, std::vector<Message> &messagesHistory) override
    {
        if (dynamic_cast<AttributeDescriptionT *>(desc))
        {
            desc_ = dynamic_cast<AttributeDescriptionT *>(desc);
            value_ = desc_->getMinimum();
        }
    }
    TypeT getValue() { return value_; }
    bool saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) override;

    /// Create UI controls for editing this integer attribute.
    void controlOptions(int position, ControlComponentsContainer *components, ControlComponentsFactoriesContainer *controlComponentsFactories, std::vector<Message> &messagesHistory) override;
    ~IntegerNumberBaseAttributeClass() override = default;

    /// Reset the value to the minimum defined by the description.
    void updateValue() override {
        value_ = getMinimum();
    }
};

/// Base attribute class for decimal values with min/max bounds.
///
/// Uses a description object for bounds and serialization behavior.
template <typename TypeT, typename AttributeDescriptionT>
class DecimalNumberBaseAttributeClass : public Attribute
{
private:
    TypeT value_;
    AttributeDescriptionT *desc_;

public:
    DecimalNumberBaseAttributeClass() {}
    std::string getName() override { return desc_->getName(); }
    AttributeType getType() override { return desc_->getType(); }
    AttributeDescription *getDescription() override { return desc_; }
    inline const TypeT getMinimum() { return desc_->getMinimum(); }
    inline const TypeT getMaximum() { return desc_->getMaximum(); }

    /// Set the current decimal value if it is within bounds.
    bool setValue(TypeT value)
    {
        if (value >= getMinimum() && value <= getMaximum())
        {
            value_ = value;
            return true;
        }
        return false;
    }

    /// Assign a description to this attribute and initialize the value.
    void setDescription(AttributeDescription *desc, std::vector<Message> &messagesHistory) override
    {
        if (dynamic_cast<AttributeDescriptionT *>(desc))
        {
            desc_ = dynamic_cast<AttributeDescriptionT *>(desc);
            value_ = desc_->getMinimum();
        }
    }
    TypeT getValue() { return value_; }
    bool saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) override;

    /// Create UI controls for editing this decimal attribute.
    void controlOptions(int position, ControlComponentsContainer *components, ControlComponentsFactoriesContainer *controlComponentsFactories, std::vector<Message> &messagesHistory) override;
    ~DecimalNumberBaseAttributeClass() override = default;

    /// Clamp the current value to the valid description bounds.
    void updateValue() override {
        if (value_ > getMaximum()) {
            value_ = getMaximum();
        } else if (value_ < getMinimum()) {
            value_ = getMinimum();
        }
    }
};

/// Helper used to automatically register attribute prototypes with the factory.
///
/// Each instantiation registers a single concrete attribute type.
template <typename AttributeTypeClass, AttributeType EnumTypeT>
struct AutoRegisterAttribute
{
    inline static bool autoRegisterAttribute = []()
    {
        AttributeFactory::getInstance()->registerPrototype<EnumTypeT>(std::make_unique<AttributeTypeClass>());
        return true;
    }();
};

/// Concrete integer attribute implementation for INT descriptions.
class AttributeInt : public IntegerNumberBaseAttributeClass<int, AttributeDescriptionInt>
{
public:
    AttributeInt() : IntegerNumberBaseAttributeClass() {}
    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeInt>(*this); }
};

struct AutoRegisterIntAttribute : public AutoRegisterAttribute<AttributeInt, AttributeType::INT>
{
    inline static bool autoRegister = []()
    {
        AutoRegisterAttribute::autoRegisterAttribute;
    };
};

/// Concrete double attribute implementation for DOUBLE descriptions.
class AttributeDouble : public DecimalNumberBaseAttributeClass<double, AttributeDescriptionDouble>
{
public:
    AttributeDouble() : DecimalNumberBaseAttributeClass() {};
    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeDouble>(*this); }
};

struct AutoRegisterDoubleAttribute : public AutoRegisterAttribute<AttributeDouble, AttributeType::DOUBLE>
{
    inline static bool registerDoubleAttribute = []()
    {
        AutoRegisterAttribute::autoRegisterAttribute;
    };
};

/// Concrete float attribute implementation for FLOAT descriptions.
class AttributeFloat : public DecimalNumberBaseAttributeClass<float, AttributeDescriptionFloat>
{
public:
    AttributeFloat() : DecimalNumberBaseAttributeClass() {};
    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeFloat>(*this); }
};

struct AutoRegisterFloatAttribute : public AutoRegisterAttribute<AttributeFloat, AttributeType::FLOAT>
{
    inline static bool registerFloatAttribute = []()
    {
        AutoRegisterAttribute::autoRegisterAttribute;
    };
};

/// Concrete unsigned integer attribute implementation for UINT descriptions.
class AttributeUint : public IntegerNumberBaseAttributeClass<uint32_t, AttributeDescriptionUint>
{
public:
    AttributeUint() : IntegerNumberBaseAttributeClass() {};
    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeUint>(*this); }
};

struct AutoRegisterUintAttribute : public AutoRegisterAttribute<AttributeUint, AttributeType::UINT>
{
    inline static bool registerUintAttribute = []()
    {
        AutoRegisterAttribute::autoRegisterAttribute;
    };
};

/// Concrete long integer attribute implementation for LONG descriptions.
class AttributeLong : public IntegerNumberBaseAttributeClass<long, AttributeDescriptionLong>
{
public:
    AttributeLong() : IntegerNumberBaseAttributeClass() {};
    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeLong>(*this); }
};

struct AutoRegisterLongAttribute : public AutoRegisterAttribute<AttributeLong, AttributeType::LONG>
{
    inline static bool registerLongAttribute = []()
    {
        AutoRegisterAttribute::autoRegisterAttribute;
    };
};

/// Concrete character number attribute implementation for CHARN descriptions.
class AttributeCharNumber : public IntegerNumberBaseAttributeClass<char, AttributeDescriptionCharNumber>
{
public:
    AttributeCharNumber() : IntegerNumberBaseAttributeClass() {};
    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeCharNumber>(*this); }
};

struct AutoRegisterCharNumberAttribute : public AutoRegisterAttribute<AttributeCharNumber, AttributeType::CHARN>
{
    inline static bool registerCharAttribute = []()
    {
        AutoRegisterAttribute::autoRegisterAttribute;
    };
};

/// Concrete attribute implementation for character text values.
///
/// Uses `AttributeDescriptionCharText` to enforce valid char boundaries and serialization.
class AttributeCharText : public Attribute
{
private:
    unsigned char value_;
    AttributeDescriptionCharText *desc_;

public:
    AttributeCharText() {}
    std::string getName() override { return desc_->getName(); }
    AttributeType getType() override { return desc_->getType(); }
    AttributeDescription *getDescription() override { return desc_; }
    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeCharText>(*this); }
    inline const uint8_t getMinimum() { return desc_->getMinimum(); }
    inline const uint8_t getMaximum() { return desc_->getMaximum(); }

    /// Set the character value only if it lies within the allowed range.
    bool setValue(char value)
    {
        if (sizeof(value) >= getMinimum() && sizeof(value) <= getMaximum())
        {
            value_ = value;
            return true;
        }
        return false;
    }

    /// Attach the matching char text description and initialize the value.
    void setDescription(AttributeDescription *desc, std::vector<Message> &messagesHistory) override
    {
        if (dynamic_cast<AttributeDescriptionCharText *>(desc))
        {
            desc_ = dynamic_cast<AttributeDescriptionCharText *>(desc);
            value_ = desc_->getMinimum();
        }
    }
    char getValue() { return value_; }
    bool saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) override;

    void controlOptions(int position, ControlComponentsContainer *components, ControlComponentsFactoriesContainer *controlComponentsFactories, std::vector<Message> &messagesHistory) override;
    ~AttributeCharText() override = default;
    void updateValue() override {}
};

struct AutoRegisterCharTextAttribute : public AutoRegisterAttribute<AttributeCharText, AttributeType::CHART>
{
    inline static bool registerCharAttribute = []()
    {
        AutoRegisterAttribute::autoRegisterAttribute;
    };
};

/// Concrete boolean attribute implementation.
///
/// Stores a boolean value and exposes UI/control integration via the description.
class AttributeBool : public Attribute
{
private:
    bool value_;
    AttributeDescriptionBool *desc_;

public:
    AttributeBool() {}
    std::string getName() override { return desc_->getName(); }
    AttributeType getType() override { return desc_->getType(); }
    AttributeDescription *getDescription() override { return desc_; }
    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeBool>(*this); }

    /// Bind the bool description and initialize the value to false.
    void setDescription(AttributeDescription *desc, std::vector<Message> &messagesHistory) override
    {
        if (dynamic_cast<AttributeDescriptionBool *>(desc))
        {
            desc_ = dynamic_cast<AttributeDescriptionBool *>(desc);
            value_ = false;
        }
    }
    bool saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) override;

    bool setValue(bool value)
    {
        value_ = value;
        return true;
    }
    bool getValue() { return value_; }
    void controlOptions(int position, ControlComponentsContainer *components, ControlComponentsFactoriesContainer *controlComponentsFactories, std::vector<Message> &messagesHistory) override;
    ~AttributeBool() override = default;
    void updateValue() override {}
};

struct AutoRegisterBoolAttribute : public AutoRegisterAttribute<AttributeBool, AttributeType::BOOL>
{
    inline static bool registerBoolAttribute = []()
    {
        AutoRegisterAttribute::autoRegisterAttribute;
    };
};

class AttributesContainer;

/// Attribute wrapper for a nested cluster of attributes.
///
/// Contains a child `AttributesContainer` and delegates description/serialization to it.
class AttributeCluster : public Attribute
{
private:
    std::unique_ptr<AttributesContainer> value_;
    AttributeDescriptionCluster *desc_;

public:
    /// Construct an empty cluster attribute.
    AttributeCluster();

    /// Copy constructor clones the contained attribute container.
    AttributeCluster(const AttributeCluster &attributeCluster);

    /// Access the nested attributes container held by this cluster.
    AttributesContainer *getAttributeContainer();

    ~AttributeCluster() override;

public:
    std::string getName() override { return desc_->getName(); }
    AttributeType getType() override { return desc_->getType(); }
    AttributeDescription *getDescription() override { return desc_; }

    /// Clone this cluster attribute, including its nested attribute container.
    std::unique_ptr<Attribute> clone() override;

    /// Attach the cluster description and build the inner attribute container.
    void setDescription(AttributeDescription *desc, std::vector<Message> &messagesHistory) override;

    /// Serialize the nested cluster contents into JSON.
    bool saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) override;

    /// Create UI controls for the nested cluster contents.
    void controlOptions(int position, ControlComponentsContainer *components, ControlComponentsFactoriesContainer *controlComponentsFactories, std::vector<Message> &messagesHistory) override;
    void updateValue() override {}
};

/// Declaration placeholder for the cluster auto-registration helper.
struct AutoRegisterClusterAttribute;

/// Concrete string attribute implementation for text values.
///
/// Uses `AttributeDescriptionString` to enforce min/max length and manage serialization.
class AttributeString : public Attribute
{
private:
    std::string value_;
    AttributeDescriptionString *desc_;

public:
    AttributeString() {}
    std::string getName() override { return desc_->getName(); }
    AttributeType getType() override { return desc_->getType(); }
    uint32_t getMinimum() { return desc_->getMinimum(); }
    uint32_t getMaximum() { return desc_->getMaximum(); }
    AttributeDescription *getDescription() override { return desc_; }
    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeString>(*this); }

    /// Bind the string description and reset to an empty string.
    void setDescription(AttributeDescription *desc, std::vector<Message> &messagesHistory) override
    {
        if (dynamic_cast<AttributeDescriptionString *>(desc))
        {
            desc_ = dynamic_cast<AttributeDescriptionString *>(desc);
            value_ = "";
        }
    }
    bool saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) override;

    /// Set the string value only if length fits within bounds.
    bool setValue(std::string value)
    {
        if (value.length() >= desc_->getMinimum() && value.length() <= desc_->getMaximum())
        {
            value_ = value;
            return true;
        }
        return false;
    }
    std::string getValue() { return value_; }
    void controlOptions(int position, ControlComponentsContainer *components, ControlComponentsFactoriesContainer *controlComponentsFactories, std::vector<Message> &messagesHistory) override;
    ~AttributeString() override = default;

    /// Truncate the string if it exceeds the allowed maximum length.
    void updateValue() override {
        if (value_.length() > getMaximum()) {
            value_.resize(getMaximum());
        }
    }
};

struct AutoRegisterStringAttribute : public AutoRegisterAttribute<AttributeString, AttributeType::STRING>
{
    inline static bool registerStringAttribute = []()
    {
        AutoRegisterAttribute::autoRegisterAttribute;
    };
};