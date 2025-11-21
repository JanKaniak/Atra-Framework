#pragma once
#include "../Descriptions/AtributeDescription.h"
#include <string>
#include <limits.h>
#include <iostream>

class Atribute {
    protected:
        AtributeDescription* desc_;
        
    
    public:
        //AtributeType type_;
        inline std::string getName() { return desc_->getName(); }

        inline AtributeType getType() { return desc_->getType(); }

        AtributeDescription* getDescription() {return desc_;};

        virtual ~Atribute() {};
        virtual Atribute* clone() = 0;
        virtual void setDescription(AtributeDescription* desc) = 0;
        virtual std::string getValue() = 0;
        virtual void setValue(std::string value) = 0;

};

class AtributeInt : public Atribute {
    private:
        int value_;
    
        public:
            AtributeInt() {desc_ = new AtributeDescription_int();};

            inline int getMin() { return desc_->getMin(); }

            inline int getMaximum() { return desc_->getMax(); }

            void setValue(std::string value) override { value_ = (std::stoi(value) > getMin() && std::stoi(value) < getMaximum()) ? std::stoi(value) : value_; }

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
            AtributeDouble() {desc_ = new AtributeDescription_double();};

            const double getMin() {
                return desc_->getMin(); 
            }

            const double getMaximum() {
                return desc_->getMax();
            }

            void setValue(std::string value) override { value_ = (std::atof(value.c_str()) > getMin() && std::atof(value.c_str()) < getMaximum()) ? std::atof(value.c_str()) : value_; }

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
            AtributeChar() {desc_ = new AtributeDescription_char();};

            int getMin() {
                return desc_->getMin(); 
            }

            int getMaximum() {
                return desc_->getMax();
            }

            void setValue(std::string value) override { value_[0] = (sizeof(value) >= getMin()) ? value[0] : value_[0]; }

            AtributeChar* clone() override { return new AtributeChar(*this); }

            void setDescription(AtributeDescription* desc) override { desc_ = desc; }

            std::string getValue() { return std::string(1,value_[0]);}
};