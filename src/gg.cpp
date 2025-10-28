#include "libs/Hodnoty.h"
#include "libs/AtributInt.h"
#include <iostream>

int main() {
    Popisy* popisy = new Popisy();
    Hodnoty hodnoty = Hodnoty(popisy);
    std::string meno = "Ahoj";
    TypAtributu typ = TypAtributu::Int;
    int hodnota = 50;
    hodnoty.pridajAtribut(new AtributInt(meno,hodnota,));
    std::cout << "atribut: " << meno << " ma hodnotu: " << hodnoty.dajInt(meno) << "\n";
    return 0;
    
}


