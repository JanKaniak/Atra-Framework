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

enum class EditTypeChar
{
    NOTACONTROL,
    TEXT,
};

enum class EditTypeLogic
{
    NOTACONTROL,
    CHECKBOX,
    BUTTON
};

enum class EditTypeCluster
{
    DEFAULT
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

struct CHARTEXT
{
    static constexpr EditTypeChar typeEnum = EditTypeChar::TEXT;
    static constexpr std::string_view typeString = "TEXT";
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

using NumberEditTypes = std::tuple<NUMBERSLIDER, NUMBERVSLIDER, NUMBERDRAG>;
using CharEditTypes = std::tuple<CHARTEXT>;
using LogicEditTypes = std::tuple<CHECKBOX, Button>;

struct EditTypeNumberConverter
{
    static constexpr std::string_view EnumToString(EditTypeNumber editTypeNumber)
    {
        return StructUnpack<NumberEditTypes>::unpack([&]<typename... EditTypeNumberParameter>()
                                                     {
            std::string_view type = "";
            ((EditTypeNumberParameter::typeEnum == editTypeNumber ? type = EditTypeNumberParameter::typeString : ""), ...);
            return type; });
    }

    static constexpr EditTypeNumber StringToEnum(std::string_view editTypeNumber)
    {
        return StructUnpack<NumberEditTypes>::unpack([&]<typename... EditTypeNumberParameter>()
                                                     {
            EditTypeNumber type = EditTypeNumber::SLIDER;
            ((EditTypeNumberParameter::typeString == editTypeNumber ? type = EditTypeNumberParameter::typeEnum : EditTypeNumber::NOTACONTROL), ...);
            return type; });
    }
};

struct EditTypeCharConverter
{
    static constexpr std::string_view EnumToString(EditTypeChar charEditTypes)
    {
        return StructUnpack<CharEditTypes>::unpack([&]<typename... EditTypeCharParameter>()
                                                   {
            std::string_view type = "";
            ((EditTypeCharParameter::typeEnum == charEditTypes ? type = EditTypeCharParameter::typeString : ""), ...);
            return type; });
    }

    static constexpr EditTypeChar StringToEnum(std::string_view charEditTypes)
    {
        return StructUnpack<CharEditTypes>::unpack([&]<typename... EditTypeCharParameter>()
                                                   {
            EditTypeChar type = EditTypeChar::NOTACONTROL;
            ((EditTypeCharParameter::typeString == charEditTypes ? type = EditTypeCharParameter::typeEnum : EditTypeChar::NOTACONTROL), ...);
            return type; });
    }
};

struct EditTypeLogicConverter
{
    static constexpr std::string_view EnumToString(EditTypeLogic logicEditTypes)
    {
        return StructUnpack<LogicEditTypes>::unpack([&]<typename... EditTypeLogicParameter>()
                                                    {
            std::string_view type = "";
            ((EditTypeLogicParameter::typeEnum == logicEditTypes ? type = EditTypeLogicParameter::typeString : ""), ...);
            return type; });
    }

