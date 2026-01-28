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
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<IntSlider>(*this); };
};

class IntVSSlider : public ControlComponentInt<EditTypeInt::VSLIDER>
{
private:
public:
    IntVSSlider() {};

    void draw() override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<IntVSSlider>(*this); }
    
};

class IntDrag : public ControlComponentInt<EditTypeInt::DRAG>
{
public:
    IntDrag() {};

    void draw() override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<IntDrag>(*this); };
};

//------------------------------------------------------------------------------------------

class DoubleSlider : public ControlComponentDouble<EditTypeDouble::SLIDER>
{
public:
    DoubleSlider() {};
    void draw() override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<DoubleSlider>(*this); };
    
};

class DoubleVSSlider : public ControlComponentDouble<EditTypeDouble::SLIDER>
{
public:
    DoubleVSSlider() {};
    void draw() override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<DoubleVSSlider>(*this); };
};

class DoubleDrag : public ControlComponentDouble<EditTypeDouble::SLIDER>
{
private:

public:
    DoubleDrag() {};
    void draw() override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<DoubleDrag>(*this); };
};

//------------------------------------------------------------------------------------------

class FloatSlider : public ControlComponentFloat<EditTypeFloat::SLIDER>
{
public:
    FloatSlider() {};
    void draw() override;
   
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<FloatSlider>(*this); };
    
};

class FloatVSSlider : public ControlComponentFloat<EditTypeFloat::SLIDER>
{
public:
    FloatVSSlider() {};
    void draw() override;

    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<FloatVSSlider>(*this); };

};

class FloatDrag : public ControlComponentFloat<EditTypeFloat::SLIDER>
{
private:

public:
    FloatDrag() {};
    void draw() override;

    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<FloatDrag>(*this); };

};
