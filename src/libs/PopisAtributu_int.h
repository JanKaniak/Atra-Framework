#pragma once
#include "PopisAtributu.h"
#include <iostream>
class PopisAtributu_int : public PopisAtributu {
    private:
        int min_ = 10;
        int max_ = 50;
    public:
        PopisAtributu_int() : PopisAtributu(TypAtributu::Int) {}

        void priradNastavenia(std::string meno, int minimum, int maximum) {
            if (minimum < maximum) {
                min_ = minimum;
                max_ = maximum;
            }
            meno_ = meno;
        }
        
        double getMin() { return min_; }

        double getMax() { return max_; }

        PopisAtributu_int* clone() override { return new PopisAtributu_int(*this); }
        void setLimit(double minimum, double maximum) override { 
            if (minimum < maximum) {
                min_ = minimum;
                max_ = maximum;
            }
        }
};