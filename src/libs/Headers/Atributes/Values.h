#pragma once
#include "Descriptions.h"
#include "Atribute.h"
#include <vector>
#include <memory>
#include <map>

using AtributeUptr = std::unique_ptr<Atribute>;

class AtributeFactory {
private:
    std::map<AtributeType, AtributeUptr> prototypes_;

public:
    inline Atribute* createAtribute(AtributeType type) { return prototypes_[type]->clone(); }

    template <typename atributeTypeT>
    void registerPrototype() {
        AtributeUptr prototype = std::make_unique<atributeTypeT>();
        prototypes_[prototype->getType()] = std::move(prototype);
    }
};

//------------------------------------------

using DescUptr = std::unique_ptr<AtributeDescription>;

class DescFactory {
private:
    std::map<AtributeType, DescUptr> prototypes_;

public:
    inline AtributeDescription* createDesc(AtributeType type) { return prototypes_[type]->clone(); }

    template <typename atributeDescriptionT>
    void registerPrototype() {
        DescUptr prototype = std::make_unique<atributeDescriptionT>();
        prototypes_[prototype->getType()] = std::move(prototype);
    }
};

//------------------------------------------


class Values {
    private:
        Descriptions* descs_;
        std::vector<Atribute*> atributes_;
        AtributeFactory atributeFactory_;
        DescFactory descFactory_;

    public:
        Values(){};
        Values(Descriptions* descs);
        
        void addAtributeDescription(std::string name, AtributeType type,double minimum, double maximum);

        void setAtributeValue(std::string name, AtributeType type,std::string value);

        int giveInt(std::string name);

        inline Atribute* getLast() { return atributes_.at(atributes_.size() - 1); }

        inline int getSize() { return atributes_.size(); }

        inline Atribute* giveAtribute(int rank) { return atributes_.at(rank); }

        void setValueOfLast(AtributeType type,std::string value) {
            if (!value.empty() || type == AtributeType::Char)
                atributes_.at(atributes_.size())->setValue(value);
        }
};