#pragma once
#include "Attribute.h"

using AttributeUptr = std::unique_ptr<Attribute>;

/// Factory that creates attribute instances from registered prototypes.
///
/// This singleton stores one prototype per `AttributeType` and clones it when a new attribute is requested.
class AttributeFactory
{
private:
    std::map<AttributeType, AttributeUptr> prototypes_;
    static AttributeFactory *instance_;
    AttributeFactory() = default;

public:
    /// Create a new attribute instance for the given type.
    ///
    /// The implementation clones the registered prototype for the requested attribute type.
    AttributeUptr createAttribute(AttributeType type);

    /// Retrieve the singleton factory instance.
    static AttributeFactory *getInstance();

    /// Register a concrete attribute prototype for the given attribute type.
    ///
    /// Only the first registered prototype is kept for each `AttributeType`.
    template <AttributeType EnumTypeT>
    void registerPrototype(AttributeUptr prototype)
    {
        if (prototypes_.find(EnumTypeT) == prototypes_.end())
        {
            prototypes_[EnumTypeT] = std::move(prototype);
        }
    }
};
