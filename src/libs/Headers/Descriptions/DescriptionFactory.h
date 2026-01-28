#pragma once
#include <map>
#include <memory>
#include "AttributeDescription.h"


using DescUptr = std::unique_ptr<AttributeDescription>;

class DescFactory
{
private:
    std::map<AttributeType, DescUptr> prototypes_;
    static DescFactory instance_;

public:
    DescFactory() = default;
    static DescFactory& getInstance()
    {
        static DescFactory instance_;
        return instance_;
    }
    
    inline DescUptr createDesc(AttributeType type) { 
        return prototypes_[type]->clone();
        return nullptr; 
    }

    void registerPrototype(DescUptr prototype)
    {
        prototypes_[prototype->getType()] = std::move(prototype);
    }
};



