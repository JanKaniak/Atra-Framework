#pragma once
#include "OvladaciPrvok.h"
#include "AtributDouble.h"

enum class DruhEdituDouble {
    SLIDER,
    VSLIDER,
    DRAG
};

class OvladaciPrvokDouble : public OvladaciPrvok {
    protected:
        double hodnota_;
        double minimum_;
        double maximum_;

    public:
        DruhEdituDouble typ_;
        OvladaciPrvokDouble(DruhEdituDouble typ) {typ_ = typ;};
        virtual OvladaciPrvokDouble* clone() =0;
        virtual void priradAtribut(Atribut * atribut) = 0;


};