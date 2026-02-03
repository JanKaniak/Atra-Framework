#include "AttributeDescriptionsContainer.h"
#include "Attribute.h"

using AttributeUptr = std::unique_ptr<Attribute>;
using AttributeTypeVariant = std::variant<int, double, char>;

class AttributeFactory
{
private:
    std::map<AttributeType, AttributeUptr> prototypes_;
    static AttributeFactory *instance_;
    AttributeFactory() = default;

public:
    inline AttributeUptr createAttribute(AttributeType type)
    {
        if (prototypes_.find(type) == prototypes_.end())
        {
            return nullptr;
        }
        return prototypes_[type]->clone();
    }
    static AttributeFactory *getInstance()
    {
        static AttributeFactory *instance_;
        if (instance_ == nullptr)
        {
            instance_ = new AttributeFactory();
        }
        return instance_;
    }
    void registerPrototype(AttributeUptr prototype)
    {
        prototypes_[prototype->getType()] = std::move(prototype);
    }
};
