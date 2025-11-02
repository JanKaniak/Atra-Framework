#pragma once
#include "OvladaciPrvok.h"
#include "AtributChar.h"


class OvladaciPrvokChar : public OvladaciPrvok {
    protected:
        char hodnota_;
        int minimum_;
        int maximum_;

    public:
        OvladaciPrvokChar() {};
        virtual OvladaciPrvokChar* clone() =0;
        virtual void priradAtribut(Atribut * atribut) = 0;


};