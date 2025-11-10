#include "Formular.h"
#include "json.hpp"




// Class Formular
Formular::Formular(Values *values)
{
    Formular::values_ = values;

     factoryInt_ = std::make_unique<IntEditFactory>();
     factoryInt_->registerPrototype<IntSlider>();
     factoryInt_->registerPrototype<IntVSSlider>();
     factoryInt_->registerPrototype<IntDrag>();

     factoryDouble_ = std::make_unique<DoubleEditFactory>();
     factoryDouble_->registerPrototype<DoubleSlider>();
     factoryDouble_->registerPrototype<DoubleVSSlider>();
     factoryDouble_->registerPrototype<DoubleDrag>();

     factoryChar_ = std::make_unique<CharEditFactory>();
     factoryChar_->registerPrototype<CharInput>();

     decision_.emplace(AtributeType::Int, std::move(factoryInt_));
     decision_.emplace(AtributeType::Double, std::move(factoryDouble_));
     decision_.emplace(AtributeType::Char, std::move(factoryChar_));

}

bool Formular::sameName(std::string name)
{
    for (ControlComponent *component : components_)
    {
        if (component->getName().compare(name) == 0)
        {
            return true;
        }
    }
    return false;
}

void Formular::draw()
{
    for (ControlComponent *component : components_)
    {
        component->draw();
    }
}

void Formular::readFile(const char *path)
{
    std::ifstream file(path);
    nlohmann::json jsonFile = nlohmann::json::parse(file);
    file.close();

    for (auto it : jsonFile)
    {
        // this->addAtributeWrapper(0,it.at("Meno Atributu").get<std::string>(),static_cast<AtributeFactory>(it.at("Typ Atributu").get<int>()),it.at("Minimum").get<std::string>(),it.at("Maximum").get<std::string>());
    }
}

void Formular::saveToFile()
{
    nlohmann::json jsonTemp;
    for (int i = 0; i < values_->getSize(); i++)
    {
        jsonTemp.push_back({{"Atribute name", values_->giveAtribute(i)->getName()}, {"Atribute type", static_cast<int>(values_->giveAtribute(i)->getType())}, {"Minimum", values_->giveAtribute(i)->getDescription()->getMin()}, {"Maximum", values_->giveAtribute(i)->getDescription()->getMax()}, {"Value",values_->giveAtribute(i)->getValue()}});
    }

    std::ofstream file("output.json");
    file << jsonTemp;
    file.close();
}