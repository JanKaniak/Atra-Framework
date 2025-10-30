#pragma once
#include "PopisAtributu_double.h"
#include "Atribut.h"
#include <limits.h>
#include <iostream>
class AtributDouble : public Atribut {
    private:
        double hodnota_;
    
        public:
            AtributDouble(){};
            AtributDouble(PopisAtributu* popis)
            {
                popis_ = popis;
                hodnota_ = popis_->getMin();

                
            };

            double getHodnota() {
                return hodnota_;
            }

            const double getMin() {
                return popis_->getMin(); 
            }

            const double getMaximum() {
                return popis_->getMax();
            }

            void upravHodnotu(double hodnota) {
                if (hodnota_ > popis_->getMin() && hodnota_ < popis_->getMax()) {
                    hodnota_ = hodnota;
                }
            }
};