#include "Values.h"

Values::Values(Descriptions* descs) {
            descs_ = descs;
            atributeFactory_.registerPrototype<AtributeInt>();
            atributeFactory_.registerPrototype<AtributeDouble>();
            atributeFactory_.registerPrototype<AtributeChar>();

            descFactory_.registerPrototype<AtributeDescription_int>();
            descFactory_.registerPrototype<AtributeDescription_double>();
            descFactory_.registerPrototype<AtributeDescription_char>();
}

void Values::addAtributeDescription(std::string name, AtributeType type,double minimum, double maximum) {
            AtributeDescription* desc = descFactory_.createDesc(type);
            desc->setName(name);
            desc->setLimit(minimum, maximum);
            
            Atribute* atribute = atributeFactory_.createAtribute(type);
            
            descs_->addDescription(desc);
            atribute->setDescription(descs_->getLast());
            atributes_.push_back(atribute);

};

void Values::setAtributeValue(std::string name, AtributeType type,std::string value) {
    for (auto atribute : atributes_) {
        if (atribute->getType() == type && atribute->getName().compare(name.c_str()) == 0) {
            atribute->setValue(value);
        }
    }

int Values::giveInt(std::string name) {
            for (auto atribute : atributes_) {
                if (atribute->getName().compare(name) == 0 && atribute->getType() == AtributeType::Int) {
                    if (AtributeInt* aatribute = dynamic_cast<AtributeInt*>(atribute)) {
                        return std::stoi(aatribute->getValue());
                    }
                }
            }
            return -1;
}

}