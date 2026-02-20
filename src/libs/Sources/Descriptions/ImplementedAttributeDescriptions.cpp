#include "ImplementedAttributeDescriptions.h"

#include <iostream>

template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
void IntegerNumberBaseClass<TypeT, ImGuiDataTypeT, TypeEnumT>::setLimit(TypeT minimum, TypeT maximum)
{
    if (minimum < maximum)
    {
        min_ = minimum;
        max_ = maximum;
    }
}

template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool IntegerNumberBaseClass<TypeT, ImGuiDataTypeT, TypeEnumT>::jsonParse(nlohmann::ordered_json &json, std::string &outputMessage)
{
    if (json.find("Minimum") == json.end() || json.find("Maximum") == json.end() || json.find("Attribute name") == json.end()) {
        outputMessage = "Incorrect json format!";
        return false;
    }
    if ((!json["Minimum"].is_number_integer() && json["Minimum"].type() != TypeEnumT) || (!json["Maximum"].is_number_integer() && json["Maximum"].type() != TypeEnumT))
    {
        std::cout << json["Minimum"] << "\n";
        outputMessage = "Bounds must be number value!";
        return false;
    }

    auto tmpMinimum = json["Minimum"].get<long long>();
    auto tmpMaximum = json["Maximum"].get<long long>();

    if ((tmpMaximum > std::numeric_limits<TypeT>::max() || tmpMaximum < std::numeric_limits<TypeT>::min()) || (tmpMinimum > std::numeric_limits<TypeT>::max() || tmpMinimum < std::numeric_limits<TypeT>::min())) {
        outputMessage = "Bounds must be INSERT value!";
        return false;
    }

    if(!json["Attribute name"].is_string()) {
        outputMessage = "Name must be string type!";
        return false;
    }

    setName(json["Attribute name"].get<std::string>());
    setLimit(json["Minimum"].get<TypeT>(), json["Maximum"].get<TypeT>());
    return true;
}


template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
void DecimalNumberBaseClass<TypeT, ImGuiDataTypeT, TypeEnumT>::setLimit(TypeT minimum, TypeT maximum)
{
    if (minimum < maximum)
    {
        min_ = minimum;
        max_ = maximum;
    }
}

template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool DecimalNumberBaseClass<TypeT, ImGuiDataTypeT, TypeEnumT>::jsonParse(nlohmann::ordered_json &json, std::string &outputMessage)
{
    if (json.find("Minimum") == json.end() || json.find("Maximum") == json.end() || json.find("Attribute name") == json.end()) {
        outputMessage = "Incorrect json format!";
        return false;
    }
    if ((!json["Minimum"].is_number_float() && json["Minimum"].type() != TypeEnumT) || (!json["Minimum"].is_number_float() && json["Maximum"].type() != TypeEnumT))
    {
        std::cout << json["Minimum"] << "\n";
        outputMessage = "Bounds must be number value!";
        return false;
    }

    if(!json["Attribute name"].is_string()) {
        outputMessage = "Name must be string type!";
        return false;
    }

    setName(json["Attribute name"].get<std::string>());
    setLimit(json["Minimum"].get<TypeT>(), json["Maximum"].get<TypeT>());
    return true;
}





// CHAR
std::unique_ptr<AttributeDescription> AttributeDescription_char::clone() { return std::make_unique<AttributeDescription_char>(*this); }
void AttributeDescription_char::setLimit(int minimum) {
            if (minimum <= max_ && minimum >= 0) {
                min_ = minimum;
            }
        }

bool AttributeDescription_char::jsonParse(nlohmann::ordered_json &json, std::string &outputMessage)
{
    if (!json["Minimum"].is_number_integer())
    {
        outputMessage = "Bounds must be int value!";
        return false;
    }

    if(!json["Attribute name"].is_string()) {
        outputMessage = "Name must be string type!";
        return false;
    }

    setName(json["Attribute name"].get<std::string>());
    setLimit(json["Minimum"].get<int>());
    return true;
}


std::unique_ptr<AttributeDescription> AttributeDescription_int::clone() { return std::make_unique<AttributeDescription_int>(*this);}

std::unique_ptr<AttributeDescription> AttributeDescription_double::clone() { return std::make_unique<AttributeDescription_double>(*this);}

std::unique_ptr<AttributeDescription> AttributeDescription_float::clone() { return std::make_unique<AttributeDescription_float>(*this);}

std::unique_ptr<AttributeDescription> AttributeDescription_long::clone() { return std::make_unique<AttributeDescription_long>(*this);}

std::unique_ptr<AttributeDescription> AttributeDescription_uint::clone() { return std::make_unique<AttributeDescription_uint>(*this);}

