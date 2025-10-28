#pragma once
#include "Atribut.h"
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


