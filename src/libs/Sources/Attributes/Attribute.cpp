#include "Attribute.h"

// INT -----------------------------------------------------------------------------------------

bool AttributeInt::saveToJson(nlohmann::ordered_json &json, std::string &outputMessage)  {
    json.push_back(nlohmann::ordered_json::object_t::value_type("Minimum",getMin()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Maximum",getMaximum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Value",getValue()));
    return true;
} 

































// ---------------------------------------------------------------------------------------------------

// DOUBLE -----------------------------------------------------------------------------------------

bool AttributeDouble::saveToJson(nlohmann::ordered_json &json, std::string &outputMessage)  {
    json.push_back(nlohmann::ordered_json::object_t::value_type("Minimum",getMin()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Maximum",getMaximum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Value",getValue()));
    return true;
} 

// ---------------------------------------------------------------------------------------------------

// FLOAT -----------------------------------------------------------------------------------------

bool AttributeFloat::saveToJson(nlohmann::ordered_json &json, std::string &outputMessage)  {
    json.push_back(nlohmann::ordered_json::object_t::value_type("Minimum",getMin()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Maximum",getMaximum()));
    json.push_back(nlohmann::ordered_json::object_t::value_type("Value",getValue()));
    return true;
} 
