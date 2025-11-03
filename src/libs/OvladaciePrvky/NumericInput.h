#pragma once
#include "../OvladaciePrvky/OvladaciPrvok.h"
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




//------------------------------------------------------------------------------------------

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

