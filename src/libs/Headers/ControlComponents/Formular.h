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

class Factory {
    public:
    virtual ControlComponent* createEdit(int type) = 0;
};



using IntEditUptr = std::unique_ptr<ControlComponent>;

class IntEditFactory : public Factory
{
private:
    static IntEditFactory* instance;
private:
    std::map<EditTypeInt, IntEditUptr> prototypes_;

private:
    IntEditFactory();

    template <typename EditTypeIntT>
    void registerPrototype();
public:
    static IntEditFactory* getInstance();

    ControlComponent *createEdit(int type)
    {
        return prototypes_[static_cast<EditTypeInt>(type)]->clone();
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

    std::map<AtributeType, Factory*> decision_;

public:
    Formular(Values *values);

    void addAtribute(int editType, std::string name, AtributeType type, double min, double max);
    void addAtribute(int editType, std::string name, AtributeType type, double min, double max,std::string value);
    bool sameName(std::string name);

    void draw();

    inline int getNumberOfAtributes() { return values_->getSize(); }

    void readFile(const char *path);

    void saveToFile();

// ==========



};
