#pragma once
#include "PopisAtributu.h"
#include <string>

class Atribut {
    protected:
        PopisAtributu* popis_;
        
    
    public:
        TypAtributu typ_;

        Atribut(TypAtributu typ) : typ_(typ) {}

        std::string getMeno() {
            return popis_->getMeno();
        }

        TypAtributu getTyp() {
            return typ_;
        }

        virtual ~Atribut() {};
        virtual Atribut* clone() = 0;
        virtual void priradPopis(PopisAtributu* popis) = 0;

};