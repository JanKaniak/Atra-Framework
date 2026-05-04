#pragma once
#include "ImplementedAttribute.h"
#include <variant>

/// Edit types available for numeric attribute controls.
enum class EditTypeNumber
{
    NOTACONTROL,
    SLIDER,
    VSLIDER,
    DRAG
};

/// Edit types available for char-text controls.
enum class EditTypeCharText
{
    NOTACONTROL,
    TEXT
};

/// Edit types available for boolean/logic controls.
enum class EditTypeLogic
{
    NOTACONTROL,
    CHECKBOX,
    BUTTON
};

/// Edit types available for cluster attribute controls.
enum class EditTypeCluster
{
    NOTACONTROL,
    TREE,
    WINDOW
};

/// Edit types available for string attribute controls.
enum class EditTypeString
{
    NOTACONTROL,
    TEXT
};

/// Helper structs describing concrete edit control options.
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

/// Generic converter between edit-type enums and string identifiers.
///
/// Uses a tuple of concrete edit type structs to map values bidirectionally.
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

/// Converters between edit type enums and string identifiers.
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

/// Abstract base class for all GUI control components bound to attributes.
///
/// Each implementation is responsible for rendering itself, tracking the
/// associated attribute, and reporting matching names/types.
class ControlComponent
{
protected:
    ImVec2 dimensions_;

public:
    ImVec2 getDimensions() { return dimensions_; }

public:
    /// Render the control into the UI.
    virtual void draw(std::vector<Message> &messageHistory) = 0;

    /// Return the name of the bound attribute.
    virtual std::string getName() = 0;

    virtual ~ControlComponent() = default;

    /// Bind this component to an attribute instance.
    virtual void setAttribute(Attribute *attribute) = 0;

    /// Clone the control component for reuse.
    virtual std::unique_ptr<ControlComponent> clone() = 0;

    /// Retrieve the bound attribute by name.
    virtual Attribute *getAttribute(std::string_view name) = 0;

    /// Check whether this component matches the given attribute name.
    virtual bool sameName(std::string_view name) = 0;

    /// Return the display type of this control for the given attribute.
    virtual std::string getType(std::string_view name) = 0;

    /// Refresh limit values from the current attribute metadata.
    virtual void updateLimitValues() = 0;

    /// Return the owning component container, if any.
    virtual ControlComponentsContainer *getContainer() = 0;
};

/// Base control component for numeric attributes.
///
/// This template binds a numeric attribute type to a specific edit control variant.
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

    /// Bind a numeric attribute and initialize its values/limits.
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
    /// Return the bound attribute name.
    std::string getName() override { return attribute_->getName(); };

    /// Retrieve the bound attribute by matching name.
    Attribute *getAttribute(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? attribute_ : nullptr; };

    /// Return the control type string when the name matches.
    std::string getType(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? EditTypeNumberConverter::EnumToString(type_).data() : ""; }

    /// Compare the given name against the bound attribute name.
    bool sameName(std::string_view name) override { return (!name.empty() && attribute_ != nullptr && (attribute_->getName().compare(name.data()) == 0)) ? true : false; }

    /// Refresh minimum and maximum limits from the bound attribute.
    void updateLimitValues() override
    {
        minimum_ = attribute_->getMinimum();
        maximum_ = attribute_->getMaximum();
    }

private:
    /// No owning container for this simple numeric control helper.
    ControlComponentsContainer *getContainer() { return nullptr; }
};

/// Numeric integer edit component for `AttributeInt`.
template <EditTypeNumber TYPE>
class ControlComponentInt : public NumberBaseControlComponent<TYPE, int, AttributeInt>
{
};

/// Numeric double edit component for `AttributeDouble`.
template <EditTypeNumber TYPE>
class ControlComponentDouble : public NumberBaseControlComponent<TYPE, double, AttributeDouble>
{
};

/// Numeric float edit component for `AttributeFloat`.
template <EditTypeNumber TYPE>
class ControlComponentFloat : public NumberBaseControlComponent<TYPE, float, AttributeFloat>
{
};

/// Numeric char edit component for `AttributeCharNumber`.
template <EditTypeNumber TYPE>
class ControlComponentCharNumber : public NumberBaseControlComponent<TYPE, char, AttributeCharNumber>
{
};

/// Numeric unsigned int edit component for `AttributeUint`.
template <EditTypeNumber TYPE>
class ControlComponentUInt : public NumberBaseControlComponent<TYPE, uint32_t, AttributeUint>
{
};

/// Numeric long edit component for `AttributeLong`.
template <EditTypeNumber TYPE>
class ControlComponentLong : public NumberBaseControlComponent<TYPE, long, AttributeLong>
{
};

