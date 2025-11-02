#pragma once
#include "PopisAtributu.h"
#include <iostream>
class PopisAtributu_double : public PopisAtributu {
   private:
        double min_ = 10;
        double max_ = 50;
    public:
        PopisAtributu_double() : PopisAtributu(TypAtributu::Double) {}
        double getMin() {
            return min_;
        }

        double getMax() {
            return max_;
        }

        PopisAtributu_double* clone() override { return new PopisAtributu_double(*this); }

        void setLimit(double minimum, double maximum) override { 
            if (minimum < maximum) {
                min_ = minimum;
                max_ = maximum;
            }
        }
};