#pragma once
#include "ControlComponent.h"
#include <iostream>
#include <variant>
#include <format>

class IntSlider : public ControlComponentInt<EditTypeNumber::SLIDER>
{

private:
public:
    IntSlider() {
        minimumWidth_ = 100;
    };
    void draw() override;
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<IntSlider>(*this); };
};

class IntVSSlider : public ControlComponentInt<EditTypeNumber::VSLIDER>
{
private:
public:
    IntVSSlider() {
        minimumWidth_ = 100;
    };

    void draw() override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<IntVSSlider>(*this); }
    
};

class IntDrag : public ControlComponentInt<EditTypeNumber::DRAG>
{
public:
    IntDrag() {
        minimumWidth_ = 100;
    };

    void draw() override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<IntDrag>(*this); };
};

//------------------------------------------------------------------------------------------

class DoubleSlider : public ControlComponentDouble<EditTypeNumber::SLIDER>
{
public:
    DoubleSlider() {
        minimumWidth_ = 100;
    };
    void draw() override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<DoubleSlider>(*this); };
    
};

class DoubleVSSlider : public ControlComponentDouble<EditTypeNumber::VSLIDER>
{
public:
    DoubleVSSlider() {
        minimumWidth_ = 100;
    };
    void draw() override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<DoubleVSSlider>(*this); };
};

class DoubleDrag : public ControlComponentDouble<EditTypeNumber::DRAG>
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

class FloatSlider : public ControlComponentFloat<EditTypeNumber::SLIDER>
{
public:
    FloatSlider() {
        minimumWidth_ = 100;
    };
    void draw() override;
   
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<FloatSlider>(*this); };
    
};

class FloatVSSlider : public ControlComponentFloat<EditTypeNumber::VSLIDER>
{
public:
    FloatVSSlider() {
        minimumWidth_ = 100;
    };
    void draw() override;

    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<FloatVSSlider>(*this); };

};

class FloatDrag : public ControlComponentFloat<EditTypeNumber::DRAG>
{
private:

public:
    FloatDrag() {
        minimumWidth_ = 100;
    };
    void draw() override;

    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<FloatDrag>(*this); };

};
