#pragma once
#include "PopisAtributu_int.h"
#include "Atribut.h"
#include <limits.h>
#include <iostream>
class AtributInt : public Atribut {
    private:
        int hodnota_;
    
        public:
            AtributInt(){};
            AtributInt(PopisAtributu* popis)
            {
                popis_ = popis;
                hodnota_ = popis_->getMin();

                std::cout << "atributint min: " << popis_->getMin() << "a max: " << popis_->getMax() << "hodnota: " << hodnota_ << "\n";
                
            };

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
};