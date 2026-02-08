#pragma once
#include "AttributeDescription.h"
#include "NumericInput.h"
#include "CharacterInput.h"

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
    
    std::map<EditTypeInt, IntEditUptr> prototypes_;
    std::map<std::string, EditTypeInt> stringToEnum{{"SLIDER", EditTypeInt::SLIDER}, {"VSLIDER", EditTypeInt::VSLIDER}, {"DRAG", EditTypeInt::DRAG}};
    std::map<EditTypeInt, std::string> enumToString{{EditTypeInt::SLIDER, "SLIDER"}, {EditTypeInt::VSLIDER, "VSLIDER"}, {EditTypeInt::DRAG, "DRAG"}};

private:
    IntEditFactory();

    template <typename EditTypeIntT>
    void registerPrototype();

public:
    static IntEditFactory *getInstance();

    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeInt edit = EditTypeIntConverter::getInstance()->stringToEnumConverter(editType);
        if (edit == EditTypeInt::DEFAULT)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }

    std::unique_ptr<ControlComponent> createDefaultEdit() {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeInt::SLIDER]->clone();
    }
};

//--------------------------------------------------

using DoubleEditUptr = std::unique_ptr<ControlComponent>;
class DoubleEditFactory : public Factory
{
private:
    static DoubleEditFactory *instance;

private:
    std::map<EditTypeDouble, DoubleEditUptr> prototypes_;
    std::map<std::string, EditTypeDouble> stringToEnum{{"SLIDER", EditTypeDouble::SLIDER}, {"VSLIDER", EditTypeDouble::VSLIDER}, {"DRAG", EditTypeDouble::DRAG}};
    std::map<EditTypeDouble, std::string> enumToString{{EditTypeDouble::SLIDER, "SLIDER"}, {EditTypeDouble::VSLIDER, "VSLIDER"}, {EditTypeDouble::DRAG, "DRAG"}};

private:
    DoubleEditFactory();

    template <typename EditTypeDoubleT>
    void registerPrototype();

public:
    static DoubleEditFactory *getInstance();
     const AttributeType type_ = AttributeType::DOUBLE;
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeDouble edit = EditTypeDoubleConverter::getInstance()->stringToEnumConverter(editType);
        if (edit == EditTypeDouble::DEFAULT)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }

    std::unique_ptr<ControlComponent> createDefaultEdit() {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeDouble::SLIDER]->clone();
    }
};

//---------------------------------------------------

using FloatEditUptr = std::unique_ptr<ControlComponent>;
class FloatEditFactory : public Factory
{
private:
    static FloatEditFactory *instance;

private:
    std::map<EditTypeFloat, FloatEditUptr> prototypes_;
    std::map<std::string, EditTypeFloat> stringToEnum{{"SLIDER", EditTypeFloat::SLIDER}, {"VSLIDER", EditTypeFloat::VSLIDER}, {"DRAG", EditTypeFloat::DRAG}};
    std::map<EditTypeFloat, std::string> enumToString{{EditTypeFloat::SLIDER, "SLIDER"}, {EditTypeFloat::VSLIDER, "VSLIDER"}, {EditTypeFloat::DRAG, "DRAG"}};

private:
    FloatEditFactory();

    template <typename EditTypeFloatT>
    void registerPrototype();

public:
    static FloatEditFactory *getInstance();
    const AttributeType type_ = AttributeType::FLOAT;
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeFloat edit = EditTypeFloatConverter::getInstance()->stringToEnumConverter(editType);
        if (edit == EditTypeFloat::DEFAULT)
        {
            return nullptr;
        }
        return prototypes_[edit]->clone();
    }

    std::unique_ptr<ControlComponent> createDefaultEdit() {
        if (prototypes_.size() == 0) {
            return nullptr;
        }
        return prototypes_[EditTypeFloat::SLIDER]->clone();
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
    std::map<std::string, EditTypeChar> stringToEnum{{"TEXT", EditTypeChar::TEXT}};
    std::map<EditTypeChar, std::string> enumToString{{EditTypeChar::TEXT, "TEXT"}};

private:
    CharEditFactory();

    template <typename EditTypeCharT>
    void registerPrototype();

public:
    static CharEditFactory *getInstance();
    const AttributeType type_ = AttributeType::FLOAT;
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeChar edit = EditTypeCharConverter::getInstance()->stringToEnumConverter(editType);
        if (edit == EditTypeChar::DEFAULT)
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
    FactoryR(Char, CharEditFactory)

#define FactoryR(type,factory) \
struct AutoRegister##type##Factory { \
    inline static bool autoRegister = [] () { \
        Config::getInstance()->registerFactory(factory::getInstance()); \
        return true; \
    } (); \
};
Factory_register
#undef FactoryR

/*struct AutoRegisterDoubleFactory {
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
};*/