#pragma once
#include "AttributeFactory.h"

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
        if (value > getMinimum() && value < getMaximum())
        {
            value_ = value;
            return true;
        }
        return false;
    }

    void setDescription(AttributeDescription *desc) override
    {
        if (dynamic_cast<AttributeDescriptionT *>(desc))
        {
            desc_ = dynamic_cast<AttributeDescriptionT *>(desc);
            value_ = desc_->getMinimum();
        }
    }
    TypeT getValue() { return value_; }
    bool saveToJson(nlohmann::ordered_json &json, std::string &outputMessage) override;
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

class AttributeInt : public IntegerNumberBaseAttributeClass<int, AttributeDescription_int>
{
public:
    AttributeInt() : IntegerNumberBaseAttributeClass() {}
    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeInt>(*this); }
};

struct AutoRegisterIntAttribute : public AutoRegisterAttribute<AttributeInt,AttributeType::INT>
{
    inline static bool autoRegister = []()
    {
        AutoRegisterAttribute::autoRegisterAttribute;
    };
};

class AttributeDouble : public IntegerNumberBaseAttributeClass<double, AttributeDescription_double>
{
public:
    AttributeDouble() : IntegerNumberBaseAttributeClass() {};
    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeDouble>(*this); }
};

struct AutoRegisterDoubleAttribute : public AutoRegisterAttribute<AttributeDouble, AttributeType::DOUBLE>
{
    inline static bool registerDoubleAttribute = []()
    {
        AutoRegisterAttribute::autoRegisterAttribute;
    };
};

class AttributeFloat : public IntegerNumberBaseAttributeClass<float, AttributeDescription_float>
{
public:
    AttributeFloat() : IntegerNumberBaseAttributeClass() {};
    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeFloat>(*this); }
};

struct AutoRegisterFloatAttribute : public AutoRegisterAttribute<AttributeFloat, AttributeType::FLOAT>
{
    inline static bool registerFloatAttribute = []()
    {
        AutoRegisterAttribute::autoRegisterAttribute;
    };
};

class AttributeChar : public IntegerNumberBaseAttributeClass<char, AttributeDescription_char>
{
public:
    AttributeChar() : IntegerNumberBaseAttributeClass() {};
    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeChar>(*this); }
};

struct AutoRegisterCharAttribute : public AutoRegisterAttribute<AttributeChar, AttributeType::CHAR>
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
    AttributeDescription_bool *desc_;

public:
    AttributeBool() {}
    std::string getName() override { return desc_->getName(); }
    AttributeType getType() override { return desc_->getType(); }
    AttributeDescription *getDescription() override { return desc_; }
    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeBool>(*this); }
    void setDescription(AttributeDescription *desc) override
    {
        if (dynamic_cast<AttributeDescription_bool *>(desc))
        {
            desc_ = dynamic_cast<AttributeDescription_bool *>(desc);
            value_ = false;
        }
    }
    bool saveToJson(nlohmann::ordered_json &json, std::string &outputMessage) override;

    bool setValue(bool value)
    {
        value_ = value;
        return true;
    }
    bool getValue() { return value_; }
};

struct AutoRegisterBoolAttribute : public AutoRegisterAttribute<AttributeBool, AttributeType::BOOL>
{
    inline static bool registerBoolAttribute = []()
    {
        AutoRegisterAttribute::autoRegisterAttribute;
    };
};