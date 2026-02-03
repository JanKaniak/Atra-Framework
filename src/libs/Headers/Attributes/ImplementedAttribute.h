#include "AttributeFactory.h"

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
    bool saveToJson(nlohmann::ordered_json &json, std::string &outputMessage) override;
};

struct AutoRegisterIntAttribute {
    inline static bool registerIntAttribute = [] () {
        AttributeFactory::getInstance()->registerPrototype(std::make_unique<AttributeInt>());
        return true;
    }();
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
    bool saveToJson(nlohmann::ordered_json &json, std::string &outputMessage) override;
};

struct AutoRegisterDoubleAttribute {
    inline static bool registerDoubleAttribute = [] () {
        AttributeFactory::getInstance()->registerPrototype(std::make_unique<AttributeDouble>());
        return true;
    }();
};


class AttributeFloat : public Attribute
{
private:
    float value_;
    AttributeDescription_float *desc_;

public:
    AttributeFloat() {};
    std::string getName() override { return desc_->getName(); }
    AttributeType getType() override { return AttributeType::FLOAT; }
    AttributeDescription *getDescription() override { return desc_; }
    inline const float getMin() { return desc_->getMin(); }
    inline const float getMaximum() { return desc_->getMax(); }
    void setValue(float value)  { value_ = value; }
    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeFloat>(*this); }
    void setDescription(AttributeDescription *desc) override
    {
        if (dynamic_cast<AttributeDescription_float *>(desc))
        {
            desc_ = dynamic_cast<AttributeDescription_float *>(desc);
            value_ = desc_->getMin();
        }
    }
    float getValue() { return value_; }
    bool saveToJson(nlohmann::ordered_json &json, std::string &outputMessage) override;
};

struct AutoRegisterFloatAttribute {
    inline static bool registerFloatAttribute = [] () {
        AttributeFactory::getInstance()->registerPrototype(std::make_unique<AttributeFloat>());
        return true;
    }();
};
