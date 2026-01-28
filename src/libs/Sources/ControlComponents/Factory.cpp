#include "Factory.h"
// FACTORIES ----------------------------------------------------------------------------------

// INT

IntEditFactory *IntEditFactory::instance = nullptr;

IntEditFactory::IntEditFactory()
{
    this->registerPrototype<IntSlider>();
    this->registerPrototype<IntVSSlider>();
    this->registerPrototype<IntDrag>();
}

IntEditFactory *IntEditFactory::getInstance()
{
    if (instance == nullptr)
    {
        instance = new IntEditFactory();
    }

    return instance;
}

template <typename EditTypeIntT>
inline void IntEditFactory::registerPrototype()
{
    prototypes_[EditTypeIntT::type_] = std::move(std::make_unique<EditTypeIntT>());
}

//

// DOUBLE

DoubleEditFactory *DoubleEditFactory::instance = nullptr;

DoubleEditFactory::DoubleEditFactory()
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
    prototypes_[EditTypeDoubleT::type_] = std::move(std::make_unique<EditTypeDoubleT>());
}

//

// FLOAT

FloatEditFactory *FloatEditFactory::instance = nullptr;

FloatEditFactory::FloatEditFactory()
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
    prototypes_[EditTypeFloatT::type_] = std::move(std::make_unique<EditTypeFloatT>());
}

// ------------------------------------------------------------------------------------------------------