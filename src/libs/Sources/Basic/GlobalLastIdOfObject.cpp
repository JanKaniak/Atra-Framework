#include "GlobalLastIdOfObject.h"

GlobalLastIdOfObject *GlobalLastIdOfObject::instance_ = nullptr;

GlobalLastIdOfObject *GlobalLastIdOfObject::getInstance()
{

    if (instance_ == nullptr)
    {
        instance_ = new GlobalLastIdOfObject();
    }
    return instance_;
}

uint64_t GlobalLastIdOfObject::getNewId() {
        lastId_ = lastId_+1;
        return lastId_;
    }