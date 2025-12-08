#pragma once
#include "ControlComponent.h"
#include <iostream>
#include <variant>
#include <format>

class IntSlider : public ControlComponentInt<EditTypeInt::SLIDER> {
    
    private:
        AttributeInt* attributeint_;
    public:
        IntSlider(){};
        void draw() override;
        std::string getName() override { return attributeint_->getName();};
        AttributeType getType() override {return attributeint_->getType();};
        std::string getAgent() override {return attributeint_->getAgent();};
        std::unique_ptr<ControlComponent> clone () override { return std::make_unique<IntSlider>(*this);};
        void setAttribute(Attribute* attribute) override;
        Attribute *getAttribute() override {return attributeint_;};
};

class IntVSSlider : public ControlComponentInt<EditTypeInt::VSLIDER> {
    private:
        AttributeInt* attributeint_;

    public:
        IntVSSlider(){};

        void draw() override;
        std::string getName() override { return attributeint_->getName();};
        AttributeType getType() override {return attributeint_->getType();};
        std::string getAgent() override {return attributeint_->getAgent();};
        std::unique_ptr<ControlComponent> clone () override { return std::make_unique<IntVSSlider>(*this);}
        void setAttribute(Attribute* attribute) override;
        Attribute *getAttribute() override {return attributeint_;};
};

class IntDrag : public ControlComponentInt<EditTypeInt::DRAG> {
    private:
        

    public:
        IntDrag(){};

        void draw() override;
        std::string getName() override { return attributeint_->getName();};
        AttributeType getType() override {return attributeint_->getType();};
        std::string getAgent() override {return attributeint_->getAgent();};
        std::unique_ptr<ControlComponent> clone () override { return std::make_unique<IntDrag>(*this);};
        void setAttribute(Attribute* attribute) override;
        Attribute *getAttribute() override {return attributeint_;};
};


/*

//------------------------------------------------------------------------------------------

class DoubleSlider : public ControlComponentDouble {
    private:
        AtributeDouble* atributedouble_;

    public:
        DoubleSlider() : ControlComponentDouble(EditTypeDouble::SLIDER) {}

        void draw() override;

        ControlComponentDouble* clone () override { return new DoubleSlider(*this);};

        void setAtribute(Atribute* atribute) override;

        

};

class DoubleVSSlider : public ControlComponentDouble {
    private:
        AtributeDouble* atributedouble_;

    public:
        DoubleVSSlider() : ControlComponentDouble(EditTypeDouble::VSLIDER) {}

        void draw() override;

        ControlComponentDouble* clone () override { return new DoubleVSSlider(*this);};

        void setAtribute(Atribute* atribute) override;
};

class DoubleDrag : public ControlComponentDouble {
    private:
        AtributeDouble* atributedouble_;

    public:
        DoubleDrag() : ControlComponentDouble(EditTypeDouble::DRAG) {}

        void draw() override;

        ControlComponentDouble* clone () override { return new DoubleDrag(*this); };

        void setAtribute(Atribute* atribute) override;

        

};



*/