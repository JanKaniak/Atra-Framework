#pragma once
#include "PopisAtributu_int.h"
#include "Atribut.h"
#include <limits.h>
#include <iostream>
class AtributInt : public Atribut {
    private:
        int hodnota_;
    
        public:
            AtributInt() : Atribut(TypAtributu::Int) {};

            int getHodnota() {
                return hodnota_;
            }

            const int getMin() {
                return popis_->getMin(); 
            }

            const int getMaximum() {
                return popis_->getMax();
            }

            void upravHodnotu(int hodnota) {
                if (hodnota_ > popis_->getMin() && hodnota_ < popis_->getMax()) {
                    hodnota_ = hodnota;
                }
            }

            AtributInt* clone() override { return new AtributInt(*this); }

            void priradPopis(PopisAtributu* popis) override {
                popis_ = popis;
                hodnota_ = popis->getMin();
            }
};