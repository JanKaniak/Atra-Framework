#pragma once
#include "AtributeDescription.h"
#include <vector>
class Descriptions {
    private:
        std::vector<AtributeDescription*> descs_;
    public:
        Descriptions(){};
        void addDescription(AtributeDescription* desc) { descs_.push_back(desc); }
        AtributeDescription* getDescription(std::string name, AtributeType type);

        inline AtributeDescription* getLast() { return descs_.at(descs_.size() - 1); }

        inline int getNumberOfDescriptions() { return descs_.size();}

};