#pragma once
#include <string>
#include "TypAtributu.h"
class PopisAtributu {
    protected:
        std::string meno_;
        TypAtributu typ_;
    
        public:
        PopisAtributu(){};
        PopisAtributu(std::string meno, TypAtributu typ) {
            meno_ = meno;
            typ_ = typ;
        };
        std::string getMeno() {return meno_;};
        TypAtributu getTyp() {return typ_;};
        void init(std::string meno, TypAtributu typ) {
            meno_ = meno;
            typ_ = typ;
        };

        virtual int getMin() = 0;
        virtual int getMax() = 0;

        virtual ~PopisAtributu() {};

    
};