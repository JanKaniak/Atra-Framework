#pragma once
#include "../Descriptions/AtributeDescription.h"
#include <string>
#include <limits.h>
#include <iostream>

class Atribute {
    protected:
        AtributeDescription* desc_;
        
    
    public:
        AtributeType type_;

        Atribute(AtributeType type) : type_(type) {}

        inline std::string getName() { return desc_->getName(); }

        inline AtributeType getType() { return type_; }

        AtributeDescription* getDescription() {return desc_;};

        virtual ~Atribute() {};
        virtual Atribute* clone() = 0;
        virtual void setDescription(AtributeDescription* desc) = 0;
        virtual std::string getValue() = 0;

};

class AtributeInt : public Atribute {
    private:
        int value_;
    
        public:
            AtributeInt() : Atribute(AtributeType::Int) {};

            inline int getMin() { return desc_->getMin(); }

            inline int getMaximum() { return desc_->getMax(); }

            void setValue(int value) { value_ = (value_ > getMin() && value_ < getMaximum()) ? value : value_; }

            AtributeInt* clone() override { return new AtributeInt(*this); }

            void setDescription(AtributeDescription* desc) override {
                desc_ = desc;
                value_ = desc_->getMin();
            }

            std::string getValue() override { return std::to_string(value_);}
};

class AtributeDouble : public Atribute {
    private:
        double value_;
    
        public:
            AtributeDouble() : Atribute(AtributeType::Double) {};

            const double getMin() {
                return desc_->getMin(); 
            }

            const double getMaximum() {
                return desc_->getMax();
            }

            void setValue(double value) { value_ = (value_ > getMin() && value_ < getMaximum()) ? value : value_; }

            AtributeDouble* clone() override { return new AtributeDouble(*this); }

            void setDescription(AtributeDescription* desc) override {
                desc_ = desc;
                value_ = desc_->getMin();
            }

            std::string getValue() {return std::to_string(value_); }
};

class AtributeChar : public Atribute {
    private:
        char value_[1];
    
        public:
            AtributeChar() : Atribute(AtributeType::Char) {}

            int getMin() {
                return desc_->getMin(); 
            }

            int getMaximum() {
                return desc_->getMax();
            }

            void setValue(char *value) { value_[0] = (sizeof(value) >= getMin()) ? value[0] : value_[0]; }

            AtributeChar* clone() override { return new AtributeChar(*this); }

            void setDescription(AtributeDescription* desc) override { desc_ = desc; }

            std::string getValue() { return std::string(1,value_[0]);}
};