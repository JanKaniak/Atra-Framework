#pragma once

#include "json.hpp"
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
    CHAR,
    LONG,
    UINT
};

struct INT {
    static constexpr std::string_view typeString = "INT";
    static constexpr AttributeType typeEnum = AttributeType::INT;
};

struct DOUBLE {
    static constexpr std::string_view typeString = "DOUBLE";
    static constexpr AttributeType typeEnum = AttributeType::DOUBLE;
};

struct FLOAT {
    static constexpr std::string_view typeString = "FLOAT";
    static constexpr AttributeType typeEnum = AttributeType::FLOAT;
};

struct CHAR {
    static constexpr std::string_view typeString = "CHAR";
    static constexpr AttributeType typeEnum = AttributeType::CHAR;
};

struct LONG {
    static constexpr std::string_view typeString = "LONG";
    static constexpr AttributeType typeEnum = AttributeType::LONG;
};

struct UINT {
    static constexpr std::string_view typeString = "UINT";
    static constexpr AttributeType typeEnum = AttributeType::UINT;
};

using AttributeTypes = std::tuple<INT,DOUBLE,FLOAT,CHAR,LONG,UINT>;

template <typename Tuple>
struct StructUnpack;

template <typename... Ts>
struct StructUnpack<std::tuple<Ts...>> {
    template <typename FunctionT>
    static constexpr auto unpack(FunctionT&& predicate) {
        return predicate.template operator()<Ts...>();
    }
};


struct AttributeTypeConverter
{
    static constexpr std::string_view EnumToString(AttributeType attributeType)
    {
        return StructUnpack<AttributeTypes>::unpack([&]<typename... AttributeTypesParameter>() {
            std::string_view type = "";
            ((AttributeTypesParameter::typeEnum == attributeType ? type = AttributeTypesParameter::typeString : ""), ...);
            return type;
        });
    }

    static constexpr AttributeType StringToEnum(std::string_view attributeType)
    {
        return StructUnpack<AttributeTypes>::unpack([&]<typename... AttributeTypesParameter>() {
            AttributeType type = AttributeType::NOTATYPE;
            ((AttributeTypesParameter::typeString == attributeType ? type = AttributeTypesParameter::typeEnum : AttributeType::NOTATYPE), ...);
            return type;
        });
    }
};

/*enum class Category {
    NUMERIC,
    TEXT,
    OTHER
};*/

class AttributeDescription
{
protected:
    std::string name_;
    AttributeType type_;
    std::string category_;
    ImGuiDataType dataType_;

public:
    AttributeDescription(AttributeType type) : type_(type) {};
    inline std::string getName() { return name_; };
    inline AttributeType getType() { return type_; };
    inline std::string_view getTypeString() { return AttributeTypeConverter::EnumToString(type_); }
    inline std::string getCategory() { return category_; };
    inline void setName(std::string name) { name_ = name; };
    inline void setCategory(std::string category) { category_ = category; }
    inline ImGuiDataType getDataType() { return dataType_; }

public:
    virtual ~AttributeDescription() = default;
    virtual std::unique_ptr<AttributeDescription> clone() = 0;
    virtual bool jsonParse(nlohmann::ordered_json &json, std::string &outputMessage) = 0;
};
