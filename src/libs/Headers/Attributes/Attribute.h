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
    AttributeDescription *desc_;

public:
    // AtributeType type_;
    inline std::string getName() { return desc_->getName(); }

    inline AttributeType getType() { return desc_->getType(); }

    AttributeDescription *getDescription() { return desc_; };

    virtual ~Attribute() {};
    virtual std::unique_ptr<Attribute> clone() = 0;
    virtual void setDescription(AttributeDescription *desc) = 0;
    virtual AttributeTypeVariant getValue() = 0;
    virtual void setValue(AttributeTypeVariant value) = 0;
};

class AttributeInt : public Attribute
{
private:
    int value_;

public:
    AttributeInt() { desc_ = new AttributeDescription_int(); };

    inline int getMin() { return desc_->getMin(); }

    inline int getMaximum() { return desc_->getMax(); }

    void setValue(AttributeTypeVariant value) override
    {
        try
        {
            if (std::holds_alternative<int>(value)) {
                value_ = std::get<int>(value);
            }
            else {
                throw std::runtime_error("Not numeric type!");;
            }
        } catch (const std::exception& exc) {
            std::cerr << "Error: " << exc.what() << std::endl;
        }
    }

    std::unique_ptr<Attribute> clone() override { return std::make_unique<AttributeInt>(*this); }

    void setDescription(AttributeDescription *desc) override
    {
        desc_ = dynamic_cast<AttributeDescription_int*>(desc);
        value_ = desc_->getMin();
    }

    AttributeTypeVariant getValue() override { return value_; }
};

/*


class AtributeDouble : public Atribute
{
private:
    double value_;

public:
    AtributeDouble() { desc_ = new AtributeDescription_double(); };

    const double getMin()
    {
        return desc_->getMin();
    }

    const double getMaximum()
    {
        return desc_->getMax();
    }

    void setValue(AtributeTypeVariant value) override {}

    AtributeDouble* clone() override { return new AtributeDouble(*this); }

    void setDescription(AtributeDescription *desc) override
    {
        desc_ = desc;
        value_ = desc_->getMin();
    }

    AtributeTypeVariant getValue() { return value_; }
};

class AtributeChar : public Atribute
{
private:
    char value_[1];

public:
    AtributeChar() { desc_ = new AtributeDescription_char(); };

    int getMin()
    {
        return desc_->getMin();
    }

    int getMaximum()
    {
        return desc_->getMax();
    }

    void setValue(AtributeTypeVariant value) override {}

    AtributeChar* clone() override { return new AtributeChar(*this); }

    void setDescription(AtributeDescription *desc) override { desc_ = desc; }

    AtributeTypeVariant getValue() { return value_[0]; }
};




*/