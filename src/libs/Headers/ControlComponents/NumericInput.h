#pragma once
#include "ControlComponent.h"
#include <iostream>
#include <variant>
#include <format>

class IntSlider : public ControlComponentInt<EditTypeInt::SLIDER>
{

private:
public:
    IntSlider() {
        minimumWidth_ = 100;
    };
    void draw() override;
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<IntSlider>(*this); };
};

class IntVSSlider : public ControlComponentInt<EditTypeInt::VSLIDER>
{
private:
public:
    IntVSSlider() {
        minimumWidth_ = 100;
    };

    void draw() override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<IntVSSlider>(*this); }
    
};

class IntDrag : public ControlComponentInt<EditTypeInt::DRAG>
{
public:
    IntDrag() {
        minimumWidth_ = 100;
    };

    void draw() override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<IntDrag>(*this); };
};

//------------------------------------------------------------------------------------------

class DoubleSlider : public ControlComponentDouble<EditTypeDouble::SLIDER>
{
public:
    DoubleSlider() {
        minimumWidth_ = 100;
    };
    void draw() override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<DoubleSlider>(*this); };
    
};

class DoubleVSSlider : public ControlComponentDouble<EditTypeDouble::VSLIDER>
{
public:
    DoubleVSSlider() {
        minimumWidth_ = 100;
    };
    void draw() override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<DoubleVSSlider>(*this); };
};

class DoubleDrag : public ControlComponentDouble<EditTypeDouble::DRAG>
{
private:

public:
    DoubleDrag() {
        minimumWidth_ = 100;
    };
    void draw() override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<DoubleDrag>(*this); };
};

//------------------------------------------------------------------------------------------

class FloatSlider : public ControlComponentFloat<EditTypeFloat::SLIDER>
{
public:
    FloatSlider() {
        minimumWidth_ = 100;
    };
    void draw() override;
   
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<FloatSlider>(*this); };
    
};

class FloatVSSlider : public ControlComponentFloat<EditTypeFloat::VSLIDER>
{
public:
    FloatVSSlider() {
        minimumWidth_ = 100;
    };
    void draw() override;

    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<FloatVSSlider>(*this); };

};

class FloatDrag : public ControlComponentFloat<EditTypeFloat::DRAG>
{
private:

public:
    FloatDrag() {
        minimumWidth_ = 100;
    };
    void draw() override;

    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<FloatDrag>(*this); };

};
