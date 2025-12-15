#pragma once
#include "../Descriptions/AttributeDescription.h"
#include <string>
#include <limits.h>
#include <iostream>
#include <variant>
#include <stdexcept>
#include <memory>

using AttributeTypeVariant = std::variant<int, double, char>;

class Attribute
{
protected:
public:
    // AtributeType type_;
    virtual std::string getName() = 0;
    virtual AttributeType getType() = 0;
    virtual AttributeDescription *getDescription() = 0;
    virtual std::string getAgent() = 0;
    virtual ~Attribute() {};
    virtual std::unique_ptr<Attribute> clone() = 0;
    virtual void setDescription(AttributeDescription *desc) = 0;
    virtual bool saveToJson(nlohmann::json &json, std::string &outputMessage) = 0;
};

class AttributeInt : public Attribute
{
private:
    int value_;
    AttributeDescription_int *desc_;

public:
    AttributeInt() {}
    std::string getName() override { return desc_->getName(); }
    AttributeType getType() override { return AttributeType::INT; }
    AttributeDescription *getDescription() override { return desc_; }
    std::string getAgent() override { return desc_->getAgent(); }
    inline const int getMin() { return desc_->getMin(); }
    inline const int getMaximum() { return desc_->getMax(); }
    void setValue(int value) { value_ = value; }
    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeInt>(*this); }
    void setDescription(AttributeDescription *desc) override
    {
        if (dynamic_cast<AttributeDescription_int *>(desc))
        {
            desc_ = dynamic_cast<AttributeDescription_int *>(desc);
            value_ = desc_->getMin();
        }
    }
    int getValue() { return value_; }
    bool saveToJson(nlohmann::json &json, std::string &outputMessage) override;
};

class AttributeDouble : public Attribute
{
private:
    double value_;
    AttributeDescription_double *desc_;

public:
    AttributeDouble() {};
    std::string getName() override { return desc_->getName(); }
    AttributeType getType() override { return AttributeType::DOUBLE; }
    AttributeDescription *getDescription() override { return desc_; }
    std::string getAgent() override { return desc_->getAgent(); }
    inline const double getMin() { return desc_->getMin(); }
    inline const double getMaximum() { return desc_->getMax(); }
    void setValue(double value)  { value_ = value; }
    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeDouble>(*this); }
    void setDescription(AttributeDescription *desc) override
    {
        if (dynamic_cast<AttributeDescription_double *>(desc))
        {
            desc_ = dynamic_cast<AttributeDescription_double *>(desc);
            value_ = desc_->getMin();
        }
    }
    double getValue() { return value_; }
    bool saveToJson(nlohmann::json &json, std::string &outputMessage) override;
};
