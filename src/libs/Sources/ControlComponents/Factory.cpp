#include "Factory.h"
// FACTORIES ----------------------------------------------------------------------------------

// INT

IntEditFactory::IntEditFactory() : Factory(AttributeType::INT)
{
    this->registerPrototype<IntSlider>();
    this->registerPrototype<IntVSlider>();
    this->registerPrototype<IntDrag>();
}

IntEditFactory *IntEditFactory::getInstance()
{
    static IntEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new IntEditFactory();
    }

    return instance;
}

template <typename EditTypeIntT>
inline void IntEditFactory::registerPrototype()
{
    if (!findInVector(nameOfControlTypesVector_, EditTypeNumberConverter::EnumToString(EditTypeIntT::type_).data()))
    {
        nameOfControlTypesVector_.emplace_back(EditTypeNumberConverter::EnumToString(EditTypeIntT::type_));
    }
    prototypes_[EditTypeIntT::type_] = std::move(std::make_unique<EditTypeIntT>());
}

//

// DOUBLE

DoubleEditFactory::DoubleEditFactory() : Factory(AttributeType::DOUBLE)
{
    this->registerPrototype<DoubleSlider>();
    this->registerPrototype<DoubleVSlider>();
    this->registerPrototype<DoubleDrag>();
}

DoubleEditFactory *DoubleEditFactory::getInstance()
{
    static DoubleEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new DoubleEditFactory();
    }

    return instance;
}

template <typename EditTypeDoubleT>
inline void DoubleEditFactory::registerPrototype()
{
    if (!findInVector(nameOfControlTypesVector_, EditTypeNumberConverter::EnumToString(EditTypeDoubleT::type_).data()))
    {
        nameOfControlTypesVector_.emplace_back(EditTypeNumberConverter::EnumToString(EditTypeDoubleT::type_));
    }
    prototypes_[EditTypeDoubleT::type_] = std::move(std::make_unique<EditTypeDoubleT>());
}

//

// FLOAT


FloatEditFactory::FloatEditFactory() : Factory(AttributeType::FLOAT)
{
    this->registerPrototype<FloatSlider>();
    this->registerPrototype<FloatVSlider>();
    this->registerPrototype<FloatDrag>();
}

FloatEditFactory *FloatEditFactory::getInstance()
{
    static FloatEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new FloatEditFactory();
    }

    return instance;
}

template <typename EditTypeFloatT>
inline void FloatEditFactory::registerPrototype()
{
    if (!findInVector(nameOfControlTypesVector_, EditTypeNumberConverter::EnumToString(EditTypeFloatT::type_).data()))
    {
        nameOfControlTypesVector_.emplace_back(EditTypeNumberConverter::EnumToString(EditTypeFloatT::type_));
    }
    prototypes_[EditTypeFloatT::type_] = std::move(std::make_unique<EditTypeFloatT>());
}

// ------------------------------------------------------------------------------------------------------


// CHAR Text


CharTextEditFactory::CharTextEditFactory() : Factory(AttributeType::CHART)
{
    this->registerPrototype<CharTextField>();
}

CharTextEditFactory *CharTextEditFactory::getInstance()
{
    static CharTextEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new CharTextEditFactory();
    }

    return instance;
}

template <typename EditTypeCharT>
inline void CharTextEditFactory::registerPrototype()
{
    if (!findInVector(nameOfControlTypesVector_, EditTypeCharConverter::EnumToString(EditTypeCharT::type_).data()))
    {
        nameOfControlTypesVector_.emplace_back(EditTypeCharConverter::EnumToString(EditTypeCharT::type_));
    }
    prototypes_[EditTypeCharT::type_] = std::move(std::make_unique<EditTypeCharT>());
}

// ------------------------------------------------------------------------------------------------------

// CHAR Text

CharNumberEditFactory::CharNumberEditFactory() : Factory(AttributeType::CHARN)
{
    this->registerPrototype<CharSlider>();
    this->registerPrototype<CharVSlider>();
    this->registerPrototype<CharDrag>();
}

CharNumberEditFactory *CharNumberEditFactory::getInstance()
{
    static CharNumberEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new CharNumberEditFactory();
    }

    return instance;
}

template <typename EditTypeCharT>
inline void CharNumberEditFactory::registerPrototype()
{
    if (!findInVector(nameOfControlTypesVector_, EditTypeNumberConverter::EnumToString(EditTypeCharT::type_).data()))
    {
        nameOfControlTypesVector_.emplace_back(EditTypeNumberConverter::EnumToString(EditTypeCharT::type_));
    }
    prototypes_[EditTypeCharT::type_] = std::move(std::make_unique<EditTypeCharT>());
}

