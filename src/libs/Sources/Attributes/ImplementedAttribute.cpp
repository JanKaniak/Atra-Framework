#include "ImplementedAttribute.h"

template <typename TypeT, typename AttributeDescriptionT>
bool IntegerNumberBaseAttributeClass<TypeT,AttributeDescriptionT>::saveToJson(nlohmann::ordered_json &json, std::vector<Message>& messagesHistory)  {
    json.push_back(nlohmann::ordered_json::object_t::value_type("Attribute name", getName()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Minimum",getMinimum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Maximum",getMaximum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Value",getValue()));
    return true;
} 

bool AttributeBool::saveToJson(nlohmann::ordered_json &json, std::vector<Message>& messagesHistory) {
    json.push_back(nlohmann::ordered_json::object_t::value_type("Attribute name", getName()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Value",getValue()));
    return true;
}