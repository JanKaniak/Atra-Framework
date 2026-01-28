#include "AttributeDescription.h"
#include "NumericInput.h"

#include <map>

class Factory
{
public:
    virtual std::unique_ptr<ControlComponent> createEdit(std::string type) = 0;
};

using IntEditUptr = std::unique_ptr<ControlComponent>;

class IntEditFactory : public Factory
{
private:
    static IntEditFactory *instance;

private:
    std::map<EditTypeInt, IntEditUptr> prototypes_;
    std::map<std::string, EditTypeInt> converter{{"SLIDER", EditTypeInt::SLIDER}, {"VSLIDER", EditTypeInt::VSLIDER}, {"DRAG", EditTypeInt::DRAG}};

private:
    IntEditFactory();

    template <typename EditTypeIntT>
    void registerPrototype();

public:
    static IntEditFactory *getInstance();

    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeInt edit = EditTypeInt::SLIDER;
        if (converter.contains(editType))
        {
            edit = converter[editType];
        }
        return prototypes_[edit]->clone();
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
    std::map<std::string, EditTypeDouble> converter{{"SLIDER", EditTypeDouble::SLIDER}, {"VSLIDER", EditTypeDouble::VSLIDER}, {"DRAG", EditTypeDouble::DRAG}};

private:
    DoubleEditFactory();
    template <typename EditTypeDoubleT>
    void registerPrototype();

public:
    static DoubleEditFactory *getInstance();
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeDouble edit = EditTypeDouble::SLIDER;
        if (converter.contains(editType))
        {
            edit = converter[editType];
        }
        return prototypes_[edit]->clone();
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
    std::map<std::string, EditTypeFloat> converter{{"SLIDER", EditTypeFloat::SLIDER}, {"VSLIDER", EditTypeFloat::VSLIDER}, {"DRAG", EditTypeFloat::DRAG}};

private:
    FloatEditFactory();
    template <typename EditTypeFloatT>
    void registerPrototype();

public:
    static FloatEditFactory *getInstance();
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeFloat edit = EditTypeFloat::SLIDER;
        if (converter.contains(editType))
        {
            edit = converter[editType];
        }
        return prototypes_[edit]->clone();
    }
};

//---------------------------------------------------

using CharEditUptr = std::unique_ptr<ControlComponentChar>;
class CharEditFactory : public Factory
{
private:
    CharEditUptr prototype;

public:
    std::unique_ptr<ControlComponent> createEdit(std::string type)
    {
        return prototype->clone();
    }

    template <typename EditTypeCharT>
    void registerPrototype()
    {
        prototype = std::make_unique<EditTypeCharT>();
    }
};

//---------------------------------------------------

class Config
{
private:
    std::map<AttributeType, Factory *> factoryChoice_{{AttributeType::INT, IntEditFactory::getInstance()}, {AttributeType::DOUBLE, DoubleEditFactory::getInstance()},{AttributeType::FLOAT,FloatEditFactory::getInstance()}};

public:
    Factory *getFactory(AttributeType type)
    {
        if (factoryChoice_.contains(type))
        {
            return factoryChoice_[type];
        }
        else
        {
            return nullptr;
        }
    }
};