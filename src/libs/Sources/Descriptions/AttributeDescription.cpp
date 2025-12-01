#include "AttributeDescription.h"


//Class AttributeDescription_int
std::unique_ptr<AttributeDescription> AttributeDescription_int::clone() { return std::make_unique<AttributeDescription_int>(*this); }
void AttributeDescription_int::setLimit(AttributeTypeVariant minimum, AttributeTypeVariant maximum) { 
            if (std::get<int>(minimum) < std::get<int>(maximum)) {
                min_ = std::get<int>(minimum);
                max_ = std::get<int>(maximum);
            }
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