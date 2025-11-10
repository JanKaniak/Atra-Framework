#pragma once
#include "../Atributes/Atribute.h"
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
protected:
    std::string atributeName_;
    AtributeType atributeType_;
public:
    virtual void draw() = 0;
    std::string getName() { return atributeName_; };
    AtributeType getType() { return atributeType_; };
    virtual ~ControlComponent() = default;
    virtual void setAtribute(Atribute * atribute) = 0;
};

class ControlComponentChar : public ControlComponent {
    protected:
        char value_[2];
        int minimum_;
        int maximum_;

    public:
        ControlComponentChar() {};
        virtual ControlComponentChar* clone() =0;
};



class ControlComponentDouble : public ControlComponent {
    protected:
        double value_;
        double minimum_;
        double maximum_;

    public:
        EditTypeDouble type_;
        ControlComponentDouble(EditTypeDouble type) {type_ = type;};
        virtual ControlComponentDouble* clone() =0;
};




class ControlComponentInt : public ControlComponent {
    protected:
        int value_;
        int minimum_;
        int maximum_;
    public:
        EditTypeInt type_;
        ControlComponentInt(EditTypeInt type) {type_ = type;};
        virtual ControlComponentInt* clone() =0;
};


