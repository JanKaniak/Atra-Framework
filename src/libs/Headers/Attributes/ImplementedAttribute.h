#pragma once
#include "AttributeFactory.h"

#include <format>

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
    bool setValue(TypeT value)
    {
        if (value >= getMinimum() && value <= getMaximum())
        {
            value_ = value;
            return true;
        }
        return false;
    }

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

    void controlOptions(int position, ControlComponentsContainer *components, ControlComponentsFactoriesContainer *controlComponentsFactories, std::vector<Message> &messagesHistory) override;
    ~IntegerNumberBaseAttributeClass() override = default;
};

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
    bool setValue(TypeT value)
    {
        if (value >= getMinimum() && value <= getMaximum())
        {
            value_ = value;
            return true;
        }
        return false;
    }

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

    void controlOptions(int position, ControlComponentsContainer *components, ControlComponentsFactoriesContainer *controlComponentsFactories, std::vector<Message> &messagesHistory) override;
    ~DecimalNumberBaseAttributeClass() override = default;
};

template <typename AttributeTypeClass, AttributeType EnumTypeT>
struct AutoRegisterAttribute
{
    inline static bool autoRegisterAttribute = []()
    {
        AttributeFactory::getInstance()->registerPrototype<EnumTypeT>(std::make_unique<AttributeTypeClass>());
        return true;
    }();
};

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

class AttributeCharText : public Attribute
{
private:
    char value_;
    AttributeDescriptionCharText *desc_;

public:
    AttributeCharText() {}
    std::string getName() override { return desc_->getName(); }
    AttributeType getType() override { return desc_->getType(); }
    AttributeDescription *getDescription() override { return desc_; }
    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeCharText>(*this); }
    inline const uint8_t getMinimum() { return desc_->getMinimum(); }
    inline const uint8_t getMaximum() { return desc_->getMaximum(); }
    bool setValue(char value)
    {
        if (sizeof(value) >= getMinimum() && sizeof(value) <= getMaximum())
        {
            value_ = value;
            return true;
        }
        return false;
    }

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
};

struct AutoRegisterCharTextAttribute : public AutoRegisterAttribute<AttributeCharText, AttributeType::CHART>
{
    inline static bool registerCharAttribute = []()
    {
        AutoRegisterAttribute::autoRegisterAttribute;
    };
};

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
};

struct AutoRegisterBoolAttribute : public AutoRegisterAttribute<AttributeBool, AttributeType::BOOL>
{
    inline static bool registerBoolAttribute = []()
    {
        AutoRegisterAttribute::autoRegisterAttribute;
    };
};

class AttributesContainer;

class AttributeCluster : public Attribute
{
private:
    std::unique_ptr<AttributesContainer> value_;
    AttributeDescriptionCluster *desc_;

public:
    AttributeCluster();
    AttributeCluster(const AttributeCluster &attributeCluster);
    AttributesContainer *getAttributeContainer();
    ~AttributeCluster() override;

public:
    std::string getName() override { return desc_->getName(); }
    AttributeType getType() override { return desc_->getType(); }
    AttributeDescription *getDescription() override { return desc_; }
    std::unique_ptr<Attribute> clone() override;
    void setDescription(AttributeDescription *desc, std::vector<Message> &messagesHistory) override;
    bool saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) override;
    void controlOptions(int position, ControlComponentsContainer *components, ControlComponentsFactoriesContainer *controlComponentsFactories, std::vector<Message> &messagesHistory) override;
};

struct AutoRegisterClusterAttribute;

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
    void setDescription(AttributeDescription *desc, std::vector<Message> &messagesHistory) override
    {
        if (dynamic_cast<AttributeDescriptionString *>(desc))
        {
            desc_ = dynamic_cast<AttributeDescriptionString *>(desc);
            value_ = "";
        }
    }
    bool saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) override;

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
};

struct AutoRegisterStringAttribute : public AutoRegisterAttribute<AttributeString, AttributeType::STRING>
{
    inline static bool registerStringAttribute = []()
    {
        AutoRegisterAttribute::autoRegisterAttribute;
    };
};