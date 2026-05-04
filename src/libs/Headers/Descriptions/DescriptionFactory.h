#pragma once
#include <map>
#include <memory>
#include "AttributeDescription.h"



/// Simple container for an attribute type and its category string.
class AttributeTypeC {
    private:
        AttributeType type_;
        std::string category_;
    public:
        AttributeTypeC();

        /// Construct a typed description entry with category metadata.
        AttributeTypeC(AttributeType type, std::string category) {
            type_ = type;
            category_ = category;
        }
        void setType(AttributeType type) { type_ = type;}
        void setCategory(std::string category) { category_ = category;}
        const AttributeType getType() {return type_;}
        const std::string &getCategory() { return category_;}
};





using DescUptr = std::unique_ptr<AttributeDescription>;

/// Singleton factory for attribute description prototypes.
///
/// Stores one prototype instance per AttributeType and clones them on request.
class DescFactory
{
private:
    std::map<AttributeType, DescUptr> prototypes_;
    std::vector<AttributeTypeC> types_;
    static DescFactory* instance_;
    DescFactory() = default;
public:
    /// Return the global DescFactory singleton instance.
    static DescFactory*  getInstance()
    {
        static DescFactory* instance_;
        if (instance_ == nullptr) {
            instance_ = new DescFactory();
        }
        return instance_;
    }
    
    /// Create a cloned descriptor instance for the requested type.
    DescUptr createDesc(AttributeType type) { 
        if (prototypes_.find(type) == prototypes_.end()) {
            return nullptr;
        }
        return prototypes_[type]->clone();
    }

    /// Register a prototype for later cloning.
    void registerPrototype(DescUptr prototype)
    {
        types_.emplace_back(prototype->getType(),prototype->getCategory());
        prototypes_[prototype->getType()] = std::move(prototype);
    }

    /// Return registered description types and categories.
    const std::vector<AttributeTypeC> getRegisteredDescriptionsTypes() { return types_;}
};



