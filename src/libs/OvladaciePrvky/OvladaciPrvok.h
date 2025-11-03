#pragma once
#include "../Atributy/Atribut.h"
#include <variant>

enum class DruhEdituDouble {
    SLIDER,
    VSLIDER,
    DRAG
};

enum class DruhEdituInt {
    SLIDER,
    VSLIDER,
    DRAG
};



class OvladaciPrvok
{
protected:
    std::string menoAtributu_;
    TypAtributu typAtributu_;
public:
    virtual void kresli() = 0;
    virtual std::string getMeno() = 0;
    virtual TypAtributu getTyp() = 0;
    virtual ~OvladaciPrvok() = default;
};

class OvladaciPrvokChar : public OvladaciPrvok {
    protected:
        char hodnota_;
        int minimum_;
        int maximum_;

    public:
        OvladaciPrvokChar() {};
        virtual OvladaciPrvokChar* clone() =0;
        virtual void priradAtribut(Atribut * atribut) = 0;


};



class OvladaciPrvokDouble : public OvladaciPrvok {
    protected:
        double hodnota_;
        double minimum_;
        double maximum_;

    public:
        DruhEdituDouble typ_;
        OvladaciPrvokDouble(DruhEdituDouble typ) {typ_ = typ;};
        virtual OvladaciPrvokDouble* clone() =0;
        virtual void priradAtribut(Atribut * atribut) = 0;


};




class OvladaciPrvokInt : public OvladaciPrvok {
    protected:
        int hodnota_;
        int minimum_;
        int maximum_;

    public:
        DruhEdituInt typ_;
        OvladaciPrvokInt(DruhEdituInt typ) {typ_ = typ;};
        virtual OvladaciPrvokInt* clone() =0;
        virtual void priradAtribut(Atribut * atribut) = 0;


};


