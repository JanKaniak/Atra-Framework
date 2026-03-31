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
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<IntSlider>(*this); };
};

class IntVSlider : public ControlComponentInt<EditTypeNumber::VSLIDER>
{
private:
public:
    IntVSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };

    void draw(std::vector<Message> &messageHistory) override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<IntVSlider>(*this); }
    
};

class IntDrag : public ControlComponentInt<EditTypeNumber::DRAG>
{
public:
    IntDrag() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };

    void draw(std::vector<Message> &messageHistory) override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<IntDrag>(*this); };
};

//------------------------------------------------------------------------------------------

class DoubleSlider : public ControlComponentDouble<EditTypeNumber::SLIDER>
{
public:
    DoubleSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<DoubleSlider>(*this); };
    
};

class DoubleVSlider : public ControlComponentDouble<EditTypeNumber::VSLIDER>
{
public:
    DoubleVSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<DoubleVSlider>(*this); };
};

class DoubleDrag : public ControlComponentDouble<EditTypeNumber::DRAG>
{
private:

public:
    DoubleDrag() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;
    
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<DoubleDrag>(*this); };
};

//------------------------------------------------------------------------------------------

class FloatSlider : public ControlComponentFloat<EditTypeNumber::SLIDER>
{
public:
    FloatSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;
   
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<FloatSlider>(*this); };
    
};

class FloatVSlider : public ControlComponentFloat<EditTypeNumber::VSLIDER>
{
public:
    FloatVSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;

    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<FloatVSlider>(*this); };

};

class FloatDrag : public ControlComponentFloat<EditTypeNumber::DRAG>
{
private:

public:
    FloatDrag() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;

    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<FloatDrag>(*this); };

};

//------------------------------------------------------------------------------------------

class CharSlider : public ControlComponentCharNumber<EditTypeNumber::SLIDER>
{
public:
    CharSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;
   
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<CharSlider>(*this); };
    
};

class CharVSlider : public ControlComponentCharNumber<EditTypeNumber::VSLIDER>
{
public:
    CharVSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;

    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<CharVSlider>(*this); };

};

class CharDrag : public ControlComponentCharNumber<EditTypeNumber::DRAG>
{
private:

public:
    CharDrag() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;

    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<CharDrag>(*this); };

};

//------------------------------------------------------------------------------------------

class LongSlider : public ControlComponentLong<EditTypeNumber::SLIDER>
{
public:
    LongSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;
   
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<LongSlider>(*this); };
    
};

class LongVSlider : public ControlComponentLong<EditTypeNumber::VSLIDER>
{
public:
    LongVSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;

    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<LongVSlider>(*this); };

};

class LongDrag : public ControlComponentLong<EditTypeNumber::DRAG>
{
private:

public:
    LongDrag() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;

    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<LongDrag>(*this); };

};

//------------------------------------------------------------------------------------------

class UintSlider : public ControlComponentUInt<EditTypeNumber::SLIDER>
{
public:
    UintSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;
   
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<UintSlider>(*this); };
    
};

class UintVSlider : public ControlComponentUInt<EditTypeNumber::VSLIDER>
{
public:
    UintVSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;

    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<UintVSlider>(*this); };

};

class UintDrag : public ControlComponentUInt<EditTypeNumber::DRAG>
{
private:

public:
    UintDrag() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;

    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<UintDrag>(*this); };

};