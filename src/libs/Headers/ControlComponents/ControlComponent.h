#pragma once
#include "ImplementedAttribute.h"
#include <variant>

enum class EditTypeNumber
{
    NOTACONTROL,
    SLIDER,
    VSLIDER,
    DRAG
};

enum class EditTypeCharText
{
    NOTACONTROL,
    TEXT
};

enum class EditTypeLogic
{
    NOTACONTROL,
    CHECKBOX,
    BUTTON
};

enum class EditTypeCluster
{
    NOTACONTROL,
    TREE,
    WINDOW
};

enum class EditTypeString
{
    NOTACONTROL,
    TEXT
};

struct NUMBERSLIDER
{
    static constexpr EditTypeNumber typeEnum = EditTypeNumber::SLIDER;
    static constexpr std::string_view typeString = "SLIDER";
};

struct NUMBERVSLIDER
{
    static constexpr EditTypeNumber typeEnum = EditTypeNumber::VSLIDER;
    static constexpr std::string_view typeString = "VSLIDER";
};

struct NUMBERDRAG
{
    static constexpr EditTypeNumber typeEnum = EditTypeNumber::DRAG;
    static constexpr std::string_view typeString = "DRAG";
};

struct CHECKBOX
{
    static constexpr EditTypeLogic typeEnum = EditTypeLogic::CHECKBOX;
    static constexpr std::string_view typeString = "CHECKBOX";
};

struct Button
{
    static constexpr EditTypeLogic typeEnum = EditTypeLogic::BUTTON;
    static constexpr std::string_view typeString = "BUTTON";
};

struct ClusterTree
{
    static constexpr EditTypeCluster typeEnum = EditTypeCluster::TREE;
    static constexpr std::string_view typeString = "TREE";
};

struct ClusterWindow
{
    static constexpr EditTypeCluster typeEnum = EditTypeCluster::WINDOW;
    static constexpr std::string_view typeString = "WINDOW";
};

struct CharText
{
    static constexpr EditTypeCharText typeEnum = EditTypeCharText::TEXT;
    static constexpr std::string_view typeString = "TEXT";
};

struct StringText
{
    static constexpr EditTypeString typeEnum = EditTypeString::TEXT;
    static constexpr std::string_view typeString = "TEXT";
};

using NumberEditTypes = std::tuple<NUMBERSLIDER, NUMBERVSLIDER, NUMBERDRAG>;
using CharEditTypes = std::tuple<CharText>;
using LogicEditTypes = std::tuple<CHECKBOX, Button>;
using ClusterEditTypes = std::tuple<ClusterTree, ClusterWindow>;
using StringEditTypes = std::tuple<StringText>;

template <typename EditTypeEnumT, typename TupleT>
struct EditTypeTemplateConverter
{
    static constexpr std::string_view EnumToString(EditTypeEnumT editType)
    {
        return StructUnpack<TupleT>::unpack([&]<typename... EditTypeParameter>()
                                            {
            std::string_view type = "";
            ((EditTypeParameter::typeEnum == editType ? type = EditTypeParameter::typeString : ""), ...);
            return type; });
    }

    static constexpr EditTypeEnumT StringToEnum(std::string_view editType)
    {
        return StructUnpack<TupleT>::unpack([&]<typename... EditTypeParameter>()
                                            {
            EditTypeEnumT type = static_cast<EditTypeEnumT>(1);
            ((EditTypeParameter::typeString == editType ? type = EditTypeParameter::typeEnum : EditTypeEnumT::NOTACONTROL), ...);
            return type; });
    }
};

struct EditTypeNumberConverter : public EditTypeTemplateConverter<EditTypeNumber, NumberEditTypes>
{
};
struct EditTypeCharConverter : public EditTypeTemplateConverter<EditTypeCharText, CharEditTypes>
{
};
struct EditTypeLogicConverter : public EditTypeTemplateConverter<EditTypeLogic, LogicEditTypes>
{
};
struct EditTypeClusterConverter : public EditTypeTemplateConverter<EditTypeCluster, ClusterEditTypes>
{
};

