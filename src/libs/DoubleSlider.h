#pragma once
#include "OvladaciPrvokDouble.h"
#include "../imgui/imgui.h"
#include <iostream>

class DoubleSlider : public OvladaciPrvokDouble {
    private:
        AtributDouble* atributdouble_;

    public:
        DoubleSlider() : OvladaciPrvokDouble(DruhEdituDouble::SLIDER) {}

        void kresli() override {
            ImGui::SliderScalar(menoAtributu_.c_str(),ImGuiDataType_::ImGuiDataType_Double,&hodnota_,&minimum_,&maximum_);
        }

        std::string getMeno() override {
            return menoAtributu_;
        }

        TypAtributu getTyp() override {
            return typAtributu_;
        }

        OvladaciPrvokDouble* clone () override { return new DoubleSlider(*this);};

        void priradAtribut(Atribut * atribut) override {
            if (AtributDouble* aatribut = dynamic_cast<AtributDouble*>(atribut)) {
                atributdouble_ = aatribut;
            }
            hodnota_ = atributdouble_->getHodnota();
            minimum_ = atributdouble_->getMin();
            maximum_ = atributdouble_->getMaximum();
            menoAtributu_ = atributdouble_->getMeno();
            typAtributu_ = atributdouble_->getTyp();
        }

        

};

class DoubleVSSlider : public OvladaciPrvokDouble {
    private:
        AtributDouble* atributdouble_;

    public:
        DoubleVSSlider() : OvladaciPrvokDouble(DruhEdituDouble::VSLIDER) {}

        void kresli() override {
            ImGui::VSliderScalar(menoAtributu_.c_str(),ImVec2(20,100),ImGuiDataType_Double,&hodnota_,&minimum_,&maximum_);
        }

        std::string getMeno() override {
            return menoAtributu_;
        }

        TypAtributu getTyp() override {
            return typAtributu_;
        }

        OvladaciPrvokDouble* clone () override { return new DoubleVSSlider(*this);};

        void priradAtribut(Atribut* atribut) override {
            if (AtributDouble* aatribut = dynamic_cast<AtributDouble*>(atribut)) {
                atributdouble_ = aatribut;
            }
            hodnota_ = atributdouble_->getHodnota();
            minimum_ = atributdouble_->getMin();
            maximum_ = atributdouble_->getMaximum();
            menoAtributu_ = atributdouble_->getMeno();
            typAtributu_ = atributdouble_->getTyp();
        }
};

class DoubleDrag : public OvladaciPrvokDouble {
    private:
        AtributDouble* atributdouble_;

    public:
        DoubleDrag() : OvladaciPrvokDouble(DruhEdituDouble::DRAG) {}

        void kresli() override {
            ImGui::DragScalar(menoAtributu_.c_str(),ImGuiDataType_Double,&hodnota_,0.5f,&minimum_,&maximum_);
        }

        std::string getMeno() override {
            return menoAtributu_;
        }

        TypAtributu getTyp() override {
            return typAtributu_;
        }

        OvladaciPrvokDouble* clone () override { return new DoubleDrag(*this);};

        void priradAtribut(Atribut * atribut) override {
            if (AtributDouble* aatribut = dynamic_cast<AtributDouble*>(atribut)) {
                atributdouble_ = aatribut;
            }
            hodnota_ = atributdouble_->getHodnota();
            minimum_ = atributdouble_->getMin();
            maximum_ = atributdouble_->getMaximum();
            menoAtributu_ = atributdouble_->getMeno();
            typAtributu_ = atributdouble_->getTyp();
        }

        

};
