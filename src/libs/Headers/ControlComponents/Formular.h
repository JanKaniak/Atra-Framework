#pragma once
#include "Values.h"
#include "NumericInput.h"
#include "CharacterInput.h"

#include <iostream>
#include <map>
#include <memory>
#include <functional>
#include <variant>
#include <fstream>

using ControlComponentType = std::variant<ControlComponentInt,ControlComponentDouble,ControlComponentChar>;

class Factory {
    public:
    virtual ControlComponent* createEdit(int type) = 0;
};



using IntEditUptr = std::unique_ptr<ControlComponentInt>;

class IntEditFactory : public Factory
{
private:
    std::map<EditTypeInt, IntEditUptr> prototypes_;

public:
    ControlComponent *createEdit(int type)
    {
        return prototypes_[static_cast<EditTypeInt>(type)]->clone();
    }
    template <typename EditTypeIntT>
    void registerPrototype()
    {
        IntEditUptr prototype = std::make_unique<EditTypeIntT>();
        prototypes_[prototype->type_] = std::move(prototype);
    }
};

//--------------------------------------------------

using DoubleEditUptr = std::unique_ptr<ControlComponentDouble>;
class DoubleEditFactory : public Factory
{
private:
    std::map<EditTypeDouble, DoubleEditUptr> prototypes_;

public:
    ControlComponent *createEdit(int type)
    {
        return prototypes_[static_cast<EditTypeDouble>(type)]->clone();
    }

    template <typename EditTypeDoubleT>
    void registerPrototype()
    {
        DoubleEditUptr prototype = std::make_unique<EditTypeDoubleT>();
        prototypes_[prototype->type_] = std::move(prototype);
    }
};

//---------------------------------------------------

using CharEditUptr = std::unique_ptr<ControlComponentChar>;
class CharEditFactory : public Factory
{
private:
    CharEditUptr prototype;

public:
    ControlComponent *createEdit(int type)
    {
        return prototype->clone();
    }

    template <typename EditTypeCharT>
    void registerPrototype()
    {
        prototype = std::make_unique<EditTypeCharT>();
    }
};

//---------------------------------------------------

class Formular
{
private:
    Values *values_;
    std::vector<ControlComponent *> components_;
    std::unique_ptr<IntEditFactory> factoryInt_;
    std::unique_ptr<DoubleEditFactory> factoryDouble_;
    std::unique_ptr<CharEditFactory> factoryChar_;

    std::map<AtributeType, std::unique_ptr<Factory>> decision_;

public:
    Formular(Values *values);

    void addAtributeWrapper(int editType, std::string name, AtributeType type, double min, double max)
    {
        values_->addAtribute(name, type, min, max);
        auto controller = decision_[type]->createEdit(editType);
        controller->setAtribute(values_->getLast());
        components_.push_back(controller);
    }

    /*void addAtribute(EditTypeInt editType)
    {

        auto controller = factoryInt_.createEdit(editType);
        controller->setAtribute(values_->getLast());
        components_.push_back(controller);
    }

    void addAtribute(EditTypeDouble editType)
    {
        ControlComponentDouble *controller = factoryDouble_.createEdit(editType);
        controller->setAtribute(values_->getLast());
        components_.push_back(controller);
    }

    void addAtribute()
    {
        ControlComponentChar *controller = factoryChar_.createEdit();
        controller->setAtribute(values_->getLast());
        components_.push_back(controller);
    }
*/
    bool sameName(std::string name);

    void draw();

    inline int getNumberOfAtributes() { return values_->getSize(); }

    void readFile(const char *path);

    void saveToFile();
};
