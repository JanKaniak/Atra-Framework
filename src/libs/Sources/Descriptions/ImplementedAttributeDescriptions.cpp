#include "AttributeDescription.h"
#include "ImplementedAttributeDescriptions.h"

#include <iostream>

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
    if (json.find("Minimum") == json.end() || json.find("Maximum") == json.end()) {
        outputMessage = "Incorrect json format!";
        return false;
    }
    if (!json["Minimum"].is_number_integer() || !json["Maximum"].is_number_integer())
    {
        std::cout << json["Minimum"] << "\n";
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

// LONG
std::unique_ptr<AttributeDescription> AttributeDescription_long::clone() { return std::make_unique<AttributeDescription_long>(*this); }
void AttributeDescription_long::setLimit(long minimum, long maximum) {
            if (minimum < maximum) {
                min_ = minimum;
                max_ = maximum;
            }
        }

bool AttributeDescription_long::jsonParse(nlohmann::ordered_json &json, std::string &outputMessage)
{
    if (!json["Minimum"].is_number_integer() || !json["Maximum"].is_number_integer())
    {
        outputMessage = "Bounds must be long value!";
        return false;
    }

    if(!json["Attribute name"].is_string()) {
        outputMessage = "Name must be string type!";
        return false;
    }

    setName(json["Attribute name"].get<std::string>());
    setLimit(json["Minimum"].get<long>(), json["Maximum"].get<long>());
    return true;
}

//---------------------------------------------------------------------------------------------------------

// U_INT
std::unique_ptr<AttributeDescription> AttributeDescription_u_int::clone() { return std::make_unique<AttributeDescription_u_int>(*this); }
void AttributeDescription_u_int::setLimit(uint minimum, uint maximum) {
            if (minimum < maximum) {
                min_ = minimum;
                max_ = maximum;
            }
        }

bool AttributeDescription_u_int::jsonParse(nlohmann::ordered_json &json, std::string &outputMessage)
{
    if (!json["Minimum"].is_number_unsigned() || !json["Maximum"].is_number_unsigned())
    {
        outputMessage = "Bounds must be unsigned int value!";
        return false;
    }

    if(!json["Attribute name"].is_string()) {
        outputMessage = "Name must be string type!";
        return false;
    }

    setName(json["Attribute name"].get<std::string>());
    setLimit(json["Minimum"].get<uint>(), json["Maximum"].get<uint>());
    return true;
}

//---------------------------------------------------------------------------------------------------------

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



