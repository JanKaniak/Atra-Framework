#pragma once
#include "NumericInput.h"
#include "CharacterInput.h"
#include "LogicInput.h"
#include "ControlComponentCluster.h"

#include <map>

/// Abstract base factory for control component instances keyed by edit type.
class Factory
{
protected:
    std::vector<std::string> nameOfControlTypesVector_;
    AttributeType type_;
public:
    Factory(AttributeType type) : type_(type) {}
    /// Create a control component instance by edit type string.
    virtual std::unique_ptr<ControlComponent> createEdit(std::string type) = 0;
    /// Create a default control component instance for this factory.
    virtual std::unique_ptr<ControlComponent> createDefaultEdit() = 0;
    /// Check whether a control type name exists in the given vector.
    bool findInVector(const std::vector<std::string> vector, std::string text) {
        for (std::string object : vector) {
            if (object.compare(text) == 0) {
                return true;
            }
        }
        return false;
    }
    /// Return all supported control type names registered for this factory.
    const std::vector<std::string> getNameOfControlTypesVector() { return nameOfControlTypesVector_;}
    /// Return the attribute type that this factory handles.
    AttributeType getType() { return type_;}
};

using IntEditUptr = std::unique_ptr<ControlComponent>;

/// Singleton factory managing integer-based edit control prototypes.
class IntEditFactory : public Factory
{
private:
    std::map<EditTypeNumber, IntEditUptr> prototypes_;

private:
    IntEditFactory();

    template <typename EditTypeIntT>
    void registerPrototype();

public:
    /// Return the singleton instance of the integer edit factory.
    static IntEditFactory *getInstance();

    /// Create an integer edit control instance by edit type name.
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeNumber edit = EditTypeNumberConverter::StringToEnum(editType);
        if (edit == EditTypeNumber::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }

    /// Create the default integer edit control when none is specified.
    std::unique_ptr<ControlComponent> createDefaultEdit() {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeNumber::SLIDER]->clone();
    }
};

//--------------------------------------------------

using DoubleEditUptr = std::unique_ptr<ControlComponent>;
/// Singleton factory managing double-based edit control prototypes.
class DoubleEditFactory : public Factory
{
private:
    std::map<EditTypeNumber, DoubleEditUptr> prototypes_;

private:
    DoubleEditFactory();

    template <typename EditTypeDoubleT>
    void registerPrototype();

public:
    /// Return the singleton instance of the double edit factory.
    static DoubleEditFactory *getInstance();
     const AttributeType type_ = AttributeType::DOUBLE;
    /// Create a double edit control instance by edit type name.
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeNumber edit = EditTypeNumberConverter::StringToEnum(editType);
        if (edit == EditTypeNumber::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }

    /// Create the default double edit control when none is specified.
    std::unique_ptr<ControlComponent> createDefaultEdit() {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeNumber::SLIDER]->clone();
    }
};

//---------------------------------------------------

using FloatEditUptr = std::unique_ptr<ControlComponent>;
/// Singleton factory managing float-based edit control prototypes.
class FloatEditFactory : public Factory
{
private:
    std::map<EditTypeNumber, FloatEditUptr> prototypes_;

private:
    FloatEditFactory();

    template <typename EditTypeFloatT>
    void registerPrototype();

public:
    /// Return the singleton instance of the float edit factory.
    static FloatEditFactory *getInstance();
    const AttributeType type_ = AttributeType::FLOAT;
    /// Create a float edit control instance by edit type name.
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeNumber edit = EditTypeNumberConverter::StringToEnum(editType);
        if (edit == EditTypeNumber::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }

    /// Create the default float edit control when none is specified.
    std::unique_ptr<ControlComponent> createDefaultEdit() {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeNumber::SLIDER]->clone();
    }
};

//---------------------------------------------------

using CharTextEditUptr = std::unique_ptr<ControlComponent>;
/// Singleton factory managing character text edit control prototypes.
class CharTextEditFactory : public Factory
{
private:
    std::map<EditTypeCharText, CharTextEditUptr> prototypes_;

private:
    CharTextEditFactory();

