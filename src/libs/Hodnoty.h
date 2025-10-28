#pragma once
#include "Popisy.h"
#include "Atribut.h"
#include "AtributInt.h"
#include <vector>
class Hodnoty {
    private:
        Popisy* popisy_;
        std::vector<Atribut*> atributy_;

    public:
        Hodnoty(){};
        Hodnoty(Popisy* popisy){
            popisy_ = popisy;
        };
        
        void pridajAtribut(std::string meno, TypAtributu typ,int minimum, int maximum)
        {
            
            switch (typ)
            {
            case TypAtributu::Int:
                popisy_->pridajPopis(new PopisAtributu_int(meno,typ, minimum, maximum));
                atributy_.push_back(new AtributInt(popisy_->getPosledny()));
                break;
            
            default:
                break;
            }
        };

        int dajInt(std::string meno) {
            for (auto atribut : atributy_) {
                if (atribut->getMeno().compare(meno) == 0 && atribut->getTyp() == TypAtributu::Int) {
                    if (AtributInt* aatribut = dynamic_cast<AtributInt*>(atribut)) {
                        return aatribut->getHodnota();
                    }
                }
            }
            return -1;
        }

        Atribut* getPosledny() {
            return atributy_.at(atributy_.size() - 1);
        }

        int getPocet() {
            return atributy_.size();
        }
};