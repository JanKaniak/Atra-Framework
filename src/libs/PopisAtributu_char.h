#pragma once
#include "PopisAtributu.h"
#include <iostream>
class PopisAtributu_char : public PopisAtributu {
   private:
        int min_ = 0;
        int max_ = 20;
    public:
        PopisAtributu_int(std::string meno, TypAtributu typ, int minimum, int maximum) : PopisAtributu(meno,typ) {
            if (min_ < max_) {
                min_ = minimum;
                max_ = maximum;
            }
        }
        int getMin() {
            return min_;
        }

        int getMax() {
            return max_;
        }
};