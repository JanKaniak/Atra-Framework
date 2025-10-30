#pragma once
#include "PopisAtributu.h"
#include <string>

class Atribut {
    protected:
        PopisAtributu* popis_;
        //TypAtributuInt typ_;
    
    public:
        std::string getMeno() {
            return popis_->getMeno();
        }

        TypAtributu getTyp() {
            return popis_->getTyp();
        }

        void priradPopis(PopisAtributu* popis) {
            popis_ = popis;
        }

        virtual ~Atribut() {};
        virtual Atribut* clone() = 0;

};