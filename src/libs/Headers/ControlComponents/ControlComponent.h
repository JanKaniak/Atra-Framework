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

using NumberEditTypes = std::tuple<NUMBERSLIDER, NUMBERVSLIDER, NUMBERDRAG>;
using CharEditTypes = std::tuple<CHARTEXT>;

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

class ControlComponent
{
protected:
    // std::string controlType_;

public:
    virtual std::string getType() = 0;

public:
    virtual void draw() = 0;
    virtual std::string getName() = 0;
    virtual ~ControlComponent() = default;
    virtual void setAttribute(Attribute *attribute) = 0;
    virtual std::unique_ptr<ControlComponent> clone() = 0;
    virtual Attribute *getAttribute() = 0;
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
    Attribute *getAttribute() override { return attribute_; };
    std::string getType() override { return EditTypeNumberConverter::EnumToString(type_).data(); }
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
    Attribute *getAttribute() override { return attributechar_; };
    std::string getType() override { return EditTypeCharConverter::EnumToString(type_).data(); }
};
