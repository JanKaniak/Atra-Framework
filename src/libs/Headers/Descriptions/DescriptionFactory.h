#pragma once
#include <map>
#include <memory>
#include "AttributeDescription.h"



class AttributeTypeC {
    private:
        AttributeType type_;
        std::string category_;
    public:
        AttributeTypeC();
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

class DescFactory
{
private:
    std::map<AttributeType, DescUptr> prototypes_;
    std::vector<AttributeTypeC> types_;
    static DescFactory* instance_;
    DescFactory() = default;
public:
    static DescFactory*  getInstance()
    {
        static DescFactory* instance_;
        if (instance_ == nullptr) {
            instance_ = new DescFactory();
        }
        return instance_;
    }
    
    DescUptr createDesc(AttributeType type) { 
        if (prototypes_.find(type) == prototypes_.end()) {
            return nullptr;
        }
        return prototypes_[type]->clone();
    }

    void registerPrototype(DescUptr prototype)
    {
        types_.emplace_back(prototype->getType(),prototype->getCategory());
        prototypes_[prototype->getType()] = std::move(prototype);
    }

    const std::vector<AttributeTypeC> getRegisteredDescriptionsTypes() { return types_;}
};



