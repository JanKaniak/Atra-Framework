#pragma once
#include "OvladaciPrvokInt.h"
#include "../imgui/imgui.h"
#include <iostream>
class IntSlider : public OvladaciPrvokInt {
    private:
        AtributInt* atributint_;

    public:
        IntSlider(Atribut* atribut) {

            if (AtributInt* aatribut = dynamic_cast<AtributInt*>(atribut)) {
                atributint_ = aatribut;
            }
            hodnota_ = atributint_->getHodnota();
            minimum_ = atributint_->getMin();
            maximum_ = atributint_->getMaximum();
            menoAtributu_ = atributint_->getMeno();
            typAtributu_ = atributint_->getTyp();

        }

        IntSlider(){};

        void kresli() override {
            ImGui::SliderInt(menoAtributu_.c_str(),&hodnota_,minimum_,maximum_);
        }

        std::string getMeno() override {
            return menoAtributu_;
        }

        TypAtributu getTyp() override {
            return typAtributu_;
        }

        

};

class IntDrag : public OvladaciPrvokInt {
    private:
    AtributInt* atributint_;

    public:
        IntDrag(Atribut* atribut) {

            if (AtributInt* aatribut = dynamic_cast<AtributInt*>(atribut)) {
                atributint_ = aatribut;
            }
            hodnota_ = atributint_->getHodnota();
            minimum_ = atributint_->getMin();
            maximum_ = atributint_->getMaximum();
            menoAtributu_ = atributint_->getMeno();
            typAtributu_ = atributint_->getTyp();

        }

        IntDrag(){};

        void kresli() override {
            ImGui::DragInt(menoAtributu_.c_str(),&hodnota_,0.2f,minimum_,maximum_);
        }

        std::string getMeno() override {
            return menoAtributu_;
        }

        TypAtributu getTyp() override {
            return typAtributu_;
        }
};

class IntVSSlider : public OvladaciPrvokInt {
    private:
    AtributInt* atributint_;

    public:
        IntVSSlider(Atribut* atribut) {

            if (AtributInt* aatribut = dynamic_cast<AtributInt*>(atribut)) {
                atributint_ = aatribut;
            }
            hodnota_ = atributint_->getHodnota();
            minimum_ = atributint_->getMin();
            maximum_ = atributint_->getMaximum();
            menoAtributu_ = atributint_->getMeno();
            typAtributu_ = atributint_->getTyp();

        }

        IntVSSlider(){};

        void kresli() override {
            ImGui::VSliderInt(menoAtributu_.c_str(),ImVec2(20,100),&hodnota_,minimum_,maximum_);
        }

        std::string getMeno() override {
            return menoAtributu_;
        }

        TypAtributu getTyp() override {
            return typAtributu_;
        }
};