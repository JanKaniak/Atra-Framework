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

