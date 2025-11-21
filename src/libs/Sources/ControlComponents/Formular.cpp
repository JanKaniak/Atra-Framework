#include "Formular.h"
#include "json.hpp"




// Class Formular
Formular::Formular(Values *values)
{
    Formular::values_ = values;

     /*factoryDouble_ = std::make_unique<DoubleEditFactory>();
     factoryDouble_->registerPrototype<DoubleSlider>();
     factoryDouble_->registerPrototype<DoubleVSSlider>();
     factoryDouble_->registerPrototype<DoubleDrag>();

     factoryChar_ = std::make_unique<CharEditFactory>();
     factoryChar_->registerPrototype<CharInput>();*/
    //      IntEditFactory::getInstance()->createEdit()


    decision_.emplace(AtributeType::Int, IntEditFactory::getInstance());

}

void Formular::addAtribute(int editType, std::string name, AtributeType type, double min, double max)
    {
        values_->addAtribute(name, type, min, max);
        auto controller = decision_[type]->createEdit(editType);
        controller->setAtribute(values_->getLast());
        components_.push_back(controller);
    }

void Formular::addAtribute(int editType,std::string name, AtributeType type, double min, double max, std::string value) {
    values_->addAtribute(name,type,min,max);
    values_->setValueOfLast(type,value);
    auto controller = decision_[type]->createEdit(editType);
    controller->setAtribute(values_->getLast());
    components_.push_back(controller);
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
    /*std::ifstream file(path);
    nlohmann::json jsonFile = nlohmann::json::parse(file);
    file.close();

    for (auto it : jsonFile)
    {
        this->addAtribute(0,it.at("Atribute name").get<std::string>(),static_cast<AtributeType>(it.at("Atribute type").get<int>()),it.at("Minimum").get<std::string>(),it.at("Maximum").get<std::string>(),it.at("Value").get<std::string>());
    }*/
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

IntEditFactory* IntEditFactory::instance = nullptr;

IntEditFactory::IntEditFactory()
{
    this->registerPrototype<IntSlider>();   
    this->registerPrototype<IntVSSlider>();
    this->registerPrototype<IntDrag>();   
}

IntEditFactory* IntEditFactory::getInstance()
{
    if (instance == nullptr) {
        instance = new IntEditFactory();     
    }

    return instance;
}

template <typename EditTypeIntT>
inline void IntEditFactory::registerPrototype()
{
    prototypes_[EditTypeIntT::type_] = std::move(std::make_unique<EditTypeIntT>());   
}
