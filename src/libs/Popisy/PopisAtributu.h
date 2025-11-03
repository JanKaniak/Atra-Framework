#pragma once
#include <string>
#include "TypAtributu.h"
class PopisAtributu {
    protected:
        std::string meno_;
        TypAtributu typ_;
        
    
        public:
        PopisAtributu(TypAtributu typ) : typ_(typ) {};
        std::string getMeno() {return meno_;};
        TypAtributu getTyp() {return typ_;};
        virtual double getMin() = 0;
        virtual double getMax() = 0;
        void setMeno(std::string meno) { meno_ = meno; };


        virtual ~PopisAtributu() {};
        virtual PopisAtributu* clone() = 0;
        virtual void setLimit(double minimum, double maximum) = 0;

    
};

class PopisAtributu_int : public PopisAtributu {
    private:
        int min_ = 10;
        int max_ = 50;
    public:
        PopisAtributu_int() : PopisAtributu(TypAtributu::Int) {}

        void priradNastavenia(std::string meno, int minimum, int maximum) {
            if (minimum < maximum) {
                min_ = minimum;
                max_ = maximum;
            }
            meno_ = meno;
        }
        
        double getMin() { return min_; }

        double getMax() { return max_; }

        PopisAtributu_int* clone() override { return new PopisAtributu_int(*this); }
        void setLimit(double minimum, double maximum) override { 
            if (minimum < maximum) {
                min_ = minimum;
                max_ = maximum;
            }
        }
};


class PopisAtributu_double : public PopisAtributu {
   private:
        double min_ = 10;
        double max_ = 50;
    public:
        PopisAtributu_double() : PopisAtributu(TypAtributu::Double) {}
        double getMin() {
            return min_;
        }

        double getMax() {
            return max_;
        }

        PopisAtributu_double* clone() override { return new PopisAtributu_double(*this); }

        void setLimit(double minimum, double maximum) override { 
            if (minimum < maximum) {
                min_ = minimum;
                max_ = maximum;
            }
        }
};

class PopisAtributu_char : public PopisAtributu {
   private:
        int min_ = 0;
        int max_ = 20;
    public:
        PopisAtributu_char() : PopisAtributu(TypAtributu::Char) {}
        
        double getMin() override {
            return min_;
        }

        double getMax() override {
            return max_;
        }

        PopisAtributu_char* clone() override {return new PopisAtributu_char(*this); }

        void setLimit(double minimum, double maximum) override {
            if (minimum < maximum) {
                min_ = minimum;
                max_ = maximum;
            }
        }
};