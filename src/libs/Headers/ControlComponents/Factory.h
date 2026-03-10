#pragma once
#include "NumericInput.h"
#include "CharacterInput.h"
#include "LogicInput.h"

#include <map>

class Factory
{
protected:
    std::vector<std::string> nameOfControlTypesVector_;
    AttributeType type_;
public:
    Factory(AttributeType type) : type_(type) {}
    virtual std::unique_ptr<ControlComponent> createEdit(std::string type) = 0;
    virtual std::unique_ptr<ControlComponent> createDefaultEdit() = 0;
    bool findInVector(const std::vector<std::string> vector, std::string text) {
        for (std::string object : vector) {
            if (object.compare(text) == 0) {
                return true;
            }
        }
        return false;
    }
    const std::vector<std::string> getNameOfControlTypesVector() { return nameOfControlTypesVector_;}
    AttributeType getType() { return type_;}
};

using IntEditUptr = std::unique_ptr<ControlComponent>;

class IntEditFactory : public Factory
{
private:
    static IntEditFactory *instance_;


private:
    std::map<EditTypeNumber, IntEditUptr> prototypes_;

private:
    IntEditFactory();

    template <typename EditTypeIntT>
    void registerPrototype();

public:
    static IntEditFactory *getInstance();

    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeNumber edit = EditTypeNumberConverter::StringToEnum(editType);
        if (edit == EditTypeNumber::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }

    std::unique_ptr<ControlComponent> createDefaultEdit() {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeNumber::SLIDER]->clone();
    }
};

//--------------------------------------------------

using DoubleEditUptr = std::unique_ptr<ControlComponent>;
class DoubleEditFactory : public Factory
{
private:
    static DoubleEditFactory *instance;

private:
    std::map<EditTypeNumber, DoubleEditUptr> prototypes_;

private:
    DoubleEditFactory();

    template <typename EditTypeDoubleT>
    void registerPrototype();

public:
    static DoubleEditFactory *getInstance();
     const AttributeType type_ = AttributeType::DOUBLE;
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeNumber edit = EditTypeNumberConverter::StringToEnum(editType);
        if (edit == EditTypeNumber::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }

    std::unique_ptr<ControlComponent> createDefaultEdit() {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeNumber::SLIDER]->clone();
    }
};

//---------------------------------------------------

using FloatEditUptr = std::unique_ptr<ControlComponent>;
class FloatEditFactory : public Factory
{
private:
    static FloatEditFactory *instance;

private:
    std::map<EditTypeNumber, FloatEditUptr> prototypes_;

private:
    FloatEditFactory();

    template <typename EditTypeFloatT>
    void registerPrototype();

public:
    static FloatEditFactory *getInstance();
    const AttributeType type_ = AttributeType::FLOAT;
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeNumber edit = EditTypeNumberConverter::StringToEnum(editType);
        if (edit == EditTypeNumber::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }

    std::unique_ptr<ControlComponent> createDefaultEdit() {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeNumber::SLIDER]->clone();
    }
};

//---------------------------------------------------

using CharEditUptr = std::unique_ptr<ControlComponent>;
class CharEditFactory : public Factory
{
private:
    static CharEditFactory *instance;

private:
    std::map<EditTypeChar, CharEditUptr> prototypes_;

private:
    CharEditFactory();

    template <typename EditTypeCharT>
    void registerPrototype();

public:
    static CharEditFactory *getInstance();
    const AttributeType type_ = AttributeType::FLOAT;
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeChar edit = EditTypeCharConverter::StringToEnum(editType);
        if (edit == EditTypeChar::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }
    std::unique_ptr<ControlComponent> createDefaultEdit()  {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeChar::TEXT]->clone();
    }
};

//---------------------------------------------------

using LogicEditUptr = std::unique_ptr<ControlComponent>;
class LogicEditFactory : public Factory
{
private:
    static LogicEditFactory *instance;

private:
    std::map<EditTypeLogic, LogicEditUptr> prototypes_;

private:
    LogicEditFactory();

    template <typename EditTypeLogicT>
    void registerPrototype();

public:
    static LogicEditFactory *getInstance();
    const AttributeType type_ = AttributeType::BOOL;
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeLogic edit = EditTypeLogicConverter::StringToEnum(editType);
        if (edit == EditTypeLogic::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }
    std::unique_ptr<ControlComponent> createDefaultEdit()  {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeLogic::CHECKBOX]->clone();
    }
};


//---------------------------------------------------

using ClusterEditUptr = std::unique_ptr<ControlComponent>;
class ClusterEditFactory : public Factory
{
private:
    static ClusterEditFactory *instance;

private:
    std::map<EditTypeCluster, ClusterEditUptr> prototypes_;

private:
    ClusterEditFactory();

    void registerPrototype();

public:
    static ClusterEditFactory *getInstance();
    const AttributeType type_ = AttributeType::CLUSTER;
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        return createDefaultEdit();
    }
    std::unique_ptr<ControlComponent> createDefaultEdit()  {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeCluster::DEFAULT]->clone();
    }
};

//---------------------------------------------------


class Config
{
private:
    std::map<AttributeType, Factory*> factoryChoice_;
    static Config *instance_;
    Config() = default;
public:
    static Config* getInstance();

    Factory *getFactory(AttributeType type);
    void registerFactory(Factory *factory);
};



// ------------------------------------------------------------------


#define Factory_register \
    FactoryR(Int, IntEditFactory) \
    FactoryR(Double, DoubleEditFactory) \
    FactoryR(Float, FloatEditFactory) \
    FactoryR(Char, CharEditFactory) \
    FactoryR(Logic, LogicEditFactory) 

#define FactoryR(type,factory) \
struct AutoRegister##type##Factory { \
    inline static bool autoRegister = [] () { \
        Config::getInstance()->registerFactory(factory::getInstance()); \
        return true; \
    } (); \
};
Factory_register
#undef FactoryR

struct AutoRegisterClusterFactory {
    inline static bool autoRegister = [] () {
        
        Config::getInstance()->registerFactory(ClusterEditFactory::getInstance());
        return true;
    } ();
};
/*
struct AutoRegisterFloatFactory {
    inline static bool autoRegister = [] () {
        
        Config::getInstance()->registerFactory(FloatEditFactory::getInstance());
        return true;
    } ();
};*/