struct EditTypeStringConverter : public EditTypeTemplateConverter<EditTypeString, StringEditTypes>
{
};

class ControlComponentsContainer;

class ControlComponent
{
protected:
    ImVec2 dimensions_;

public:
    ImVec2 getDimensions() { return dimensions_; }

public:
    virtual void draw(std::vector<Message> &messageHistory) = 0;
    virtual std::string getName() = 0;
    virtual ~ControlComponent() = default;
    virtual void setAttribute(Attribute *attribute) = 0;
    virtual std::unique_ptr<ControlComponent> clone() = 0;
    virtual Attribute *getAttribute(std::string_view name) = 0;
    virtual bool sameName(std::string name) = 0;
    virtual std::string getType(std::string_view name) = 0;
    virtual void updateLimitValues() = 0;
    virtual ControlComponentsContainer *getContainer() = 0;
};

template <EditTypeNumber TYPE, typename TypeT, typename AttributeT>
class NumberBaseControlComponent : public ControlComponent
{
protected:
    TypeT value_;
    TypeT minimum_;
    TypeT maximum_;
    AttributeT *attribute_;
    float minimumWidth_;
    float maximumWidth_;

public:
    static constexpr EditTypeNumber type_ = TYPE;
    void setAttribute(Attribute *attribute) override
    {
        if (dynamic_cast<AttributeT *>(attribute))
        {
            attribute_ = dynamic_cast<AttributeT *>(attribute);
            value_ = attribute_->getValue();
            minimum_ = attribute_->getMinimum();
            maximum_ = attribute_->getMaximum();
        }
    }
    std::string getName() override { return attribute_->getName(); };
    Attribute *getAttribute(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? attribute_ : nullptr; };
    std::string getType(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? EditTypeNumberConverter::EnumToString(type_).data() : ""; }
    bool sameName(std::string name) { return (attribute_ != nullptr && (attribute_->getName().compare(name) == 0)) ? true : false; }
    void updateLimitValues()
    {
        minimum_ = attribute_->getMinimum();
        maximum_ = attribute_->getMaximum();
    }

private:
    ControlComponentsContainer *getContainer() { return nullptr; }
};
template <EditTypeNumber TYPE>
class ControlComponentInt : public NumberBaseControlComponent<TYPE, int, AttributeInt>
{
};

template <EditTypeNumber TYPE>
class ControlComponentDouble : public NumberBaseControlComponent<TYPE, double, AttributeDouble>
{
};

template <EditTypeNumber TYPE>
class ControlComponentFloat : public NumberBaseControlComponent<TYPE, float, AttributeFloat>
{
};

template <EditTypeNumber TYPE>
class ControlComponentCharNumber : public NumberBaseControlComponent<TYPE, char, AttributeCharNumber>
{
};

template <EditTypeNumber TYPE>
class ControlComponentUInt : public NumberBaseControlComponent<TYPE, uint32_t, AttributeUint>
{
};

template <EditTypeNumber TYPE>
class ControlComponentLong : public NumberBaseControlComponent<TYPE, long, AttributeLong>
{
};

template <EditTypeCharText TYPE>
class ControlComponentCharText : public ControlComponent
{
protected:
    char value_[2];
    char minimum_;
    char maximum_;
    AttributeCharText *attribute_;
    float minimumWidth_;
    float maximumWidth_;
    ImGuiDataType dataType_;


public:
    static constexpr EditTypeCharText type_ = TYPE;
    void setAttribute(Attribute *attribute) override
    {

        if (dynamic_cast<AttributeCharText *>(attribute))
        {
            std::memset(value_, 0, 2);
            attribute_ = dynamic_cast<AttributeCharText *>(attribute);
            value_[0] = attribute_->getValue();
            minimum_ = attribute_->getMinimum();
            maximum_ = attribute_->getMaximum();
            dataType_ = ImGuiDataType_U8;
        }
    }
    std::string getName() override { return attribute_->getName(); };
    Attribute *getAttribute(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? attribute_ : nullptr; };
    std::string getType(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? EditTypeCharConverter::EnumToString(type_).data() : ""; }
    bool sameName(std::string name) { return (attribute_ != nullptr && (attribute_->getName().compare(name) == 0)) ? true : false; }
    void updateLimitValues()
    {
        minimum_ = attribute_->getMinimum();
        maximum_ = attribute_->getMaximum();
    }

    

private:
    ControlComponentsContainer *getContainer() { return nullptr; }
};

