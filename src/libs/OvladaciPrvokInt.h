#pragma once
#include "OvladaciPrvok.h"
#include "AtributInt.h"

enum class DruhEdituInt {
    SLIDER,
    VSLIDER,
    DRAG
};

class OvladaciPrvokInt : public OvladaciPrvok {
    protected:
        int hodnota_;
        int minimum_;
        int maximum_;

    public:
        DruhEdituInt typ_;
        OvladaciPrvokInt(DruhEdituInt typ) {typ_ = typ;};
        virtual OvladaciPrvokInt* clone() =0;
        virtual void priradAtribut(Atribut * atribut) = 0;


};