#pragma once

#include "json.hpp"
#include "Messages.h"
#include "imgui.h"

#include <string>
#include <variant>
#include <memory>

enum class AttributeType
{
    NOTATYPE,
    INT,
    DOUBLE,
    FLOAT,
    CHARN,
    CHART,
    LONG,
    UINT,
    BOOL,
    CLUSTER,
    STRING
};

enum class Category
{
    NOTACATEGORY,
    NUMERIC,
    TEXT,
    LOGIC,
    OTHER
};

// -----------------------------------------------------------------------

/// Metadata for the INT attribute type.
struct Int
{
    static constexpr std::string_view typeString = "INT";
    static constexpr AttributeType typeEnum = AttributeType::INT;
    static constexpr std::string_view typeInFile = "int";
};

/// Metadata for the DOUBLE attribute type.
struct Double
{
    static constexpr std::string_view typeString = "DOUBLE";
    static constexpr AttributeType typeEnum = AttributeType::DOUBLE;
    static constexpr std::string_view typeInFile = "double";
};

/// Metadata for the FLOAT attribute type.
struct Float
{
    static constexpr std::string_view typeString = "FLOAT";
    static constexpr AttributeType typeEnum = AttributeType::FLOAT;
    static constexpr std::string_view typeInFile = "float";
};

/// Metadata for the CHARN attribute type.
struct CharN
{
    static constexpr std::string_view typeString = "CHARN";
    static constexpr AttributeType typeEnum = AttributeType::CHARN;
    static constexpr std::string_view typeInFile = "char";
};

/// Metadata for the CHART attribute type.
struct CharT
{
    static constexpr std::string_view typeString = "CHART";
    static constexpr AttributeType typeEnum = AttributeType::CHART;
    static constexpr std::string_view typeInFile = "char";
};

/// Metadata for the LONG attribute type.
struct Long
{
    static constexpr std::string_view typeString = "LONG";
    static constexpr AttributeType typeEnum = AttributeType::LONG;
    static constexpr std::string_view typeInFile = "long";
};

/// Metadata for the UINT attribute type.
struct Uint
{
    static constexpr std::string_view typeString = "UINT";
    static constexpr AttributeType typeEnum = AttributeType::UINT;
    static constexpr std::string_view typeInFile = "uint32_t";
};

/// Metadata for the BOOL attribute type.
struct Bool
{
    static constexpr std::string_view typeString = "BOOL";
    static constexpr AttributeType typeEnum = AttributeType::BOOL;
    static constexpr std::string_view typeInFile = "bool";
};

/// Metadata for the CLUSTER attribute type.
struct Cluster
{
    static constexpr std::string_view typeString = "CLUSTER";
    static constexpr AttributeType typeEnum = AttributeType::CLUSTER;
    static constexpr std::string_view typeInFile = "cluster";
};

/// Metadata for the STRING attribute type.
struct String
{
    static constexpr std::string_view typeString = "STRING";
    static constexpr AttributeType typeEnum = AttributeType::STRING;
    static constexpr std::string_view typeInFile = "string";
};

using AttributeTypes = std::tuple<Int, Double, Float, CharN, CharT, Long, Uint, Bool, Cluster, String>;

// -----------------------------------------------------------------------

/// Metadata for the NUMERIC category.
struct Numeric
{
    static constexpr std::string_view categoryString = "NUMERIC";
    static constexpr Category categoryEnum = Category::NUMERIC;
};

/// Metadata for the TEXT category.
struct Text
{
    static constexpr std::string_view categoryString = "TEXT";
    static constexpr Category categoryEnum = Category::TEXT;
};

/// Metadata for the LOGIC category.
struct Logic
{
    static constexpr std::string_view categoryString = "LOGIC";
    static constexpr Category categoryEnum = Category::LOGIC;
};

/// Metadata for the OTHER category.
struct Other
{
    static constexpr std::string_view categoryString = "OTHER";
    static constexpr Category categoryEnum = Category::OTHER;
};

using CategoryTypes = std::tuple<Numeric, Text, Logic, Other>;

// -----------------------------------------------------------------------

/// Helper to unpack a tuple of types and invoke a compile-time predicate.
template <typename Tuple>
struct StructUnpack;

template <typename... Ts>
struct StructUnpack<std::tuple<Ts...>>
{
    template <typename FunctionT>
    static constexpr auto unpack(FunctionT &&predicate)
    {
        return predicate.template operator()<Ts...>();
    }
};

// -----------------------------------------------------------------------

