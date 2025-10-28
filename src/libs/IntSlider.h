#pragma once
#include "OvladaciPrvokInt.h"
#include "../imgui/imgui.h"
#include <iostream>
class IntSlider : public OvladaciPrvokInt {
    private:
        AtributInt* atributint_;

    public:
        IntSlider() : OvladaciPrvokInt(DruhEdituInt::SLIDER) {}

        void kresli() override {
            ImGui::SliderInt(menoAtributu_.c_str(),&hodnota_,minimum_,maximum_);
        }

        std::string getMeno() override {
            return menoAtributu_;
        }

        TypAtributu getTyp() override {
            return typAtributu_;
        }

        OvladaciPrvokInt* clone () override { return new IntSlider(*this);};

        void priradAtribut(Atribut * atribut) override {
            if (AtributInt* aatribut = dynamic_cast<AtributInt*>(atribut)) {
                atributint_ = aatribut;
            }
            hodnota_ = atributint_->getHodnota();
            minimum_ = atributint_->getMin();
            maximum_ = atributint_->getMaximum();
            menoAtributu_ = atributint_->getMeno();
            typAtributu_ = atributint_->getTyp();
        }

        

};

class IntVSSlider : public OvladaciPrvokInt {
    private:
        AtributInt* atributint_;

    public:
        IntVSSlider() : OvladaciPrvokInt(DruhEdituInt::VSLIDER) {}

        void kresli() override {
            ImGui::VSliderInt(menoAtributu_.c_str(),ImVec2(20,100),&hodnota_,minimum_,maximum_);
        }

        std::string getMeno() override {
            return menoAtributu_;
        }

        TypAtributu getTyp() override {
            return typAtributu_;
        }

        OvladaciPrvokInt* clone () override { return new IntVSSlider(*this);};

        void priradAtribut(Atribut* atribut) override {
            if (AtributInt* aatribut = dynamic_cast<AtributInt*>(atribut)) {
                atributint_ = aatribut;
            }
            hodnota_ = atributint_->getHodnota();
            minimum_ = atributint_->getMin();
            maximum_ = atributint_->getMaximum();
            menoAtributu_ = atributint_->getMeno();
            typAtributu_ = atributint_->getTyp();
        }
};

class IntDrag : public OvladaciPrvokInt {
    private:
        AtributInt* atributint_;

    public:
        IntDrag() : OvladaciPrvokInt(DruhEdituInt::DRAG) {}

        void kresli() override {
            ImGui::DragInt(menoAtributu_.c_str(),&hodnota_,0.5f,minimum_,maximum_);
        }

        std::string getMeno() override {
            return menoAtributu_;
        }

        TypAtributu getTyp() override {
            return typAtributu_;
        }

        OvladaciPrvokInt* clone () override { return new IntDrag(*this);};

        void priradAtribut(Atribut * atribut) override {
            if (AtributInt* aatribut = dynamic_cast<AtributInt*>(atribut)) {
                atributint_ = aatribut;
            }
            hodnota_ = atributint_->getHodnota();
            minimum_ = atributint_->getMin();
            maximum_ = atributint_->getMaximum();
            menoAtributu_ = atributint_->getMeno();
            typAtributu_ = atributint_->getTyp();
        }

        

};
