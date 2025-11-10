#include "AtributeDescription.h"


//Class AtributeDescription_int
AtributeDescription_int* AtributeDescription_int::clone() { return new AtributeDescription_int(*this); }
void AtributeDescription_int::setLimit(double minimum, double maximum) { 
            if (minimum < maximum) {
                AtributeDescription_int::min_ = minimum;
                AtributeDescription_int::max_ = maximum;
            }
        }

//---------------------------------------------------------------------------------------------------------




//Class AtributeDescription_double
AtributeDescription_double* AtributeDescription_double::clone() { return new AtributeDescription_double(*this); }
void AtributeDescription_double::setLimit(double minimum, double maximum) { 
            if (minimum < maximum) {
                AtributeDescription_double::min_ = minimum;
                AtributeDescription_double::max_ = maximum;
            }
        }
        
//---------------------------------------------------------------------------------------------------------

AtributeDescription_char* AtributeDescription_char::clone() { return new AtributeDescription_char(*this);}

void AtributeDescription_char::setLimit(double minimum, double maximum) {
    if (minimum < maximum) {
                AtributeDescription_char::min_ = minimum;
            }
}