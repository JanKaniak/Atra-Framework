#include "Attributes.h"

Attributes::Attributes() {
            attributeDescs_ = std::make_unique<AttributeDescriptions>();
            attributeFactory_.registerPrototype<AttributeInt>();
            /*atributeFactory_.registerPrototype<AtributeDouble>();
            atributeFactory_.registerPrototype<AtributeChar>();*/
}

void Attributes::addAttribute(std::string agentName,std::string attributeName, AttributeType type, AttributeTypeVariant minimum, AttributeTypeVariant maximum) {
            attributeDescs_->addDescription(agentName,attributeName,type,minimum,maximum);
            attributes_.push_back(attributeFactory_.createAttribute(type));
            attributes_.at(attributes_.size() - 1)->setDescription(attributeDescs_->getLast());
            

};

void Attributes::createAttributes() {
    for (int i = 0; i < attributeDescs_->getSize(); i++) {
        AttributeDescription* desc = attributeDescs_->getDescription(i);
        attributes_.push_back(attributeFactory_.createAttribute(desc->getType()));
        attributes_.at(attributes_.size() - 1)->setDescription(desc);
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

bool Attributes::deleteAttribute(Attribute *attribute) {
    for (int i = 0; i < attributes_.size(); i++) {
        if (attributes_.at(i).get() != attribute) {
            continue;
        }
        if (attributeDescs_->deleteDescription(attribute->getDescription())) {
            attributes_.erase(attributes_.begin()+i);
            return true;
        }

    }
    return false;
}