template <EditTypeLogic TYPE>
class ControlComponentBool : public ControlComponent
{
protected:
    bool value_;
    AttributeBool *attribute_;
    float minimumWidth_;

public:
    static constexpr EditTypeLogic type_ = TYPE;
    void setAttribute(Attribute *attribute) override
    {
        if (dynamic_cast<AttributeBool *>(attribute))
        {
            attribute_ = dynamic_cast<AttributeBool *>(attribute);
            value_ = attribute_->getValue();
        }
    }
    std::string getName() override { return attribute_->getName(); };
    Attribute *getAttribute(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? attribute_ : nullptr; };
    std::string getType(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? EditTypeLogicConverter::EnumToString(type_).data() : ""; }
    bool sameName(std::string name) { return (attribute_ != nullptr && (attribute_->getName().compare(name) == 0)) ? true : false; }
    void updateLimitValues() {}
    

private:
    ControlComponentsContainer *getContainer() { return nullptr; }
};

template <EditTypeCluster TYPE>
class ControlComponentCluster : public ControlComponent
{
protected:
    AttributeCluster *attribute_;
    ControlComponentsContainer *components_;
    ImVec2 showAttributesWindowSize_;
    bool drawed = false;

public:
    ControlComponentCluster()
    {
        showAttributesWindowSize_ = ImVec2(600, 800);
    }
    static constexpr EditTypeCluster type_ = TYPE;
    std::string getName() override { return attribute_->getName(); }
    void setAttribute(Attribute *attribute);
    Attribute *getAttribute(std::string_view name) override
    {
        if (!name.empty() && sameName(name.data()))
        {
            return attribute_;
        }
        return nullptr;
    };
    std::string getType(std::string_view name) override;
    ControlComponentsContainer *getContainer() { return components_; }
    void updateLimitValues();
    bool sameName(std::string name);
    
};

template <EditTypeString TYPE>
class ControlComponentString : public ControlComponent
{
protected:
    char *buffer;
    uint32_t minimum_;
    uint32_t maximum_;
    AttributeString *attribute_;
    float minimumWidth_;
    float maximumWidth_;
    ImGuiDataType dataType_;

public:
    static constexpr EditTypeString type_ = TYPE;
    std::string getName() override { return attribute_->getName(); }
    void setAttribute(Attribute *attribute) override
    {

        if (dynamic_cast<AttributeString *>(attribute))
        {
            attribute_ = dynamic_cast<AttributeString *>(attribute);
            minimum_ = attribute_->getMinimum();
            maximum_ = attribute_->getMaximum();
            buffer = new char[maximum_ + 1];
            std::memset(buffer, 0, sizeof(buffer));
            dataType_ = ImGuiDataType_U32;
        }
    }
    Attribute *getAttribute(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? attribute_ : nullptr; };
    std::string getType(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? EditTypeStringConverter::EnumToString(type_).data() : ""; }
    void updateLimitValues()
    {
        minimum_ = attribute_->getMinimum();
        maximum_ = attribute_->getMaximum();
        char *tmpBuffer = new char[maximum_ + 1];
        if (sizeof(tmpBuffer) < sizeof(buffer))
        {
            std::copy_n(buffer, maximum_, tmpBuffer);
            delete (buffer);
            buffer = std::move(tmpBuffer);
        }
        else
        {
            std::memset(tmpBuffer, 0, sizeof(tmpBuffer));
            std::copy_n(buffer, maximum_, tmpBuffer);
            delete (buffer);
            buffer = std::move(tmpBuffer);
        }
    }
    bool sameName(std::string name) { return (attribute_ != nullptr && (attribute_->getName().compare(name) == 0)) ? true : false; }
    ~ControlComponentString()
    {
        delete (buffer);
    }

    

private:
    ControlComponentsContainer *
    getContainer()
    {
        return nullptr;
    }
};