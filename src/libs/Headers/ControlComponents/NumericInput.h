#pragma once
#include "ControlComponent.h"
#include <iostream>
class IntSlider : public ControlComponentInt {
    private:
        AtributeInt* atributeint_;

    public:
        IntSlider() : ControlComponentInt(EditTypeInt::SLIDER) {}

        void draw() override;

        ControlComponentInt* clone () override { return new IntSlider(*this);};

        void setAtribute(Atribute* atribute) override;
};

class IntVSSlider : public ControlComponentInt {
    private:
        AtributeInt* atributeint_;

    public:
        IntVSSlider() : ControlComponentInt(EditTypeInt::VSLIDER) {}

        void draw() override;

        ControlComponentInt* clone () override { return new IntVSSlider(*this);}

        void setAtribute(Atribute* atribute) override;
};

class IntDrag : public ControlComponentInt {
    private:
        AtributeInt* atributeint_;

    public:
        IntDrag() : ControlComponentInt(EditTypeInt::DRAG) {}

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

