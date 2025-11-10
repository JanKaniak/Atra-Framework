#pragma once
#include "../ControlComponents/ControlComponent.h"
#include "../imgui/imgui.h"
#include <iostream>
#include <tuple>
#include <variant>

class CharInput : public ControlComponentChar {
    private:
        AtributeChar* atributechar_;

    public:
        CharInput() : ControlComponentChar() {}

        void draw() override {
            ImGui::InputText(atributeName_.c_str(),value_,sizeof(value_));
            atributechar_->setValue(value_);
        }

        ControlComponentChar* clone () override { return new CharInput(*this);};

        void setAtribute(Atribute* atribute) override {
            if (AtributeChar* aatribute = dynamic_cast<AtributeChar*>(atribute)) {
                atributechar_ = aatribute;
            }
            value_[0] = atributechar_->getValue()[0];
            minimum_ = atributechar_->getMin();
            maximum_ = atributechar_->getMaximum();
            atributeName_ = atributechar_->getName();
            atributeType_ = atributechar_->getType();
        }

};