struct AttributeTypeConverter
{
    /// Convert an AttributeType enum to its string identifier.
    static constexpr std::string_view EnumToString(AttributeType attributeType)
    {
        return StructUnpack<AttributeTypes>::unpack([&]<typename... AttributeTypesParameter>()
                                                    {
            std::string_view type = "";
            ((AttributeTypesParameter::typeEnum == attributeType ? type = AttributeTypesParameter::typeString : ""), ...);
            return type; });
    }

    /// Convert a string identifier to the corresponding AttributeType enum.
    static constexpr AttributeType StringToEnum(std::string_view attributeType)
    {
        return StructUnpack<AttributeTypes>::unpack([&]<typename... AttributeTypesParameter>()
                                                    {
            AttributeType type = AttributeType::NOTATYPE;
            ((AttributeTypesParameter::typeString == attributeType ? type = AttributeTypesParameter::typeEnum : AttributeType::NOTATYPE), ...);
            return type; });
    }

    /// Convert an AttributeType enum to the file type string used for code generation.
    static constexpr std::string_view EnumToFileString(AttributeType attributeType)
    {
        return StructUnpack<AttributeTypes>::unpack([&]<typename... AttributeTypesParameter>()
                                                    {
            std::string_view type = "";
            ((AttributeTypesParameter::typeEnum == attributeType ? type = AttributeTypesParameter::typeInFile : ""), ...);
            return type; });
    }
};

// -----------------------------------------------------------------------

struct CategoryConverter
{
    /// Convert a Category enum to its string identifier.
    static constexpr std::string_view EnumToString(Category category)
    {
        return StructUnpack<CategoryTypes>::unpack([&]<typename... CategoryParameter>()
                                                   {
            std::string_view tmpCategory = "";
            ((CategoryParameter::categoryEnum == category ? tmpCategory = CategoryParameter::categoryString : ""), ...);
            return tmpCategory; });
    }

    /// Convert a string identifier to the corresponding Category enum.
    static constexpr Category StringToEnum(std::string_view category)
    {
        return StructUnpack<CategoryTypes>::unpack([&]<typename... CategoryParameter>()
                                                   {
            Category tmpCategory = Category::NOTACATEGORY;
            ((CategoryParameter::categoryString == category ? tmpCategory = CategoryParameter::categoryEnum : Category::NOTACATEGORY), ...);
            return tmpCategory; });
    }
};

// -----------------------------------------------------------------------

class AttributesDescriptionsContainer;

class AttributeDescription
{
protected:
    std::string name_;
    AttributeType type_;
    Category category_;
    bool assigned_;
    uint64_t id_;
    ImGuiDataType dataType_;
public:
    /// Create a base attribute description with the specified attribute type.
    AttributeDescription(AttributeType type) : type_(type), assigned_(false), id_(0) {};

    /// Return the attribute name.
    inline std::string getName() { return name_; };

    /// Return the attribute type enum.
    inline AttributeType getType() { return type_; };

    /// Return the attribute type as a string identifier.
    inline std::string getTypeString() { return AttributeTypeConverter::EnumToString(type_).data(); }

    /// Return the category as a string identifier.
    inline std::string getCategory() { return CategoryConverter::EnumToString(category_).data(); };

    /// Set the attribute name if it is not longer than 40 characters.
    inline void setName(std::string name)
    {
        if (name.length() <= 40)
        {
            name_ = name;
        }
    };

    /// Set the attribute category.
    inline void setCategory(Category category) { category_ = category; }

    /// Mark the attribute as assigned or unassigned.
    inline void setAssigned(bool assigned) { assigned_ = assigned; }

    /// Query whether the attribute is assigned.
    inline bool isAssigned() { return assigned_; }

    /// Set the unique attribute identifier.
    void setID(uint64_t id)
    {
        id_ = id;
    }

    /// Get the unique attribute identifier.
    uint64_t getID() { return id_; }

    /// Return the ImGui data type associated with this attribute.
    ImGuiDataType getDataType() {
        return dataType_;
    }

public:
    /// Virtual destructor to allow proper cleanup in derived classes.
    virtual ~AttributeDescription() = 0;

    /// Create a polymorphic copy of this attribute description.
    virtual std::unique_ptr<AttributeDescription> clone() = 0;

    /// Parse attribute data from JSON and populate any parse messages.
    virtual bool jsonParse(nlohmann::ordered_json &json, std::vector<Message> *messagesHistory) = 0;

    /// Add this description to the provided vector if it matches the given type.
    virtual void addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type) = 0;

    /// Return the associated container for this description by name and identifier.
    virtual AttributesDescriptionsContainer *getContainer(std::string_view descriptionName, uint64_t descriptionId) = 0;

    /// Draw ImGui controls for changing attribute limits and return whether the input changed.
    virtual bool drawInputForChangingLimits(std::vector<Message> *messagesHistory) = 0;
    
};
