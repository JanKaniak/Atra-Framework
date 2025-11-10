#include "Descriptions.h"

AtributeDescription* Descriptions::getDescription(std::string name, AtributeType type) {
            for (auto desc : Descriptions::descs_) {
                if (desc->getName().compare(name) == 0 && desc->getType() == type) {
                    return desc;
                }
            }
            return nullptr;
}