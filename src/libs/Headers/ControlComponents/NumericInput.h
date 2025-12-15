#pragma once
#include "ControlComponent.h"
#include <iostream>
#include <variant>
#include <format>

class IntSlider : public ControlComponentInt<EditTypeInt::SLIDER>
{

private:
public:
    IntSlider() {};
    void draw() override;
    std::string getName() override { return attributeint_->getName(); };
    AttributeType getType() override { return attributeint_->getType(); };
    std::string getAgent() override { return attributeint_->getAgent(); };
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<IntSlider>(*this); };
    Attribute *getAttribute() override { return attributeint_; };
};

class IntVSSlider : public ControlComponentInt<EditTypeInt::VSLIDER>
{
private:
public:
    IntVSSlider() {};

    void draw() override;
    std::string getName() override { return attributeint_->getName(); };
    AttributeType getType() override { return attributeint_->getType(); };
    std::string getAgent() override { return attributeint_->getAgent(); };
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<IntVSSlider>(*this); }
    Attribute *getAttribute() override { return attributeint_; };
};

class IntDrag : public ControlComponentInt<EditTypeInt::DRAG>
{
public:
    IntDrag() {};

    void draw() override;
    std::string getName() override { return attributeint_->getName(); };
    AttributeType getType() override { return attributeint_->getType(); };
    std::string getAgent() override { return attributeint_->getAgent(); };
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<IntDrag>(*this); };
    Attribute *getAttribute() override { return attributeint_; };
};

//------------------------------------------------------------------------------------------

class DoubleSlider : public ControlComponentDouble<EditTypeDouble::SLIDER>
{
public:
    DoubleSlider() {};
    void draw() override;
    std::string getName() override { return attributedouble_->getName(); };
    AttributeType getType() override { return attributedouble_->getType(); };
    std::string getAgent() override { return attributedouble_->getAgent(); };
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<DoubleSlider>(*this); };
    Attribute *getAttribute() override { return attributedouble_; };
};

class DoubleVSSlider : public ControlComponentDouble<EditTypeDouble::SLIDER>
{
public:
    DoubleVSSlider() {};
    void draw() override;
    std::string getName() override { return attributedouble_->getName(); };
    AttributeType getType() override { return attributedouble_->getType(); };
    std::string getAgent() override { return attributedouble_->getAgent(); };
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<DoubleVSSlider>(*this); };
    Attribute *getAttribute() override { return attributedouble_; };
};

class DoubleDrag : public ControlComponentDouble<EditTypeDouble::SLIDER>
{
private:

public:
    DoubleDrag() {};
    void draw() override;
    std::string getName() override { return attributedouble_->getName(); };
    AttributeType getType() override { return attributedouble_->getType(); };
    std::string getAgent() override { return attributedouble_->getAgent(); };
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<DoubleDrag>(*this); };
    Attribute *getAttribute() override { return attributedouble_; };
};
