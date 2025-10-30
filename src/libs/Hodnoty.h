#pragma once
#include "Popisy.h"
#include "Atribut.h"
#include "AtributInt.h"
#include <vector>
#include <memory>
#include <map>

using AtributUptr = std::unique_ptr<Atribut>;

class AtributFactory {
private:
    std::map<TypAtributu, AtributUptr> prototypy;

public:
    Atribut* createAtribut(TypAtributu typ) {
        return prototypy[typ]->clone();
    }

    template <typename typAtributuT>
    void registerPrototype() {
        AtributUptr prototyp = std::make_unique<typAtributuT>();
        prototypy[prototyp->getTyp()] = std::move(prototyp);
    }
};

//------------------------------------------

using PopisUptr = std::unique_ptr<PopisAtributu>;

class PopisFactory {
private:
    std::map<TypAtributu, PopisUptr> prototypy;

public:
    PopisAtributu* createPopis(TypAtributu typ) {
        return prototypy[typ]->clone();
    }

    template <typename popisAtributuT>
    void registerPrototype() {
        PopisUptr prototyp = std::make_unique<popisAtributuT>();
        prototypy[prototyp->getTyp()] = std::move(prototyp);
    }
};

//------------------------------------------


class Hodnoty {
    private:
        Popisy* popisy_;
        std::vector<Atribut*> atributy_;
        AtributFactory atributFactory_;
        PopisFactory popisFactory_;

    public:
        Hodnoty(){};
        Hodnoty(Popisy* popisy){
            popisy_ = popisy;
            atributFactory_.registerPrototype<AtributInt>();
            popisFactory_.registerPrototype<PopisAtributu_int>();
        };
        
        void pridajAtribut(std::string meno, TypAtributu typ,int minimum, int maximum)
        {
            PopisAtributu* popis = popisFactory_.createPopis(typ);
            Atribut* atribut = atributFactory_.createAtribut(typ);
            
            popisy_->pridajPopis(popis);
            atribut->priradPopis(popisy_->getPosledny());
            atributy_.push_back(atribut);

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