#pragma once
#include <string>
#include "TypAtributu.h"
class PopisAtributu {
    protected:
        std::string meno_;
        TypAtributu typ_;
        
    
        public:
        PopisAtributu(TypAtributu typ) : typ_(typ) {};
        std::string getMeno() {return meno_;};
        TypAtributu getTyp() {return typ_;};
        virtual double getMin() = 0;
        virtual double getMax() = 0;

        virtual ~PopisAtributu() {};
        virtual PopisAtributu* clone() = 0;

    
};