    template <typename EditTypeCharT>
    void registerPrototype();

public:
    /// Return the singleton instance of the char-text edit factory.
    static CharTextEditFactory *getInstance();
    const AttributeType type_ = AttributeType::CHART;
    /// Create a char-text edit control instance by edit type name.
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeCharText edit = EditTypeCharConverter::StringToEnum(editType);
        if (edit == EditTypeCharText::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }
    /// Create the default char-text control when none is specified.
    std::unique_ptr<ControlComponent> createDefaultEdit()  {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeCharText::TEXT]->clone();
    }
};

//---------------------------------------------------

using CharNumberEditUptr = std::unique_ptr<ControlComponent>;
/// Singleton factory managing character-number edit control prototypes.
class CharNumberEditFactory : public Factory
{
private:
    std::map<EditTypeNumber, CharNumberEditUptr> prototypes_;

private:
    CharNumberEditFactory();

    template <typename EditTypeCharT>
    void registerPrototype();

public:
    /// Return the singleton instance of the char-number edit factory.
    static CharNumberEditFactory *getInstance();
    const AttributeType type_ = AttributeType::CHARN;
    /// Create a char-number edit control instance by edit type name.
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeNumber edit = EditTypeNumberConverter::StringToEnum(editType);
        if (edit == EditTypeNumber::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }
    /// Create the default char-number control when none is specified.
    std::unique_ptr<ControlComponent> createDefaultEdit()  {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeNumber::SLIDER]->clone();
    }
};

//---------------------------------------------------

using LogicEditUptr = std::unique_ptr<ControlComponent>;
/// Singleton factory managing boolean logic edit control prototypes.
class LogicEditFactory : public Factory
{
private:
    std::map<EditTypeLogic, LogicEditUptr> prototypes_;

private:
    LogicEditFactory();

    template <typename EditTypeLogicT>
    void registerPrototype();

public:
    /// Return the singleton instance of the logic edit factory.
    static LogicEditFactory *getInstance();
    const AttributeType type_ = AttributeType::BOOL;
    /// Create a logic edit control instance by edit type name.
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeLogic edit = EditTypeLogicConverter::StringToEnum(editType);
        if (edit == EditTypeLogic::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }
    /// Create the default logic edit control when none is specified.
    std::unique_ptr<ControlComponent> createDefaultEdit()  {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeLogic::CHECKBOX]->clone();
    }
};


//---------------------------------------------------

using ClusterEditUptr = std::unique_ptr<ControlComponent>;
/// Singleton factory managing cluster/tree edit control prototypes.
class ClusterEditFactory : public Factory
{
private:
    std::map<EditTypeCluster, ClusterEditUptr> prototypes_;

private:
    ClusterEditFactory();
    template <typename EditTypeLogicT>
    void registerPrototype();

public:
    /// Return the singleton instance of the cluster edit factory.
    static ClusterEditFactory *getInstance();
    const AttributeType type_ = AttributeType::CLUSTER;
    /// Create a cluster edit control instance by edit type name.
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeCluster edit = EditTypeClusterConverter::StringToEnum(editType);
        if (edit == EditTypeCluster::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }
    /// Create the default cluster edit control when none is specified.
    std::unique_ptr<ControlComponent> createDefaultEdit()  {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeCluster::TREE]->clone();
    }
};

//---------------------------------------------------

using LongEditUptr = std::unique_ptr<ControlComponent>;
/// Singleton factory managing long integer edit control prototypes.
class LongEditFactory : public Factory
{
private:
    std::map<EditTypeNumber, LongEditUptr> prototypes_;

private:
    LongEditFactory();

    template <typename EditTypeLongT>
    void registerPrototype();

public:
    /// Return the singleton instance of the long edit factory.
    static LongEditFactory *getInstance();
    const AttributeType type_ = AttributeType::LONG;
    /// Create a long integer edit control instance by edit type name.
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeNumber edit = EditTypeNumberConverter::StringToEnum(editType);
        if (edit == EditTypeNumber::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }

    /// Create the default long integer edit control when none is specified.
    std::unique_ptr<ControlComponent> createDefaultEdit() {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeNumber::SLIDER]->clone();
    }
};

//---------------------------------------------------

using UintEditUptr = std::unique_ptr<ControlComponent>;
/// Singleton factory managing unsigned integer edit control prototypes.
class UintEditFactory : public Factory
{
private:
    std::map<EditTypeNumber, UintEditUptr> prototypes_;

private:
    UintEditFactory();

