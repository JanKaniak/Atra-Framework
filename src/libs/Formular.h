#pragma once
#include "Hodnoty.h"
#include "IntSlider.h"
#include <iostream>
#include <map>
#include <memory>

class Formular {
    private:
        Hodnoty* hodnoty_;
        std::vector<OvladaciPrvok*> prvky_;

    public:
        Formular(Hodnoty* hodnoty) {
            hodnoty_ = hodnoty;
        }

        void pridajAtribut(int typPosuvaca,std::string meno, TypAtributu typ,int minimum, int maximum) {
            hodnoty_->pridajAtribut(meno, typ, minimum, maximum);
            switch (typ)
            {
            case TypAtributu::Int:
                switch (typPosuvaca)
                {
                case 0:
                    prvky_.push_back(new IntSlider(hodnoty_->getPosledny()));
                    break;
                case 1:
                    prvky_.push_back(new IntDrag(hodnoty_->getPosledny()));
                    break;

                case 2:
                    prvky_.push_back(new IntVSSlider(hodnoty_->getPosledny()));
                    break;
                default:
                    break;
                }
                
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

enum class DruhEdituInt {
    SLIDER,
    VSLIDER
};

class IntEdit {
private:
    DruhEdituInt typ_;
public:
    IntEdit(DruhEdituInt typ) {
        typ_ = typ;
};
    virtual IntEdit* clone() =0;

};
using IntEditUptr = std::unique_ptr <IntEdit>;

class IntEditFactory {
private:
    std::map<DruhEdituInt, IntEditUptr> protypy;
};