#include "Factory.h"
// FACTORIES ----------------------------------------------------------------------------------

// INT

IntEditFactory *IntEditFactory::instance_ = nullptr;

IntEditFactory::IntEditFactory() : Factory(AttributeType::INT)
{
    this->registerPrototype<IntSlider>();
    this->registerPrototype<IntVSSlider>();
    this->registerPrototype<IntDrag>();
}

IntEditFactory *IntEditFactory::getInstance()
{
    if (instance_ == nullptr)
    {
        instance_ = new IntEditFactory();
    }

    return instance_;
}

template <typename EditTypeIntT>
inline void IntEditFactory::registerPrototype()
{
    if (!findInVector(nameOfControlTypesVector_, enumToString[EditTypeIntT::type_]))
    {
        nameOfControlTypesVector_.emplace_back(enumToString[EditTypeIntT::type_]);
    }
    prototypes_[EditTypeIntT::type_] = std::move(std::make_unique<EditTypeIntT>());
}

//

// DOUBLE

DoubleEditFactory *DoubleEditFactory::instance = nullptr;

DoubleEditFactory::DoubleEditFactory() : Factory(AttributeType::DOUBLE)
{
    this->registerPrototype<DoubleSlider>();
    this->registerPrototype<DoubleVSSlider>();
    this->registerPrototype<DoubleDrag>();
}

DoubleEditFactory *DoubleEditFactory::getInstance()
{
    if (instance == nullptr)
    {
        instance = new DoubleEditFactory();
    }

    return instance;
}

template <typename EditTypeDoubleT>
inline void DoubleEditFactory::registerPrototype()
{
    if (!findInVector(nameOfControlTypesVector_, enumToString[EditTypeDoubleT::type_]))
    {
        nameOfControlTypesVector_.emplace_back(enumToString[EditTypeDoubleT::type_]);
    }
    prototypes_[EditTypeDoubleT::type_] = std::move(std::make_unique<EditTypeDoubleT>());
}

//

// FLOAT

FloatEditFactory *FloatEditFactory::instance = nullptr;

FloatEditFactory::FloatEditFactory() : Factory(AttributeType::FLOAT)
{
    this->registerPrototype<FloatSlider>();
    this->registerPrototype<FloatVSSlider>();
    this->registerPrototype<FloatDrag>();
}

FloatEditFactory *FloatEditFactory::getInstance()
{
    if (instance == nullptr)
    {
        instance = new FloatEditFactory();
    }

    return instance;
}

template <typename EditTypeFloatT>
inline void FloatEditFactory::registerPrototype()
{
    if (!findInVector(nameOfControlTypesVector_, enumToString[EditTypeFloatT::type_]))
    {
        nameOfControlTypesVector_.emplace_back(enumToString[EditTypeFloatT::type_]);
    }
    prototypes_[EditTypeFloatT::type_] = std::move(std::make_unique<EditTypeFloatT>());
}

// ------------------------------------------------------------------------------------------------------


// CHAR

CharEditFactory *CharEditFactory::instance = nullptr;

CharEditFactory::CharEditFactory() : Factory(AttributeType::CHAR)
{
    this->registerPrototype<TextField>();
}

CharEditFactory *CharEditFactory::getInstance()
{
    if (instance == nullptr)
    {
        instance = new CharEditFactory();
    }

    return instance;
}

template <typename EditTypeCharT>
inline void CharEditFactory::registerPrototype()
{
    if (!findInVector(nameOfControlTypesVector_, enumToString[EditTypeCharT::type_]))
    {
        nameOfControlTypesVector_.emplace_back(enumToString[EditTypeCharT::type_]);
    }
    prototypes_[EditTypeCharT::type_] = std::move(std::make_unique<EditTypeCharT>());
}

// ------------------------------------------------------------------------------------------------------

// Config
Config *Config::instance_ = nullptr;

Config *Config::getInstance()
{
    if (instance_ == nullptr)
    {
        return instance_ = new Config();
    }
    return instance_;
}

Factory *Config::getFactory(AttributeType type)
{
    if (factoryChoice_.find(type) == factoryChoice_.end())
    {
        return nullptr;
    }
    return factoryChoice_[type];
}

void Config::registerFactory(Factory *factory)
{
    factoryChoice_[factory->getType()] = factory;
}