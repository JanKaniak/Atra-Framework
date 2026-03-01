#include "ImplementedAttributeDescriptions.h"

#include <format>

// INTEGER NUMBERS -------------------------------------------
template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool IntegerNumberBaseClass<TypeT, ImGuiDataTypeT, TypeEnumT>::setLimit(TypeT minimum, TypeT maximum, std::vector<Message>& messagesHistory)
{
    if (minimum < maximum)
    {
        min_ = minimum;
        max_ = maximum;
        messagesHistory.emplace_back(Message("Bounds were successfully changed!"));
        return true;
    }
    messagesHistory.emplace_back(Message("Minimum must be lower value than maximum!"));
    return false;
}

template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool IntegerNumberBaseClass<TypeT, ImGuiDataTypeT, TypeEnumT>::jsonParse(nlohmann::ordered_json &json, std::vector<Message>& messagesHistory)
{
    if (json.find("Minimum") == json.end() || json.find("Maximum") == json.end() || json.find("Attribute name") == json.end())
    {
        messagesHistory.emplace_back(Message("Incorrect json format!"));
        return false;
    }
    if (!json["Minimum"].is_number_integer() || !json["Maximum"].is_number_integer())
    {
        messagesHistory.emplace_back(Message(std::format("{} Bounds must be number value!", json["Attribute name"].get<std::string>())));
        return false;
    }

    if (!json["Attribute name"].is_string())
    {
        messagesHistory.emplace_back(Message("Name must be string type!"));
        return false;
    }

    setName(json["Attribute name"].get<std::string>());
    return setLimit(json["Minimum"].get<TypeT>(), json["Maximum"].get<TypeT>(), messagesHistory);
}

template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
void IntegerNumberBaseClass<TypeT, ImGuiDataTypeT, TypeEnumT>::drawInputForChangingLimits(std::vector<Message>& messagesHistory)
{
    static auto tmpMin = 0;
    static auto tmpMax = 0;
    static bool minChange = false;
    static bool maxChange = true;
    if (ImGui::InputScalar("Minimum", ImGuiDataTypeT, &tmpMin, nullptr, nullptr, nullptr, ImGuiInputTextFlags_CharsDecimal))
    {
        minChange = true;
    }
    if (ImGui::InputScalar("Maximum", ImGuiDataTypeT, &tmpMax, nullptr, nullptr, nullptr, ImGuiInputTextFlags_CharsDecimal))
    {
        maxChange = true;
    }

    if (minChange && maxChange)
    {
        setLimit(tmpMin, tmpMax, messagesHistory);
        minChange = false;
        maxChange = false;
    }
}

//------------------------------------------------------

// DECIMAL NUMBERS -----------------------------------------------------
template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool DecimalNumberBaseClass<TypeT, ImGuiDataTypeT, TypeEnumT>::setLimit(TypeT minimum, TypeT maximum, std::vector<Message>& messagesHistory)
{

    if (minimum < maximum)
    {
        min_ = minimum;
        max_ = maximum;
        return true;
    }
    messagesHistory.emplace_back(Message("Minimum must be lower value than maximum!"));
    return false;
}

template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool DecimalNumberBaseClass<TypeT, ImGuiDataTypeT, TypeEnumT>::jsonParse(nlohmann::ordered_json &json, std::vector<Message>& messagesHistory)
{
    if (json.find("Minimum") == json.end() || json.find("Maximum") == json.end() || json.find("Attribute name") == json.end())
    {
        messagesHistory.emplace_back(Message("Incorrect json format!"));
        return false;
    }

    if (!json["Attribute name"].is_string())
    {
        messagesHistory.emplace_back(Message("Name must be string type!"));
        return false;
    }

    if ((!json["Minimum"].is_number_float() && json["Minimum"].type() != TypeEnumT) || (!json["Minimum"].is_number_float() && json["Maximum"].type() != TypeEnumT))
    {
        messagesHistory.emplace_back(Message("Bounds must be number value!"));
        return false;
    }

    setName(json["Attribute name"].get<std::string>());
    return setLimit(json["Minimum"].get<TypeT>(), json["Maximum"].get<TypeT>(), messagesHistory);
}

template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
void DecimalNumberBaseClass<TypeT, ImGuiDataTypeT, TypeEnumT>::drawInputForChangingLimits(std::vector<Message>& messagesHistory)
{
    static auto tmpMin = 0;
    static auto tmpMax = 0;
    static bool minChange = false;
    static bool maxChange = true;
    if (ImGui::InputScalar("Minimum", ImGuiDataTypeT, &tmpMin, nullptr, nullptr, nullptr, ImGuiInputTextFlags_CharsDecimal))
    {
        minChange = true;
    }
    if (ImGui::InputScalar("Maximum", ImGuiDataTypeT, &tmpMax, nullptr, nullptr, nullptr, ImGuiInputTextFlags_CharsDecimal))
    {
        maxChange = true;
    }

    if (minChange && maxChange)
    {
        setLimit(tmpMin, tmpMax, messagesHistory);
        minChange = false;
        maxChange = false;
    }
}

//-------------------------------------------------------------


//BOOL --------------------------------------------------------

bool AttributeDescription_bool::jsonParse(nlohmann::ordered_json &json, std::vector<Message>& messagesHistory) {
    if (json.find("Attribute name") == json.end())
    {
        messagesHistory.emplace_back(Message("Incorrect json format!"));
        return false;
    }

    if (!json["Attribute name"].is_string())
    {
        messagesHistory.emplace_back(Message("Name must be string type!"));
        return false;
    }

    setName(json["Attribute name"].get<std::string>());
    return true;
}














std::unique_ptr<AttributeDescription> AttributeDescription_int::clone() { return std::make_unique<AttributeDescription_int>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescription_double::clone() { return std::make_unique<AttributeDescription_double>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescription_float::clone() { return std::make_unique<AttributeDescription_float>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescription_long::clone() { return std::make_unique<AttributeDescription_long>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescription_uint::clone() { return std::make_unique<AttributeDescription_uint>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescription_char::clone() { return std::make_unique<AttributeDescription_char>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescription_bool::clone() { return std::make_unique<AttributeDescription_bool>(*this); }
