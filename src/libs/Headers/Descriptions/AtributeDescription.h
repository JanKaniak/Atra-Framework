#pragma once
#include <string>

enum class AtributeType {
    Int,
    Double,
    Bool,
    Char
};

class AtributeDescription {
    protected:
        std::string name_;
        AtributeType type_;
        
    
        public:
        AtributeDescription(AtributeType type) : type_(type) {};
        inline std::string getName() {return name_;};
        inline AtributeType getType() {return type_;};
        virtual double getMin() = 0;
        virtual double getMax() = 0;
        inline void setName(std::string name) { name_ = name; };


        virtual ~AtributeDescription() {};
        virtual AtributeDescription* clone() = 0;
        virtual void setLimit(double minimum, double maximum) = 0;

    
};

class AtributeDescription_int : public AtributeDescription {
    private:
        int min_ = 10;
        int max_ = 50;
    public:
        AtributeDescription_int() : AtributeDescription(AtributeType::Int) {}
        inline double getMin() override { return min_; }
        inline double getMax() override { return max_; }
        AtributeDescription_int* clone() override;
        void setLimit(double minimum, double maximum) override ;
};


class AtributeDescription_double : public AtributeDescription {
   private:
        double min_ = 10;
        double max_ = 50;
    public:
        AtributeDescription_double() : AtributeDescription(AtributeType::Double) {}
        inline double getMin() override { return min_; }
        inline double getMax() override { return max_; }
        AtributeDescription_double* clone() override;
        void setLimit(double minimum, double maximum) override;

        
};

class AtributeDescription_char : public AtributeDescription {
   private:
        int min_ = 0;
        int max_ = 1;
    public:
        AtributeDescription_char() : AtributeDescription(AtributeType::Char) {}
        
        inline double getMin() override { return min_; }

        inline double getMax() override { return max_; }

        AtributeDescription_char* clone() override;

        void setLimit(double minimum, double maximum) override;
};