// ------------------------------------------------------------------------------------------------------

// BOOL

LogicEditFactory::LogicEditFactory() : Factory(AttributeType::BOOL)
{
    this->registerPrototype<CheckBox>();
    this->registerPrototype<LogicButton>();
}

LogicEditFactory *LogicEditFactory::getInstance()
{
    static LogicEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new LogicEditFactory();
    }

    return instance;
}

template <typename EditTypeLogicT>
inline void LogicEditFactory::registerPrototype()
{
    if (!findInVector(nameOfControlTypesVector_, EditTypeLogicConverter::EnumToString(EditTypeLogicT::type_).data()))
    {
        nameOfControlTypesVector_.emplace_back(EditTypeLogicConverter::EnumToString(EditTypeLogicT::type_));
    }
    prototypes_[EditTypeLogicT::type_] = std::move(std::make_unique<EditTypeLogicT>());
}


//-------------------------------------------------------------------------------------------------------

// CLUSTER

ClusterEditFactory::ClusterEditFactory() : Factory(AttributeType::CLUSTER)
{
    this->registerPrototype<Tree>();
}

ClusterEditFactory *ClusterEditFactory::getInstance()
{
    static ClusterEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new ClusterEditFactory();
    }

    return instance;
}

template <typename EditTypeClusterT>
inline void ClusterEditFactory::registerPrototype()
{
    if (!findInVector(nameOfControlTypesVector_, EditTypeClusterConverter::EnumToString(EditTypeClusterT::type_).data()))
    {
        nameOfControlTypesVector_.emplace_back(EditTypeClusterConverter::EnumToString(EditTypeClusterT::type_));
    }
    prototypes_[EditTypeClusterT::type_] = std::move(std::make_unique<EditTypeClusterT>());
}



//-------------------------------------------------------------------------------------------------------

// LONG

LongEditFactory::LongEditFactory() : Factory(AttributeType::LONG)
{
    this->registerPrototype<LongSlider>();
    this->registerPrototype<LongVSlider>();
    this->registerPrototype<LongDrag>();
}

LongEditFactory *LongEditFactory::getInstance()
{
    static LongEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new LongEditFactory();
    }

    return instance;
}

template <typename EditTypeLongT>
inline void LongEditFactory::registerPrototype()
{
    if (!findInVector(nameOfControlTypesVector_, EditTypeNumberConverter::EnumToString(EditTypeLongT::type_).data()))
    {
        nameOfControlTypesVector_.emplace_back(EditTypeNumberConverter::EnumToString(EditTypeLongT::type_));
    }
    prototypes_[EditTypeLongT::type_] = std::move(std::make_unique<EditTypeLongT>());
}



//-------------------------------------------------------------------------------------------------------

// String

StringEditFactory::StringEditFactory() : Factory(AttributeType::STRING)
{
    this->registerPrototype<StringTextField>();
}

StringEditFactory *StringEditFactory::getInstance()
{
    static StringEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new StringEditFactory();
    }

    return instance;
}

template <typename EditTypeStringT>
inline void StringEditFactory::registerPrototype()
{
    if (!findInVector(nameOfControlTypesVector_, EditTypeStringConverter::EnumToString(EditTypeStringT::type_).data()))
    {
        nameOfControlTypesVector_.emplace_back(EditTypeStringConverter::EnumToString(EditTypeStringT::type_));
    }
    prototypes_[EditTypeStringT::type_] = std::move(std::make_unique<EditTypeStringT>());
}



//-------------------------------------------------------------------------------------------------------

// UINT

UintEditFactory::UintEditFactory() : Factory(AttributeType::UINT)
{
    this->registerPrototype<UintSlider>();
    this->registerPrototype<UintVSlider>();
    this->registerPrototype<UintDrag>();
}

UintEditFactory *UintEditFactory::getInstance()
{
    static UintEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new UintEditFactory();
    }

    return instance;
}

template <typename EditTypeUintT>
inline void UintEditFactory::registerPrototype()
{
    if (!findInVector(nameOfControlTypesVector_, EditTypeNumberConverter::EnumToString(EditTypeUintT::type_).data()))
    {
        nameOfControlTypesVector_.emplace_back(EditTypeNumberConverter::EnumToString(EditTypeUintT::type_));
    }
    prototypes_[EditTypeUintT::type_] = std::move(std::make_unique<EditTypeUintT>());
}



//-------------------------------------------------------------------------------------------------------

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