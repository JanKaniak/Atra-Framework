#include "Attribute.h"

// INT -----------------------------------------------------------------------------------------

bool AttributeInt::saveToJson(nlohmann::json &json, std::string &outputMessage)  {
    json.push_back(nlohmann::json::object_t::value_type("Minimum",getMin()));
    json.push_back(nlohmann::json::object_t::value_type("Maximum",getMaximum()));
    json.push_back(nlohmann::json::object_t::value_type("Value",getValue()));
    return true;
} 

































// ---------------------------------------------------------------------------------------------------

// DOUBLE -----------------------------------------------------------------------------------------

bool AttributeDouble::saveToJson(nlohmann::json &json, std::string &outputMessage)  {
    json.push_back(nlohmann::json::object_t::value_type("Minimum",getMin()));
    json.push_back(nlohmann::json::object_t::value_type("Maximum",getMaximum()));
    json.push_back(nlohmann::json::object_t::value_type("Value",getValue()));
    return true;
} 
