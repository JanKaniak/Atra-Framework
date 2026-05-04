#pragma once
#include "ControlComponent.h"
#include <iostream>
#include <variant>
#include <format>

/// Integer slider control for `AttributeInt` values.
class IntSlider : public ControlComponentInt<EditTypeNumber::SLIDER>
{
public:
    IntSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };

    /// Render the horizontal integer slider.
    void draw(std::vector<Message> &messageHistory) override;

    /// Clone a new `IntSlider` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<IntSlider>(*this); };
};

/// Integer vertical slider control for `AttributeInt`.
class IntVSlider : public ControlComponentInt<EditTypeNumber::VSLIDER>
{
public:
    IntVSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };

    /// Render the vertical integer slider.
    void draw(std::vector<Message> &messageHistory) override;
    
    /// Clone a new `IntVSlider` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<IntVSlider>(*this); }
    
};

/// Integer drag control for fine-grained `AttributeInt` editing.
class IntDrag : public ControlComponentInt<EditTypeNumber::DRAG>
{
public:
    IntDrag() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };

    /// Render the drag input for integer values.
    void draw(std::vector<Message> &messageHistory) override;
    
    /// Clone a new `IntDrag` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<IntDrag>(*this); };
};

//------------------------------------------------------------------------------------------

/// Double slider control for `AttributeDouble` values.
class DoubleSlider : public ControlComponentDouble<EditTypeNumber::SLIDER>
{
public:
    DoubleSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };

    /// Render the horizontal double slider control.
    void draw(std::vector<Message> &messageHistory) override;
    
    /// Clone a new `DoubleSlider` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<DoubleSlider>(*this); };
    
};

/// Double vertical slider control for `AttributeDouble` values.
class DoubleVSlider : public ControlComponentDouble<EditTypeNumber::VSLIDER>
{
public:
    DoubleVSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };

    /// Render the vertical double slider control.
    void draw(std::vector<Message> &messageHistory) override;
    
    /// Clone a new `DoubleVSlider` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<DoubleVSlider>(*this); };
};

class DoubleDrag : public ControlComponentDouble<EditTypeNumber::DRAG>
{
public:
    DoubleDrag() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };

    /// Render the drag input for double-precision values.
    void draw(std::vector<Message> &messageHistory) override;
    
    /// Clone a new `DoubleDrag` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<DoubleDrag>(*this); };
};

//------------------------------------------------------------------------------------------

/// Float slider control for `AttributeFloat` values.
class FloatSlider : public ControlComponentFloat<EditTypeNumber::SLIDER>
{
public:
    FloatSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };

    /// Render the horizontal float slider control.
    void draw(std::vector<Message> &messageHistory) override;
   
    /// Clone a new `FloatSlider` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<FloatSlider>(*this); };
    
};

/// Float vertical slider control for `AttributeFloat` values.
class FloatVSlider : public ControlComponentFloat<EditTypeNumber::VSLIDER>
{
public:
    FloatVSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };

    /// Render the vertical float slider control.
    void draw(std::vector<Message> &messageHistory) override;

    /// Clone a new `FloatVSlider` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<FloatVSlider>(*this); };

};

/// Float drag control for `AttributeFloat` values.
class FloatDrag : public ControlComponentFloat<EditTypeNumber::DRAG>
{
public:
    FloatDrag() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };

    /// Render the drag input for single-precision float values.
    void draw(std::vector<Message> &messageHistory) override;

    /// Clone a new `FloatDrag` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<FloatDrag>(*this); };

};

//------------------------------------------------------------------------------------------

/// Character slider control for `AttributeCharNumber` values.
class CharSlider : public ControlComponentCharNumber<EditTypeNumber::SLIDER>
{
public:
    CharSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };

    /// Render the horizontal char slider control.
    void draw(std::vector<Message> &messageHistory) override;
   
    /// Clone a new `CharSlider` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<CharSlider>(*this); };
    
};

/// Character vertical slider control for `AttributeCharNumber` values.
class CharVSlider : public ControlComponentCharNumber<EditTypeNumber::VSLIDER>
{
public:
    CharVSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };

    /// Render the vertical char slider control.
    void draw(std::vector<Message> &messageHistory) override;

    /// Clone a new `CharVSlider` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<CharVSlider>(*this); };

};

/// Character drag control for `AttributeCharNumber` values.
class CharDrag : public ControlComponentCharNumber<EditTypeNumber::DRAG>
{
public:
    CharDrag() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };

    /// Render the character drag input control.
    void draw(std::vector<Message> &messageHistory) override;

    /// Clone a new `CharDrag` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<CharDrag>(*this); };

};

//------------------------------------------------------------------------------------------

/// Long integer slider control for `AttributeLong` values.
class LongSlider : public ControlComponentLong<EditTypeNumber::SLIDER>
{
public:
    LongSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;
   
    /// Clone a new `LongSlider` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<LongSlider>(*this); };
    
};

/// Long integer vertical slider control for `AttributeLong` values.
class LongVSlider : public ControlComponentLong<EditTypeNumber::VSLIDER>
{
public:
    LongVSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;

    /// Clone a new `LongVSlider` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<LongVSlider>(*this); };

};

/// Long integer drag control for `AttributeLong` values.
class LongDrag : public ControlComponentLong<EditTypeNumber::DRAG>
{
public:
    LongDrag() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };
    void draw(std::vector<Message> &messageHistory) override;

    /// Clone a new `LongDrag` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<LongDrag>(*this); };

};

//------------------------------------------------------------------------------------------

/// Unsigned integer slider control for `AttributeUint` values.
class UintSlider : public ControlComponentUInt<EditTypeNumber::SLIDER>
{
public:
    UintSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };

    /// Render the horizontal unsigned integer slider.
    void draw(std::vector<Message> &messageHistory) override;
   
    /// Clone a new `UintSlider` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<UintSlider>(*this); };
    
};

/// Unsigned integer vertical slider control for `AttributeUint` values.
class UintVSlider : public ControlComponentUInt<EditTypeNumber::VSLIDER>
{
public:
    UintVSlider() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };

    /// Render the vertical unsigned integer slider.
    void draw(std::vector<Message> &messageHistory) override;

    /// Clone a new `UintVSlider` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<UintVSlider>(*this); };

};

/// Unsigned integer drag control for `AttributeUint` values.
class UintDrag : public ControlComponentUInt<EditTypeNumber::DRAG>
{
public:
    UintDrag() {
        minimumWidth_ = 100;
        maximumWidth_ = 300;
    };

    /// Render the drag input for unsigned integer values.
    void draw(std::vector<Message> &messageHistory) override;

    /// Clone a new `UintDrag` component.
    std::unique_ptr<ControlComponent> clone() override { return std::make_unique<UintDrag>(*this); };

};