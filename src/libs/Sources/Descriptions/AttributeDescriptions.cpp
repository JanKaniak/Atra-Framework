#include "AttributeDescriptions.h"

AttributeDescriptions::AttributeDescriptions() {
    descFactory_.registerPrototype<AttributeDescription_int>();
    //descFactory_.registerPrototype<AtributeDescription_double>();
    //descFactory_.registerPrototype<AtributeDescription_char>();
}

void AttributeDescriptions::addDescription(std::string agentName,std::string attributeName, AttributeType type,AttributeTypeVariant minimum, AttributeTypeVariant maximum)  { 
            attributeDescs_.push_back(descFactory_.createDesc(type));
            getLast()->setName(attributeName);
            getLast()->setAgent(agentName);
            getLast()->setLimit(minimum,maximum);
            
         }


AttributeDescription* AttributeDescriptions::getDescription(std::string name, AttributeType type) {
            for (auto& desc : attributeDescs_) {
                if (desc->getName().compare(name) == 0 && desc->getType() == type) {
                    return desc.get();
                }
            }
            return nullptr;
}