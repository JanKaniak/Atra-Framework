#pragma once
#include "PopisAtributu_char.h"
#include "Atribut.h"
#include <limits.h>
#include <iostream>
class AtributChar : public Atribut {
    private:
        char hodnota_;
    
        public:
            AtributChar() : Atribut(TypAtributu::CHAR) {}

            char getHodnota() {
                return hodnota_;
            }

            int getMin() {
                return popis_->getMin(); 
            }

            int getMaximum() {
                return popis_->getMax();
            }

            void upravHodnotu(char hodnota) {
                hodnota_ = hodnota;
            }

            AtributChar* clone() override { return new AtributChar(*this); }

            void priradPopis(PopisAtributu* popis) override {
                popis_ = popis;
            }
};