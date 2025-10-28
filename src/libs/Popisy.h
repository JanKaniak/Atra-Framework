#include "PopisAtributu.h"
#include <vector>
class Popisy {
    private:
        std::vector<PopisAtributu*> popisy;
    public:
        Popisy(){};
        void pridajPopis(PopisAtributu* popis) {
            popisy.push_back(popis);
        }
        PopisAtributu* getPopis(std::string meno, TypAtributu typ) {
            for (auto popis : popisy) {
                if (popis->getMeno().compare(meno) == 0 && popis->getTyp() == typ) {
                    return popis;
                }
            }
            return nullptr;
        }

        PopisAtributu* getPosledny() {
            return popisy.at(popisy.size() - 1);
        }

        int getPocetPopisov() { return popisy.size();}

};