#include "Factory.h"
// FACTORIES ----------------------------------------------------------------------------------

// INT

/// Construct the integer edit factory and register its supported prototypes.
IntEditFactory::IntEditFactory() : Factory(AttributeType::INT)
{
    this->registerPrototype<IntSlider>();
    this->registerPrototype<IntVSlider>();
    this->registerPrototype<IntDrag>();
}

/// Return the singleton factory for integer edit controls.
IntEditFactory *IntEditFactory::getInstance()
{
    static IntEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new IntEditFactory();
    }

    return instance;
}

/// Register a concrete integer edit control prototype for this factory.
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

/// Construct the double edit factory and register its supported prototypes.
DoubleEditFactory::DoubleEditFactory() : Factory(AttributeType::DOUBLE)
{
    this->registerPrototype<DoubleSlider>();
    this->registerPrototype<DoubleVSlider>();
    this->registerPrototype<DoubleDrag>();
}

/// Return the singleton factory for double edit controls.
DoubleEditFactory *DoubleEditFactory::getInstance()
{
    static DoubleEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new DoubleEditFactory();
    }

    return instance;
}

/// Register a concrete double edit control prototype for this factory.
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

/// Return the singleton factory for float edit controls.
FloatEditFactory *FloatEditFactory::getInstance()
{
    static FloatEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new FloatEditFactory();
    }

    return instance;
}

/// Register a concrete float edit control prototype for this factory.
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


/// Construct the char-text edit factory and register its supported prototype.
CharTextEditFactory::CharTextEditFactory() : Factory(AttributeType::CHART)
{
    this->registerPrototype<CharTextField>();
}

/// Return the singleton factory for char-text edit controls.
CharTextEditFactory *CharTextEditFactory::getInstance()
{
    static CharTextEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new CharTextEditFactory();
    }

    return instance;
}

/// Register a concrete char-text edit control prototype for this factory.
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

/// Construct the char-number edit factory and register its supported prototypes.
CharNumberEditFactory::CharNumberEditFactory() : Factory(AttributeType::CHARN)
{
    this->registerPrototype<CharSlider>();
    this->registerPrototype<CharVSlider>();
    this->registerPrototype<CharDrag>();
}

/// Return the singleton factory for char-number edit controls.
CharNumberEditFactory *CharNumberEditFactory::getInstance()
{
    static CharNumberEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new CharNumberEditFactory();
    }

    return instance;
}

/// Register a concrete char-number edit control prototype for this factory.
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

/// Construct the logic edit factory and register its supported prototypes.
LogicEditFactory::LogicEditFactory() : Factory(AttributeType::BOOL)
{
    this->registerPrototype<CheckBox>();
    this->registerPrototype<LogicButton>();
}

/// Return the singleton factory for logic edit controls.
LogicEditFactory *LogicEditFactory::getInstance()
{
    static LogicEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new LogicEditFactory();
    }

    return instance;
}

/// Register a concrete logic edit control prototype for this factory.
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

/// Construct the cluster edit factory and register its supported prototype.
ClusterEditFactory::ClusterEditFactory() : Factory(AttributeType::CLUSTER)
{
    this->registerPrototype<Tree>();
}

/// Return the singleton factory for cluster edit controls.
ClusterEditFactory *ClusterEditFactory::getInstance()
{
    static ClusterEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new ClusterEditFactory();
    }

    return instance;
}

/// Register a concrete cluster edit control prototype for this factory.
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

/// Construct the long integer edit factory and register its supported prototypes.
LongEditFactory::LongEditFactory() : Factory(AttributeType::LONG)
{
    this->registerPrototype<LongSlider>();
    this->registerPrototype<LongVSlider>();
    this->registerPrototype<LongDrag>();
}

/// Return the singleton factory for long integer edit controls.
LongEditFactory *LongEditFactory::getInstance()
{
    static LongEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new LongEditFactory();
    }

    return instance;
}

/// Register a concrete long integer edit control prototype for this factory.
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

/// Construct the string edit factory and register its supported prototype.
StringEditFactory::StringEditFactory() : Factory(AttributeType::STRING)
{
    this->registerPrototype<StringTextField>();
}

/// Return the singleton factory for string edit controls.
StringEditFactory *StringEditFactory::getInstance()
{
    static StringEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new StringEditFactory();
    }

    return instance;
}

/// Register a concrete string edit control prototype for this factory.
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

/// Construct the unsigned integer edit factory and register its supported prototypes.
UintEditFactory::UintEditFactory() : Factory(AttributeType::UINT)
{
    this->registerPrototype<UintSlider>();
    this->registerPrototype<UintVSlider>();
    this->registerPrototype<UintDrag>();
}

/// Return the singleton factory for unsigned integer edit controls.
UintEditFactory *UintEditFactory::getInstance()
{
    static UintEditFactory *instance;
    if (instance == nullptr)
    {
        instance = new UintEditFactory();
    }

    return instance;
}

/// Register a concrete unsigned integer edit control prototype for this factory.
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

// ControlComponentsFactoriesContainer

/// Return the singleton registry for all control component factories.
ControlComponentsFactoriesContainer *ControlComponentsFactoriesContainer::getInstance()
{
    static ControlComponentsFactoriesContainer *instance;
    if (instance == nullptr)
    {
        return instance = new ControlComponentsFactoriesContainer();
    }
    return instance;
}

/// Return the factory responsible for the given attribute type, or nullptr if missing.
Factory *ControlComponentsFactoriesContainer::getFactory(AttributeType type)
{
    if (factoryChoice_.find(type) == factoryChoice_.end())
    {
        return nullptr;
    }
    return factoryChoice_[type];
}

/// Register a factory instance for the given attribute type.
void ControlComponentsFactoriesContainer::registerFactory(Factory *factory)
{
    factoryChoice_[factory->getType()] = factory;
}