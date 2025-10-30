#pragma once
#include "PopisAtributu_int.h"
#include "Atribut.h"
#include <limits.h>
#include <iostream>
class AtributChar : public Atribut {
    private:
        char hodnota_;
    
        public:
            AtributChar(){};
            AtributChar(PopisAtributu* popis)
            {
                popis_ = popis;
            };

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
                if (sizeof(hodnota) > popis_->getMin() && (sizeof(hodnota) < popis_->getMax())) {
                    hodnota_ = hodnota;
                }
            }
};