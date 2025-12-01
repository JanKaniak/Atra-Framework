#pragma once
#include "../Attributes/Attribute.h"
#include <variant>

enum class EditTypeDouble {
    SLIDER,
    VSLIDER,
    DRAG
};

enum class EditTypeInt {
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
    virtual ~ControlComponent() = default;
    virtual void setAttribute(Attribute * attribute) = 0;
    virtual std::unique_ptr<ControlComponent> clone() = 0;
};

class ControlComponentChar : public ControlComponent {
    protected:
        char value_[2];
        int minimum_;
        int maximum_;

    public:
        ControlComponentChar() {};
        virtual std::unique_ptr<ControlComponent> clone() =0;
};



class ControlComponentDouble : public ControlComponent {
    protected:
        double value_;
        double minimum_;
        double maximum_;

    public:
        EditTypeDouble type_;
        ControlComponentDouble(EditTypeDouble type) {type_ = type;};
        virtual std::unique_ptr<ControlComponent> clone() =0;
};



template<EditTypeInt TYPE>
class ControlComponentInt : public ControlComponent {
    protected:
        int value_;
        int minimum_;
        int maximum_;
    public:
        static constexpr EditTypeInt type_ = TYPE;
        //virtual ControlComponentInt* clone() =0;
};


