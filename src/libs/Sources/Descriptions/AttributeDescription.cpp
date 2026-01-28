#include "AttributeDescription.h"
#include "AttributeDescriptionsComplete.h"

// INT
std::unique_ptr<AttributeDescription> AttributeDescription_int::clone() { return std::make_unique<AttributeDescription_int>(*this); }
void AttributeDescription_int::setLimit(int minimum, int maximum)
{
    if (minimum < maximum)
    {
        min_ = minimum;
        max_ = maximum;
    }
}

bool AttributeDescription_int::jsonParse(nlohmann::ordered_json &json, std::string &outputMessage)
{
    if (!json["Minimum"].is_number_integer() || !json["Maximum"].is_number_integer())
    {
        outputMessage = "Bounds must be integer value!";
        return false;
    }

    if(!json["Attribute name"].is_string()) {
        outputMessage = "Name must be string type!";
        return false;
    }

    setName(json["Attribute name"].get<std::string>());
    setLimit(json["Minimum"].get<int>(), json["Maximum"].get<int>());
    return true;
}

//---------------------------------------------------------------------------------------------------------



// DOUBLE
std::unique_ptr<AttributeDescription> AttributeDescription_double::clone() { return std::make_unique<AttributeDescription_double>(*this); }
void AttributeDescription_double::setLimit(double minimum, double maximum) {
            if (minimum < maximum) {
                min_ = minimum;
                max_ = maximum;
            }
        }

bool AttributeDescription_double::jsonParse(nlohmann::ordered_json &json, std::string &outputMessage)
{
    if (!json["Minimum"].is_number_float() || !json["Maximum"].is_number_float())
    {
        outputMessage = "Bounds must be double value!";
        return false;
    }

    if(!json["Attribute name"].is_string()) {
        outputMessage = "Name must be string type!";
        return false;
    }

    setName(json["Attribute name"].get<std::string>());
    setLimit(json["Minimum"].get<double>(), json["Maximum"].get<double>());
    return true;
}

//---------------------------------------------------------------------------------------------------------



// FLOAT
std::unique_ptr<AttributeDescription> AttributeDescription_float::clone() { return std::make_unique<AttributeDescription_float>(*this); }
void AttributeDescription_float::setLimit(float minimum, float maximum) {
            if (minimum < maximum) {
                min_ = minimum;
                max_ = maximum;
            }
        }

bool AttributeDescription_float::jsonParse(nlohmann::ordered_json &json, std::string &outputMessage)
{
    if (!json["Minimum"].is_number_float() || !json["Maximum"].is_number_float())
    {
        outputMessage = "Bounds must be float value!";
        return false;
    }

    if(!json["Attribute name"].is_string()) {
        outputMessage = "Name must be string type!";
        return false;
    }

    setName(json["Attribute name"].get<std::string>());
    setLimit(json["Minimum"].get<float>(), json["Maximum"].get<float>());
    return true;
}

//---------------------------------------------------------------------------------------------------------



