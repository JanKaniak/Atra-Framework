#pragma once
#include "NumericInput.h"
#include "CharacterInput.h"
#include "LogicInput.h"
#include "ControlComponentCluster.h"

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

using CharTextEditUptr = std::unique_ptr<ControlComponent>;
class CharTextEditFactory : public Factory
{
private:
    std::map<EditTypeCharText, CharTextEditUptr> prototypes_;

private:
    CharTextEditFactory();

    template <typename EditTypeCharT>
    void registerPrototype();

public:
    static CharTextEditFactory *getInstance();
    const AttributeType type_ = AttributeType::CHART;
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeCharText edit = EditTypeCharConverter::StringToEnum(editType);
        if (edit == EditTypeCharText::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }
    std::unique_ptr<ControlComponent> createDefaultEdit()  {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeCharText::TEXT]->clone();
    }
};

//---------------------------------------------------

using CharNumberEditUptr = std::unique_ptr<ControlComponent>;
class CharNumberEditFactory : public Factory
{
private:
    std::map<EditTypeNumber, CharNumberEditUptr> prototypes_;

private:
    CharNumberEditFactory();

    template <typename EditTypeCharT>
    void registerPrototype();

public:
    static CharNumberEditFactory *getInstance();
    const AttributeType type_ = AttributeType::CHARN;
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeNumber edit = EditTypeNumberConverter::StringToEnum(editType);
        if (edit == EditTypeNumber::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }
    std::unique_ptr<ControlComponent> createDefaultEdit()  {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeNumber::SLIDER]->clone();
    }
};

//---------------------------------------------------

using LogicEditUptr = std::unique_ptr<ControlComponent>;
class LogicEditFactory : public Factory
{
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
    std::map<EditTypeCluster, ClusterEditUptr> prototypes_;

private:
    ClusterEditFactory();
    template <typename EditTypeLogicT>
    void registerPrototype();

public:
    static ClusterEditFactory *getInstance();
    const AttributeType type_ = AttributeType::CLUSTER;
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeCluster edit = EditTypeClusterConverter::StringToEnum(editType);
        if (edit == EditTypeCluster::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }
    std::unique_ptr<ControlComponent> createDefaultEdit()  {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeCluster::TREE]->clone();
    }
};

//---------------------------------------------------

using LongEditUptr = std::unique_ptr<ControlComponent>;
class LongEditFactory : public Factory
{
private:
    std::map<EditTypeNumber, LongEditUptr> prototypes_;

private:
    LongEditFactory();

    template <typename EditTypeLongT>
    void registerPrototype();

public:
    static LongEditFactory *getInstance();
    const AttributeType type_ = AttributeType::LONG;
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

using UintEditUptr = std::unique_ptr<ControlComponent>;
class UintEditFactory : public Factory
{
private:
    std::map<EditTypeNumber, UintEditUptr> prototypes_;

private:
    UintEditFactory();

    template <typename EditTypeUintT>
    void registerPrototype();

public:
    static UintEditFactory *getInstance();
    const AttributeType type_ = AttributeType::UINT;
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
using StringEditUptr = std::unique_ptr<ControlComponent>;
class StringEditFactory : public Factory
{
private:
    std::map<EditTypeString, StringEditUptr> prototypes_;

private:
    StringEditFactory();

    template <typename EditTypeStringT>
    void registerPrototype();

public:
    static StringEditFactory *getInstance();
    const AttributeType type_ = AttributeType::STRING;
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeString edit = EditTypeStringConverter::StringToEnum(editType);
        if (edit == EditTypeString::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }

    std::unique_ptr<ControlComponent> createDefaultEdit() {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeString::TEXT]->clone();
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

struct AutoRegisterIntFactory {
    inline static bool autoRegister = [] () {
        
        Config::getInstance()->registerFactory(IntEditFactory::getInstance());
        return true;
    } ();
};

struct AutoRegisterDoubleFactory {
    inline static bool autoRegister = [] () {
        
        Config::getInstance()->registerFactory(DoubleEditFactory::getInstance());
        return true;
    } ();
};

struct AutoRegisterFloatFactory {
    inline static bool autoRegister = [] () {
        
        Config::getInstance()->registerFactory(FloatEditFactory::getInstance());
        return true;
    } ();
};

struct AutoRegisterCharTextFactory {
    inline static bool autoRegister = [] () {
        
        Config::getInstance()->registerFactory(CharTextEditFactory::getInstance());
        return true;
    } ();
};

struct AutoRegisterCharNumberFactory {
    inline static bool autoRegister = [] () {
        
        Config::getInstance()->registerFactory(CharNumberEditFactory::getInstance());
        return true;
    } ();
};

struct AutoRegisterLogicFactory {
    inline static bool autoRegister = [] () {
        
        Config::getInstance()->registerFactory(LogicEditFactory::getInstance());
        return true;
    } ();
};

struct AutoRegisterClusterFactory {
    inline static bool autoRegister = [] () {
        
        Config::getInstance()->registerFactory(ClusterEditFactory::getInstance());
        return true;
    } ();
};

struct AutoRegisterStringFactory {
    inline static bool autoRegister = [] () {
        
        Config::getInstance()->registerFactory(StringEditFactory::getInstance());
        return true;
    } ();
};

struct AutoRegisterLongFactory {
    inline static bool autoRegister = [] () {
        
        Config::getInstance()->registerFactory(LongEditFactory::getInstance());
        return true;
    } ();
};

struct AutoRegisterUintFactory {
    inline static bool autoRegister = [] () {
        
        Config::getInstance()->registerFactory(UintEditFactory::getInstance());
        return true;
    } ();
};

