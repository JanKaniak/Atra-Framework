#pragma once
#include "ControlComponent.h"
#include <iostream>
class IntSlider : public ControlComponentInt<EditTypeInt::SLIDER> {
    private:
        AtributeInt* atributeint_;

    public:
        IntSlider(){};
        void draw() override;

        ControlComponentInt* clone () override { return new IntSlider(*this);};

        void setAtribute(Atribute* atribute) override;
};

class IntVSSlider : public ControlComponentInt<EditTypeInt::VSLIDER> {
    private:
        AtributeInt* atributeint_;

    public:
        IntVSSlider(){};

        void draw() override;

        ControlComponentInt* clone () override { return new IntVSSlider(*this);}

        void setAtribute(Atribute* atribute) override;
};

class IntDrag : public ControlComponentInt<EditTypeInt::DRAG> {
    private:
        AtributeInt* atributeint_;

    public:
        IntDrag(){};

        void draw() override;

        ControlComponentInt* clone () override { return new IntDrag(*this);};
        void setAtribute(Atribute* atribute) override;
};




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

