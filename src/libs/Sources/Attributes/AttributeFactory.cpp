#include "AttributeFactory.h"

AttributeFactory *AttributeFactory::instance_ = nullptr;

AttributeFactory *AttributeFactory::getInstance()
{
    if (instance_ == nullptr)
    {
        instance_ = new AttributeFactory();
    }
    return instance_;
}

AttributeUptr AttributeFactory::createAttribute(AttributeType type)
{
    if (prototypes_.find(type) == prototypes_.end())
    {
        return nullptr;
    }
    return prototypes_[type]->clone();
}

