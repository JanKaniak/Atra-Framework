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
    Atribute* atribute_;
public:
    virtual void draw() = 0;
    std::string getName() { return atribute_->getName(); };
    AtributeType getType() { return atribute_->getType(); };
    virtual ~ControlComponent() = default;
    virtual void setAtribute(Atribute * atribute) = 0;
    virtual ControlComponent* clone() = 0;
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


