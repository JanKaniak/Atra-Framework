#include "Attributes.h"

Attributes::Attributes(AttributeDescriptions* attributeDescs) {
            attributeDescs_ = attributeDescs;
            attributeFactory_.registerPrototype<AttributeInt>();
            /*atributeFactory_.registerPrototype<AtributeDouble>();
            atributeFactory_.registerPrototype<AtributeChar>();*/
}

void Attributes::addAttribute(std::string name, AttributeType type,AttributeTypeVariant minimum, AttributeTypeVariant maximum) {
            attributeDescs_->addDescription(name,type,minimum,maximum);
            attributes_.push_back(attributeFactory_.createAttribute(type));
            attributes_.at(attributes_.size() - 1)->setDescription(attributeDescs_->getLast());
            

};

void Attributes::setAttributeValue(std::string name, AttributeType type,AttributeTypeVariant value) {
    for (auto& attribute : attributes_) {
        if (attribute->getType() == type && attribute->getName().compare(name.c_str()) == 0) {
            attribute->setValue(value);
        }
    }
}

int Attributes::giveInt(std::string name) {
            for (auto& attribute : attributes_) {
                if (attribute->getName().compare(name) == 0 && attribute->getType() == AttributeType::INT) {
                        return std::get<int>(attribute->getValue());
                }
            }
            return INT_MAX;
}

