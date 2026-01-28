#pragma once
#include "../Attributes/Attribute.h"
#include <variant>

enum class EditTypeDouble
{
    SLIDER,
    VSLIDER,
    DRAG
};

enum class EditTypeInt
{
    SLIDER,
    VSLIDER,
    DRAG
};

enum class EditTypeFloat
{
    SLIDER,
    VSLIDER,
    DRAG
};

class ControlComponent
{
public:
    virtual void draw() = 0;
    virtual std::string getName() = 0;
    virtual AttributeType getType() = 0;
    virtual std::string getAgent() = 0;
    virtual ~ControlComponent() = default;
    virtual void setAttribute(Attribute *attribute) = 0;
    virtual std::unique_ptr<ControlComponent> clone() = 0;
    virtual Attribute *getAttribute() = 0;
};

template <EditTypeInt TYPE>
class ControlComponentInt : public ControlComponent
{
protected:
    int value_;
    int minimum_;
    int maximum_;
    AttributeInt *attributeint_;

public:
    static constexpr EditTypeInt type_ = TYPE;
    void setAttribute(Attribute *attribute) override
    {
        if (dynamic_cast<AttributeInt*>(attribute))
        {
            attributeint_ = dynamic_cast<AttributeInt *>(attribute);
            value_ = attributeint_->getValue();
            minimum_ = attributeint_->getMin();
            maximum_ = attributeint_->getMaximum();
        }
    }
    std::string getName() override { return attributeint_->getName(); };
    AttributeType getType() override { return attributeint_->getType(); };
    std::string getAgent() override { return attributeint_->getAgent(); };
    Attribute *getAttribute() override { return attributeint_; };
};

template <EditTypeDouble TYPE>
class ControlComponentDouble : public ControlComponent
{
protected:
    double value_;
    double minimum_;
    double maximum_;
    AttributeDouble *attributedouble_;

public:
    static constexpr EditTypeDouble type_ = TYPE;
    void setAttribute(Attribute *attribute) override
    {
        if (dynamic_cast<AttributeDouble*>(attribute))
        {
            attributedouble_ = dynamic_cast<AttributeDouble*>(attribute);
            value_ = attributedouble_->getValue();
            minimum_ = attributedouble_->getMin();
            maximum_ = attributedouble_->getMaximum();
        }
    }
    std::string getName() override { return attributedouble_->getName(); };
    AttributeType getType() override { return attributedouble_->getType(); };
    std::string getAgent() override { return attributedouble_->getAgent(); };
    Attribute *getAttribute() override { return attributedouble_; };
};

template <EditTypeFloat TYPE>
class ControlComponentFloat : public ControlComponent
{
protected:
    float value_;
    float minimum_;
    float maximum_;
    AttributeFloat *attributefloat_;

public:
    static constexpr EditTypeFloat type_ = TYPE;
    void setAttribute(Attribute *attribute) override
    {
        if (dynamic_cast<AttributeFloat*>(attribute))
        {
            attributefloat_ = dynamic_cast<AttributeFloat*>(attribute);
            value_ = attributefloat_->getValue();
            minimum_ = attributefloat_->getMin();
            maximum_ = attributefloat_->getMaximum();
        }
    }
     std::string getName() override { return attributefloat_->getName(); };
    AttributeType getType() override { return attributefloat_->getType(); };
    std::string getAgent() override { return attributefloat_->getAgent(); };
    Attribute *getAttribute() override { return attributefloat_; };
};

















class ControlComponentChar : public ControlComponent
{
protected:
    char value_[2];
    int minimum_;
    int maximum_;

public:
    ControlComponentChar() {};
    virtual std::unique_ptr<ControlComponent> clone() = 0;
};

