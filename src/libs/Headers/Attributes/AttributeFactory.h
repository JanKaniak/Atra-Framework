#pragma once
#include "Attribute.h"

using AttributeUptr = std::unique_ptr<Attribute>;

class AttributeFactory
{
private:
    std::map<AttributeType, AttributeUptr> prototypes_;
    static AttributeFactory *instance_;
    AttributeFactory() = default;

public:
    AttributeUptr createAttribute(AttributeType type);
    static AttributeFactory *getInstance();
    template <AttributeType EnumTypeT>
    void registerPrototype(AttributeUptr prototype)
    {
        if (prototypes_.find(EnumTypeT) == prototypes_.end())
        {
            prototypes_[EnumTypeT] = std::move(prototype);
        }
    }
};