    template <typename EditTypeUintT>
    void registerPrototype();

public:
    /// Return the singleton instance of the unsigned integer edit factory.
    static UintEditFactory *getInstance();
    const AttributeType type_ = AttributeType::UINT;
    /// Create an unsigned integer edit control instance by edit type name.
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeNumber edit = EditTypeNumberConverter::StringToEnum(editType);
        if (edit == EditTypeNumber::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }

    /// Create the default unsigned integer edit control when none is specified.
    std::unique_ptr<ControlComponent> createDefaultEdit() {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeNumber::SLIDER]->clone();
    }
};

//---------------------------------------------------
using StringEditUptr = std::unique_ptr<ControlComponent>;
/// Singleton factory managing string edit control prototypes.
class StringEditFactory : public Factory
{
private:
    std::map<EditTypeString, StringEditUptr> prototypes_;

private:
    StringEditFactory();

    template <typename EditTypeStringT>
    void registerPrototype();

public:
    /// Return the singleton instance of the string edit factory.
    static StringEditFactory *getInstance();
    const AttributeType type_ = AttributeType::STRING;
    /// Create a string edit control instance by edit type name.
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeString edit = EditTypeStringConverter::StringToEnum(editType);
        if (edit == EditTypeString::NOTACONTROL)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }

    /// Create the default string edit control when none is specified.
    std::unique_ptr<ControlComponent> createDefaultEdit() {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeString::TEXT]->clone();
    }
};

//---------------------------------------------------




/// Registry holding a singleton instance of each control component factory.
class ControlComponentsFactoriesContainer
{
private:
    std::unordered_map<AttributeType, Factory*> factoryChoice_;
    ControlComponentsFactoriesContainer() = default;
public:
    /// Return the singleton factory registry.
    static ControlComponentsFactoriesContainer* getInstance();

    /// Look up a factory by its attribute type.
    Factory *getFactory(AttributeType type);
    /// Register a factory into the global container.
    void registerFactory(Factory *factory);
};



// ------------------------------------------------------------------

/// Auto-register each control factory into the global factory container at static initialization.
struct AutoRegisterIntFactory {
    inline static bool autoRegister = [] () {
        
        ControlComponentsFactoriesContainer::getInstance()->registerFactory(IntEditFactory::getInstance());
        return true;
    } ();
};

struct AutoRegisterDoubleFactory {
    inline static bool autoRegister = [] () {
        
        ControlComponentsFactoriesContainer::getInstance()->registerFactory(DoubleEditFactory::getInstance());
        return true;
    } ();
};

struct AutoRegisterFloatFactory {
    inline static bool autoRegister = [] () {
        
        ControlComponentsFactoriesContainer::getInstance()->registerFactory(FloatEditFactory::getInstance());
        return true;
    } ();
};

struct AutoRegisterCharTextFactory {
    inline static bool autoRegister = [] () {
        
        ControlComponentsFactoriesContainer::getInstance()->registerFactory(CharTextEditFactory::getInstance());
        return true;
    } ();
};

struct AutoRegisterCharNumberFactory {
    inline static bool autoRegister = [] () {
        
        ControlComponentsFactoriesContainer::getInstance()->registerFactory(CharNumberEditFactory::getInstance());
        return true;
    } ();
};

struct AutoRegisterLogicFactory {
    inline static bool autoRegister = [] () {
        
        ControlComponentsFactoriesContainer::getInstance()->registerFactory(LogicEditFactory::getInstance());
        return true;
    } ();
};

struct AutoRegisterClusterFactory {
    inline static bool autoRegister = [] () {
        
        ControlComponentsFactoriesContainer::getInstance()->registerFactory(ClusterEditFactory::getInstance());
        return true;
    } ();
};

struct AutoRegisterStringFactory {
    inline static bool autoRegister = [] () {
        
        ControlComponentsFactoriesContainer::getInstance()->registerFactory(StringEditFactory::getInstance());
        return true;
    } ();
};

struct AutoRegisterLongFactory {
    inline static bool autoRegister = [] () {
        
        ControlComponentsFactoriesContainer::getInstance()->registerFactory(LongEditFactory::getInstance());
        return true;
    } ();
};

struct AutoRegisterUintFactory {
    inline static bool autoRegister = [] () {
        
        ControlComponentsFactoriesContainer::getInstance()->registerFactory(UintEditFactory::getInstance());
        return true;
    } ();
};

