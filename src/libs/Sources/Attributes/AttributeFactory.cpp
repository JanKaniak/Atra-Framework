#include "AttributeFactory.h"

AttributeFactory *AttributeFactory::instance_ = nullptr;

/// Retrieve the singleton factory instance.
///
/// Creates the instance on first use.
AttributeFactory *AttributeFactory::getInstance()
{
    if (instance_ == nullptr)
    {
        instance_ = new AttributeFactory();
    }
    return instance_;
}


/// Create a new attribute instance for the requested type.
///
/// Returns nullptr if no prototype is registered for the requested type.
AttributeUptr AttributeFactory::createAttribute(AttributeType type)
{
    if (prototypes_.find(type) == prototypes_.end())
    {
        return nullptr;
    }
    return prototypes_[type]->clone();
}

