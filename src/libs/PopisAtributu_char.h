#pragma once
#include "PopisAtributu.h"
#include <iostream>
class PopisAtributu_char : public PopisAtributu {
   private:
        int min_ = 0;
        int max_ = 20;
    public:
        PopisAtributu_char() : PopisAtributu(TypAtributu::CHAR) {}
        
        double getMin() override {
            return min_;
        }

        double getMax() override {
            return max_;
        }

        PopisAtributu_char* clone() override {return new PopisAtributu_char(*this); }

        void setLimit(double minimum, double maximum) override {
            if (minimum < maximum) {
                min_ = minimum;
                max_ = maximum;
            }
        }
};