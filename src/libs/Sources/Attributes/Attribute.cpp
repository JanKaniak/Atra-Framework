#include "Attribute.h"

// INT -----------------------------------------------------------------------------------------

void AttributeInt::setValue(int value) {
        value_ = value;
    }

bool AttributeInt::saveToJson(nlohmann::json &json, std::string &outputMessage)  {
    json.push_back(nlohmann::json::object_t::value_type("Minimum",getMin()));
    json.push_back(nlohmann::json::object_t::value_type("Maximum",getMaximum()));
    json.push_back(nlohmann::json::object_t::value_type("Value",std::get<int>(getValue())));
    return true;
} 































// ---------------------------------------------------------------------------------------------------