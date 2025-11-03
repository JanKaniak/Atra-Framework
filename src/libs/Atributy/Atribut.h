#pragma once
#include "../Popisy/PopisAtributu.h"
#include <string>
#include <limits.h>
#include <iostream>

class Atribut {
    protected:
        PopisAtributu* popis_;
        
    
    public:
        TypAtributu typ_;

        Atribut(TypAtributu typ) : typ_(typ) {}

        std::string getMeno() {
            return popis_->getMeno();
        }

        TypAtributu getTyp() {
            return typ_;
        }

        virtual ~Atribut() {};
        virtual Atribut* clone() = 0;
        virtual void priradPopis(PopisAtributu* popis) = 0;

};

class AtributInt : public Atribut {
    private:
        int hodnota_;
    
        public:
            AtributInt() : Atribut(TypAtributu::Int) {};

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

            AtributInt* clone() override { return new AtributInt(*this); }

            void priradPopis(PopisAtributu* popis) override {
                popis_ = popis;
                hodnota_ = popis->getMin();
            }
};

class AtributDouble : public Atribut {
    private:
        double hodnota_;
    
        public:
            AtributDouble() : Atribut(TypAtributu::Double) {};

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

            AtributDouble* clone() override { return new AtributDouble(*this); }

            void priradPopis(PopisAtributu* popis) override {
                popis_ = popis;
                hodnota_ = popis->getMin();
            }
};

class AtributChar : public Atribut {
    private:
        char hodnota_;
    
        public:
            AtributChar() : Atribut(TypAtributu::Char) {}

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
                hodnota_ = hodnota;
            }

            AtributChar* clone() override { return new AtributChar(*this); }

            void priradPopis(PopisAtributu* popis) override {
                popis_ = popis;
            }
};