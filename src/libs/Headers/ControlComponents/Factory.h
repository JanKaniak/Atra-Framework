#include "AttributeDescription.h"
#include "NumericInput.h"

#include <map>

class Factory
{
protected:
    std::vector<std::string> nameOfControlTypesVector_;
public:
    virtual std::unique_ptr<ControlComponent> createEdit(std::string type) = 0;
    bool findInVector(const std::vector<std::string> vector, std::string text) {
        for (std::string object : vector) {
            if (object.compare(text) == 0) {
                return true;
            }
        }
        return false;
    }
    const std::vector<std::string> getNameOfControlTypesVector() { return nameOfControlTypesVector_;}
};

using IntEditUptr = std::unique_ptr<ControlComponent>;

class IntEditFactory : public Factory
{
private:
    static IntEditFactory *instance;

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
        EditTypeInt edit = EditTypeInt::SLIDER;
        if (stringToEnum.contains(editType))
        {
            edit = stringToEnum[editType];
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
    std::map<std::string, EditTypeDouble> stringToEnum{{"SLIDER", EditTypeDouble::SLIDER}, {"VSLIDER", EditTypeDouble::VSLIDER}, {"DRAG", EditTypeDouble::DRAG}};
    std::map<EditTypeDouble, std::string> enumToString{{EditTypeDouble::SLIDER, "SLIDER"}, {EditTypeDouble::VSLIDER, "VSLIDER"}, {EditTypeDouble::DRAG, "DRAG"}};

private:
    DoubleEditFactory();
    template <typename EditTypeDoubleT>
    void registerPrototype();

public:
    static DoubleEditFactory *getInstance();
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeDouble edit = EditTypeDouble::SLIDER;
        if (stringToEnum.contains(editType))
        {
            edit = stringToEnum[editType];
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
    std::map<std::string, EditTypeFloat> stringToEnum{{"SLIDER", EditTypeFloat::SLIDER}, {"VSLIDER", EditTypeFloat::VSLIDER}, {"DRAG", EditTypeFloat::DRAG}};
    std::map<EditTypeFloat, std::string> enumToString{{EditTypeFloat::SLIDER, "SLIDER"}, {EditTypeFloat::VSLIDER, "VSLIDER"}, {EditTypeFloat::DRAG, "DRAG"}};

private:
    FloatEditFactory();
    template <typename EditTypeFloatT>
    void registerPrototype();

public:
    static FloatEditFactory *getInstance();
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeFloat edit = EditTypeFloat::SLIDER;
        if (stringToEnum.contains(editType))
        {
            edit = stringToEnum[editType];
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