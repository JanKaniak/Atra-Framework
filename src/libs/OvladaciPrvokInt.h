#pragma once
#include "OvladaciPrvok.h"
#include "AtributInt.h"
class OvladaciPrvokInt : public OvladaciPrvok {
    protected:
        int hodnota_;
        int minimum_;
        int maximum_;

    public:
        /*OvladaciPrvokInt(Atribut* patribut) {
            if (AtributInt* atribut = dynamic_cast<AtributInt*>(patribut)) {
                hodnota_ = atribut->getHodnota();
                minimum_ = atribut->getMin();
                maximum_ = atribut->getMaximum();
            }
        }*/

        //OvladaciPrvokInt() {};


};