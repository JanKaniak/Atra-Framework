#include "AttributeDescription.h"

// Class AttributeDescription_int
std::unique_ptr<AttributeDescription> AttributeDescription_int::clone() { return std::make_unique<AttributeDescription_int>(*this); }
void AttributeDescription_int::setLimit(AttributeTypeVariant minimum, AttributeTypeVariant maximum)
{
    if (std::get<int>(minimum) < std::get<int>(maximum))
    {
        min_ = std::get<int>(minimum);
        max_ = std::get<int>(maximum);
    }
}

bool AttributeDescription_int::jsonParse(nlohmann::json &json, std::string &outputMessage)
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

/*

//Class AtributeDescription_double
AtributeDescription_double* AtributeDescription_double::clone() { return new AtributeDescription_double(*this); }
void AtributeDescription_double::setLimit(AtributeTypeVariant minimum, AtributeTypeVariant maximum) {
            if (std::get<double>(minimum) < std::get<double>(maximum)) {
                min_ = std::get<double>(minimum);
                max_ = std::get<double>(maximum);
            }
        }

//---------------------------------------------------------------------------------------------------------

AtributeDescription_char* AtributeDescription_char::clone() { return new AtributeDescription_char(*this);}

void AtributeDescription_char::setLimit(AtributeTypeVariant minimum, AtributeTypeVariant maximum) {
    int tempMax = std::get<int>(maximum);
    int tempMin = std::get<int>(minimum);
    if ((tempMax >= 0 &&  tempMin <= 1) && (tempMin >= 0 && tempMin <= 1) && (tempMax >= tempMin)) {
                min_ = tempMin;
                max_ = tempMax;
            }
}


*/