#pragma once
#include "PopisAtributu.h"
#include <iostream>
class PopisAtributu_int : public PopisAtributu {
    private:
        int min_ = 10;
        int max_ = 50;

    public:
        PopisAtributu_int(std::string meno, TypAtributu typ, int minimum, int maximum) {
            meno_ = meno;
            typ_ = typ;
            min_ = minimum;
            max_ = maximum;

            std::cout << "popis min: " << min_ << "a max: " << max_ << "\n";
        }
        int getMin() {
            return min_;
        }

        int getMax() {
            return max_;
        }
};