    static constexpr EditTypeLogic StringToEnum(std::string_view logicEditTypes)
    {
        return StructUnpack<LogicEditTypes>::unpack([&]<typename... EditTypeLogicParameter>()
                                                    {
            EditTypeLogic type = EditTypeLogic::NOTACONTROL;
            ((EditTypeLogicParameter::typeString == logicEditTypes ? type = EditTypeLogicParameter::typeEnum : EditTypeLogic::NOTACONTROL), ...);
            return type; });
    }
};

class ControlComponent
{
protected:
    // std::string controlType_;

public:
    virtual void draw() = 0;
    virtual std::string getName() = 0;
    virtual ~ControlComponent() = default;
    virtual void setAttribute(Attribute *attribute) = 0;
    virtual std::unique_ptr<ControlComponent> clone() = 0;
    virtual Attribute *getAttribute(std::string_view name) = 0;
    virtual bool sameName(std::string name) = 0;
    virtual std::string getType(std::string_view name) = 0;
    virtual void updateLimitValues() = 0;
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
    bool sameName(std::string name) { return (attribute_->getName().compare(name) == 0) ? true : false; }
    void updateLimitValues()
    {
        minimum_ = attribute_->getMinimum();
        maximum_ = attribute_->getMaximum();
    }
};
template <EditTypeNumber TYPE>
class ControlComponentInt : public NumberBaseControlComponent<TYPE, int, AttributeInt>
{
public:
};

template <EditTypeNumber TYPE>
class ControlComponentDouble : public NumberBaseControlComponent<TYPE, double, AttributeDouble>
{
public:
    static constexpr EditTypeNumber type_ = TYPE;
};

template <EditTypeNumber TYPE>
class ControlComponentFloat : public NumberBaseControlComponent<TYPE, float, AttributeFloat>
{
public:
    static constexpr EditTypeNumber type_ = TYPE;
};

template <EditTypeChar TYPE>
class ControlComponentChar : public ControlComponent
{
protected:
    char value_;
    int minimum_;
    int maximum_;
    AttributeChar *attributechar_;
    float minimumWidth_;

public:
    static constexpr EditTypeChar type_ = TYPE;
    void setAttribute(Attribute *attribute) override
    {
        if (dynamic_cast<AttributeChar *>(attribute))
        {
            attributechar_ = dynamic_cast<AttributeChar *>(attribute);
            value_ = attributechar_->getValue();
            minimum_ = attributechar_->getMinimum();
            maximum_ = attributechar_->getMaximum();
        }
    }
    std::string getName() override { return attributechar_->getName(); };
    Attribute *getAttribute(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? attributechar_ : nullptr; };
    std::string getType(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? EditTypeCharConverter::EnumToString(type_).data() : ""; }
    bool sameName(std::string name) { return (attributechar_->getName().compare(name) == 0) ? true : false; }
    void updateLimitValues()
    {
        minimum_ = attributechar_->getMinimum();
        maximum_ = attributechar_->getMaximum();
    }
};

template <EditTypeLogic TYPE>
class ControlComponentBool : public ControlComponent
{
protected:
    bool value_;
    AttributeBool *attributebool_;
    float minimumWidth_;

public:
    static constexpr EditTypeLogic type_ = TYPE;
    void setAttribute(Attribute *attribute) override
    {
        if (dynamic_cast<AttributeBool *>(attribute))
        {
            attributebool_ = dynamic_cast<AttributeBool *>(attribute);
            value_ = attributebool_->getValue();
        }
    }
    std::string getName() override { return attributebool_->getName(); };
    Attribute *getAttribute(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? attributebool_ : nullptr; };
    std::string getType(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? EditTypeLogicConverter::EnumToString(type_).data() : nullptr; }
    bool sameName(std::string name) { return (attributebool_->getName().compare(name) == 0) ? true : false; }
    void updateLimitValues() { }
};

class ControlComponentsContainer;

class ControlComponentCluster : public ControlComponent
{
private:
    AttributeCluster *attributecluster_;
    ControlComponentsContainer *components_;
    ImVec2 showAttributesWindowSize_;
    bool drawed = false;

public:
    ControlComponentCluster()
    {
        showAttributesWindowSize_ = ImVec2(600, 800);
    }
    static constexpr EditTypeCluster type_ = EditTypeCluster::DEFAULT;
    void draw() override;
    std::string getName() override { return attributecluster_->getName(); }
    void setAttribute(Attribute *attribute);
    std::unique_ptr<ControlComponent> clone() { return std::make_unique<ControlComponentCluster>(*this); }
    Attribute *getAttribute(std::string_view name) override
    {
        if (!name.empty() && sameName(name.data()))
        {
            return attributecluster_;
        }
        return nullptr;
    };
    std::string getType(std::string_view name) override;
    ControlComponentsContainer *getContainer() { return components_; }
    bool sameName(std::string name);
    void updateLimitValues();
    
};
