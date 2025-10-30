#pragma once
#include "PopisAtributu.h"
#include <iostream>
class PopisAtributu_double : public PopisAtributu {
   private:
        double min_ = 10;
        double max_ = 50;
    public:
        PopisAtributu_int(std::string meno, TypAtributu typ, double minimum, double maximum) : PopisAtributu(meno,typ) {
            if (min_ < max_) {
                min_ = minimum;
                max_ = maximum;
            }
        }
        double getMin() {
            return min_;
        }

        double getMax() {
            return max_;
        }
};