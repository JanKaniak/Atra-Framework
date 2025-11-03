#pragma once
#include "../OvladaciePrvky/OvladaciPrvok.h"
#include "../imgui/imgui.h"
#include <iostream>
#include <tuple>
#include <variant>

class CharInput : public OvladaciPrvokChar {
    private:
        AtributChar* atributchar_;

    public:
        CharInput() : OvladaciPrvokChar() {}

        void kresli() override {
            ImGui::InputText(menoAtributu_.c_str(),&hodnota_,1);
        }

        std::string getMeno() override {
            return menoAtributu_;
        }

        TypAtributu getTyp() override {
            return typAtributu_;
        }

        OvladaciPrvokChar* clone () override { return new CharInput(*this);};

        void priradAtribut(Atribut * atribut) override {
            if (AtributChar* aatribut = dynamic_cast<AtributChar*>(atribut)) {
                atributchar_ = aatribut;
            }
            hodnota_ = atributchar_->getHodnota();
            minimum_ = atributchar_->getMin();
            maximum_ = atributchar_->getMaximum();
            menoAtributu_ = atributchar_->getMeno();
            typAtributu_ = atributchar_->getTyp();
        }

        

};