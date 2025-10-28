#pragma once
#include "Hodnoty.h"
#include "IntSlider.h"
#include <iostream>
#include <map>
#include <memory>

using IntEditUptr = std::unique_ptr<OvladaciPrvokInt>;


class IntEditFactory {
private:
    std::map<DruhEdituInt, IntEditUptr> prototypy;

public:
    OvladaciPrvokInt* createIntEdit(DruhEdituInt typ) {
        return prototypy[typ]->clone();
    }

    template <typename DruhEdituIntT>
    void registerPrototype() {
        IntEditUptr prototyp = std::make_unique<DruhEdituIntT>();
        prototypy[prototyp->typ_] = std::move(prototyp);
    }
};






class Formular {
    private:
        Hodnoty* hodnoty_;
        std::vector<OvladaciPrvok*> prvky_;
        IntEditFactory factory_;

    public:
        Formular(Hodnoty* hodnoty) {
            hodnoty_ = hodnoty;
            factory_.registerPrototype<IntSlider>();
            factory_.registerPrototype<IntDrag>();
            factory_.registerPrototype<IntVSSlider>();
        }

        void pridajAtribut(DruhEdituInt typPosuvaca,std::string meno, TypAtributu typ,int minimum, int maximum) {
            hodnoty_->pridajAtribut(meno, typ, minimum, maximum);
            OvladaciPrvokInt* ovladac;
            switch (typ)
            {
            case TypAtributu::Int:
                    ovladac = factory_.createIntEdit(typPosuvaca);
                    ovladac->priradAtribut(hodnoty_->getPosledny());
                    prvky_.push_back(ovladac);
                    break;
            default:
                break;
            }
        }

        bool rovnakyNazov(std::string meno) {
            for (OvladaciPrvok* prvok : prvky_) {
                if (prvok->getMeno().compare(meno) == 0) {
                    std::cout << "rovnake\n";
                    return true;
                }
            }
            std::cout << "nemrovnake\n";
            return false;
        }

        void kresli() {
            for (OvladaciPrvok* prvok : prvky_) {
                prvok->kresli();
            }
        }

        int getPocetAtributov() {
            return hodnoty_->getPocet();
        }

};


