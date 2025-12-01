#pragma once
#include "AttributeDescription.h"
#include <vector>
#include <memory>
#include <map>

using DescUptr = std::unique_ptr<AttributeDescription>;

class DescFactory {
private:
    std::map<AttributeType, DescUptr> prototypes_;

public:
    inline DescUptr createDesc(AttributeType type) { return prototypes_[type]->clone(); }

    template <typename AttributeDescriptionT>
    void registerPrototype() {
        DescUptr prototype = std::make_unique<AttributeDescriptionT>();
        prototypes_[prototype->getType()] = std::move(prototype);
    }
};


class AttributeDescriptions {
    private:
        std::vector<std::unique_ptr<AttributeDescription>> attributeDescs_;
        DescFactory descFactory_;
    public:
        AttributeDescriptions();
        void addDescription(std::string name, AttributeType type,AttributeTypeVariant minimum, AttributeTypeVariant maximum);
        AttributeDescription* getDescription(std::string name, AttributeType type);

        inline AttributeDescription* getLast() { 
            if (attributeDescs_.empty()) {
                return nullptr;
            }
            return attributeDescs_.at(attributeDescs_.size() - 1).get(); 
        }

        inline int getNumberOfDescriptions() { return attributeDescs_.size();}

};