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

struct Int
{
    static constexpr std::string_view typeString = "INT";
    static constexpr AttributeType typeEnum = AttributeType::INT;
    static constexpr std::string_view typeInFile = "int";
};

struct Double
{
    static constexpr std::string_view typeString = "DOUBLE";
    static constexpr AttributeType typeEnum = AttributeType::DOUBLE;
    static constexpr std::string_view typeInFile = "double";
};

struct Float
{
    static constexpr std::string_view typeString = "FLOAT";
    static constexpr AttributeType typeEnum = AttributeType::FLOAT;
    static constexpr std::string_view typeInFile = "float";
};

struct CharN
{
    static constexpr std::string_view typeString = "CHARN";
    static constexpr AttributeType typeEnum = AttributeType::CHARN;
    static constexpr std::string_view typeInFile = "char";
};

struct CharT
{
    static constexpr std::string_view typeString = "CHART";
    static constexpr AttributeType typeEnum = AttributeType::CHART;
    static constexpr std::string_view typeInFile = "char";
};

struct Long
{
    static constexpr std::string_view typeString = "LONG";
    static constexpr AttributeType typeEnum = AttributeType::LONG;
    static constexpr std::string_view typeInFile = "long";
};

struct Uint
{
    static constexpr std::string_view typeString = "UINT";
    static constexpr AttributeType typeEnum = AttributeType::UINT;
    static constexpr std::string_view typeInFile = "uint32_t";
};

struct Bool
{
    static constexpr std::string_view typeString = "BOOL";
    static constexpr AttributeType typeEnum = AttributeType::BOOL;
    static constexpr std::string_view typeInFile = "bool";
};

struct Cluster
{
    static constexpr std::string_view typeString = "CLUSTER";
    static constexpr AttributeType typeEnum = AttributeType::CLUSTER;
    static constexpr std::string_view typeInFile = "cluster";
};

struct String
{
    static constexpr std::string_view typeString = "STRING";
    static constexpr AttributeType typeEnum = AttributeType::STRING;
    static constexpr std::string_view typeInFile = "string";
};

using AttributeTypes = std::tuple<Int, Double, Float, CharN, CharT, Long, Uint, Bool, Cluster, String>;

// -----------------------------------------------------------------------

struct Numeric
{
    static constexpr std::string_view categoryString = "NUMERIC";
    static constexpr Category categoryEnum = Category::NUMERIC;
};

struct Text
{
    static constexpr std::string_view categoryString = "TEXT";
    static constexpr Category categoryEnum = Category::TEXT;
};

struct Logic
{
    static constexpr std::string_view categoryString = "LOGIC";
    static constexpr Category categoryEnum = Category::LOGIC;
};

struct Other
{
    static constexpr std::string_view categoryString = "OTHER";
    static constexpr Category categoryEnum = Category::OTHER;
};

using CategoryTypes = std::tuple<Numeric, Text, Logic, Other>;

// -----------------------------------------------------------------------

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
    static constexpr std::string_view EnumToString(AttributeType attributeType)
    {
        return StructUnpack<AttributeTypes>::unpack([&]<typename... AttributeTypesParameter>()
                                                    {
            std::string_view type = "";
            ((AttributeTypesParameter::typeEnum == attributeType ? type = AttributeTypesParameter::typeString : ""), ...);
            return type; });
    }

    static constexpr AttributeType StringToEnum(std::string_view attributeType)
    {
        return StructUnpack<AttributeTypes>::unpack([&]<typename... AttributeTypesParameter>()
                                                    {
            AttributeType type = AttributeType::NOTATYPE;
            ((AttributeTypesParameter::typeString == attributeType ? type = AttributeTypesParameter::typeEnum : AttributeType::NOTATYPE), ...);
            return type; });
    }

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
    static constexpr std::string_view EnumToString(Category category)
    {
        return StructUnpack<CategoryTypes>::unpack([&]<typename... CategoryParameter>()
                                                   {
            std::string_view tmpCategory = "";
            ((CategoryParameter::categoryEnum == category ? tmpCategory = CategoryParameter::categoryString : ""), ...);
            return tmpCategory; });
    }

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
    AttributeDescription(AttributeType type) : type_(type), assigned_(false), id_(0) {};
    inline std::string getName() { return name_; };
    inline AttributeType getType() { return type_; };
    inline std::string getTypeString() { return AttributeTypeConverter::EnumToString(type_).data(); }
    inline std::string getCategory() { return CategoryConverter::EnumToString(category_).data(); };
    inline void setName(std::string name)
    {
        if (name.length() <= 40)
        {
            name_ = name;
        }
    };
    inline void setCategory(Category category) { category_ = category; }
    inline void setAssigned(bool assigned) { assigned_ = assigned; }
    inline bool isAssigned() { return assigned_; }
    void setID(uint64_t id)
    {
        id_ = id;
    }
    uint64_t getID() { return id_; }
    ImGuiDataType getDataType() {
        return dataType_;
    }

public:
    virtual ~AttributeDescription() = 0;
    virtual std::unique_ptr<AttributeDescription> clone() = 0;
    virtual bool jsonParse(nlohmann::ordered_json &json, std::vector<Message> *messagesHistory) = 0;
    virtual void addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type) = 0;
    virtual AttributesDescriptionsContainer *getContainer(std::string_view descriptionName, uint64_t descriptionId) = 0;
    virtual bool drawInputForChangingLimits(std::vector<Message> *messagesHistory) = 0;
    
};
