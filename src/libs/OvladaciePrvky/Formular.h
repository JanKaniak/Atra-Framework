#pragma once
#include "../Atributy/Hodnoty.h"
#include "NumericInput.h"
#include "CharacterInput.h"
#include "json.hpp"


#include <iostream>
#include <map>
#include <memory>
#include <functional>
#include <variant>
#include <fstream> 



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

//--------------------------------------------------

using DoubleEditUptr = std::unique_ptr<OvladaciPrvokDouble>;
class DoubleEditFactory {
private:
    std::map<DruhEdituDouble, DoubleEditUptr> prototypy;

public:
    OvladaciPrvokDouble* createDoubleEdit(DruhEdituDouble typ) {
        return prototypy[typ]->clone();
    }

    template <typename DruhEdituDoubleT>
    void registerPrototype() {
        DoubleEditUptr prototyp = std::make_unique<DruhEdituDoubleT>();
        prototypy[prototyp->typ_] = std::move(prototyp);
    }
};

//---------------------------------------------------

using CharEditUptr = std::unique_ptr<OvladaciPrvokChar>;
class CharEditFactory {
private:
    CharEditUptr prototyp;

public:
    OvladaciPrvokChar* createCharEdit() {
        return prototyp->clone();
    }

    template <typename DruhEdituCharT>
    void registerPrototype() {
        prototyp = std::make_unique<DruhEdituCharT>();
    }
};

//---------------------------------------------------


using typAtributuEnum = std::variant<DruhEdituDouble,DruhEdituInt>;
using typHranice = std::variant<int,double>;

class Formular {
    private:
        Hodnoty* hodnoty_;
        std::vector<OvladaciPrvok*> prvky_;
        IntEditFactory factoryInt_;
        DoubleEditFactory factoryDouble_;
        CharEditFactory factoryChar_;

        std::map<TypAtributu,std::function<void(int,std::string,TypAtributu,std::string,std::string)>> rozhodnutie_{ 
            {TypAtributu::Int,
                [this](int posuvac,std::string meno,TypAtributu typ,std::string min,std::string max) {
                    DruhEdituInt intPosuvac = static_cast<DruhEdituInt>(posuvac);
                    this->pridajAtribut(intPosuvac,meno,typ, std::stoi(min), std::stoi(max));
         }},
            {TypAtributu::Double,
                [this](int posuvac,std::string meno,TypAtributu typ,std::string min,std::string max) {
                    DruhEdituDouble doublePosuvac = static_cast<DruhEdituDouble>(posuvac);
                    this->pridajAtribut(doublePosuvac,meno,typ, std::atof(min.c_str()), std::atof(max.c_str()));
         }},
            {TypAtributu::Char,
                [this](int posuvac,std::string meno,TypAtributu typ,std::string min,std::string max) {
                    this->pridajAtribut(meno, typ, std::stoi(min), std::stoi(max));
                }

            }
            
        
        };

    public:
        Formular(Hodnoty* hodnoty) {
            hodnoty_ = hodnoty;

            factoryInt_.registerPrototype<IntSlider>();
            factoryInt_.registerPrototype<IntVSSlider>();
            factoryInt_.registerPrototype<IntDrag>();

            factoryDouble_.registerPrototype<DoubleSlider>();
            factoryDouble_.registerPrototype<DoubleVSSlider>();
            factoryDouble_.registerPrototype<DoubleDrag>();

            factoryChar_.registerPrototype<CharInput>();
        }

        void pridajAtributWrapper(int posuvac,std::string meno,TypAtributu typ,std::string min,std::string max) { 
            rozhodnutie_[typ](posuvac,meno,typ,min,max);
        }

        void pridajAtribut(DruhEdituInt typPosuvaca,std::string meno, TypAtributu typ,int minimum, int maximum) {
            hodnoty_->pridajAtribut(meno, typ, minimum, maximum);
            OvladaciPrvokInt* ovladac = factoryInt_.createIntEdit(typPosuvaca);
            ovladac->priradAtribut(hodnoty_->getPosledny());
            prvky_.push_back(ovladac);
        }

        void pridajAtribut(DruhEdituDouble typPosuvaca,std::string meno, TypAtributu typ,double minimum, double maximum) {
            hodnoty_->pridajAtribut(meno, typ, minimum, maximum);
            OvladaciPrvokDouble* ovladac = factoryDouble_.createDoubleEdit(typPosuvaca);
            ovladac->priradAtribut(hodnoty_->getPosledny());
            prvky_.push_back(ovladac);
        }

        void pridajAtribut(std::string meno, TypAtributu typ, int minimum, int maximum) {
            hodnoty_->pridajAtribut(meno,typ,minimum,maximum);
            OvladaciPrvokChar* ovladac = factoryChar_.createCharEdit();
            ovladac->priradAtribut(hodnoty_->getPosledny());
            prvky_.push_back(ovladac);
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

        void nacitajZoSuboru(const char* cesta) {
            std::ifstream subor(cesta);
            nlohmann::json jsonSubor = nlohmann::json::parse(subor);
            subor.close();

            for (auto it : jsonSubor)
            {
                this->pridajAtributWrapper(0,it.at("Meno Atributu").get<std::string>(),static_cast<TypAtributu>(it.at("Typ Atributu").get<int>()),it.at("Minimum").get<std::string>(),it.at("Maximum").get<std::string>());
            }
        }

        void ulozDoSuboru() {
        }

};