/// Control component for editing char-text attributes.
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

    /// Bind a char-text attribute and initialize its display state.
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
    /// Return the bound attribute name.
    std::string getName() override { return attribute_->getName(); };

    /// Return the bound attribute if the requested name matches this component.
    Attribute *getAttribute(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? attribute_ : nullptr; };

    /// Return the concrete char-text control type for this bound attribute.
    std::string getType(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? EditTypeCharConverter::EnumToString(type_).data() : ""; }

    /// Compare the requested attribute name to the bound name.
    bool sameName(std::string_view name) override { return (!name.empty() && attribute_ != nullptr && (attribute_->getName().compare(name.data()) == 0)) ? true : false; }

    /// Refresh the allowed char range from the bound attribute.
    void updateLimitValues() override
    {
        minimum_ = attribute_->getMinimum();
        maximum_ = attribute_->getMaximum();
    }

private:
    /// No owning container for this char/text control.
    ControlComponentsContainer *getContainer() { return nullptr; }
};

/// Control component for boolean logic attributes.
template <EditTypeLogic TYPE>
class ControlComponentBool : public ControlComponent
{
protected:
    bool value_;
    AttributeBool *attribute_;
    float minimumWidth_;

public:
    static constexpr EditTypeLogic type_ = TYPE;

    /// Bind a boolean attribute and initialize its state.
    void setAttribute(Attribute *attribute) override
    {
        if (dynamic_cast<AttributeBool *>(attribute))
        {
            attribute_ = dynamic_cast<AttributeBool *>(attribute);
            value_ = attribute_->getValue();
        }
    }
    /// Return the bound attribute name.
    std::string getName() override { return attribute_->getName(); };

    /// Return the bound attribute when the requested name matches.
    Attribute *getAttribute(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? attribute_ : nullptr; };

    /// Return the boolean control type string when the name matches.
    std::string getType(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? EditTypeLogicConverter::EnumToString(type_).data() : ""; }

    /// Compare the requested attribute name to the bound boolean attribute.
    bool sameName(std::string_view name) override { return (!name.empty() && attribute_ != nullptr && (attribute_->getName().compare(name.data()) == 0)) ? true : false; }

    /// Boolean controls do not expose dynamic limit values.
    void updateLimitValues() override {}

private:
    /// No owning container for this bool control.
    ControlComponentsContainer *getContainer() { return nullptr; }
};

/// Control component for nested cluster attributes.
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

    /// Return the cluster attribute name.
    std::string getName() override { return attribute_->getName(); }

    /// Bind a cluster attribute and prepare nested controls.
    void setAttribute(Attribute *attribute);

    /// Return the cluster attribute when the requested name matches.
    Attribute *getAttribute(std::string_view name) override
    {
        if (!name.empty() && sameName(name.data()))
        {
            return attribute_;
        }
        return nullptr;
    };

    /// Return the control type string for the cluster.
    std::string getType(std::string_view name) override;

    /// Return the nested control component container.
    ControlComponentsContainer *getContainer() { return components_; }

    /// Refresh cluster control limits or layout settings.
    void updateLimitValues() override;

    /// Determine if this component is bound to the provided attribute name.
    bool sameName(std::string_view name) override;
};

/// Control component for string attributes.
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
    /// Return the bound attribute name.
    std::string getName() override { return attribute_->getName(); }

    /// Bind a string attribute and allocate a working text buffer.
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
    /// Return the bound attribute when the requested name matches.
    Attribute *getAttribute(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? attribute_ : nullptr; };

    /// Return the string control type when the requested name matches.
    std::string getType(std::string_view name) override { return (!name.empty() && sameName(name.data())) ? EditTypeStringConverter::EnumToString(type_).data() : ""; }

    /// Resize the internal text buffer when limits change.
    void updateLimitValues() override
    {
        minimum_ = attribute_->getMinimum();
        maximum_ = attribute_->getMaximum();
        char *tmpBuffer = new char[maximum_ + 1];
        if (sizeof(tmpBuffer) < sizeof(buffer))
        {
            std::copy_n(buffer, maximum_, tmpBuffer);
            delete (buffer);
            buffer = tmpBuffer;
        }
        else
        {
            std::memset(tmpBuffer, 0, sizeof(tmpBuffer));
            std::copy_n(buffer, maximum_, tmpBuffer);
            delete (buffer);
            buffer = tmpBuffer;
        }
    }
    /// Compare the requested attribute name to the bound string attribute.
    bool sameName(std::string_view name) override { return (!name.empty() && attribute_ != nullptr && (attribute_->getName().compare(name.data()) == 0)) ? true : false; }
    /// Release the allocated text buffer.
    ~ControlComponentString()
    {
        delete (buffer);
    }

    /// No owning container for this string control.
    ControlComponentsContainer *getContainer() { return nullptr; }
};