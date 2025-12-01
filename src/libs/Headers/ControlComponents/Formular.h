#pragma once
#include "Attributes.h"
#include "NumericInput.h"
#include "CharacterInput.h"
#include "json.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <functional>
#include <variant>
#include <fstream>

using AttributeTypeVariant = std::variant<int,double,char>;


class Factory {
    public:
    virtual std::unique_ptr<ControlComponent> createEdit(std::string type) = 0;
};



using IntEditUptr = std::unique_ptr<ControlComponent>;

class IntEditFactory : public Factory
{
private:
    static IntEditFactory* instance;
private:
    std::map<EditTypeInt, IntEditUptr> prototypes_;
    std::map<std::string,EditTypeInt> converter {{"SLIDER",EditTypeInt::SLIDER},{"VSLIDER",EditTypeInt::VSLIDER},{"DRAG",EditTypeInt::DRAG}};

private:
    IntEditFactory();

    template <typename EditTypeIntT>
    void registerPrototype();
public:
    static IntEditFactory* getInstance();

    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeInt edit = EditTypeInt::SLIDER;
        if (converter.contains(editType)) {
            edit = converter[editType];
        }
        return prototypes_[edit]->clone();
    }

};

//--------------------------------------------------

using DoubleEditUptr = std::unique_ptr<ControlComponentDouble>;
class DoubleEditFactory : public Factory
{
private:
    std::map<EditTypeDouble, DoubleEditUptr> prototypes_;
    std::map<std::string,EditTypeDouble> converter {{"SLIDER",EditTypeDouble::SLIDER},{"VSLIDER",EditTypeDouble::VSLIDER},{"DRAG",EditTypeDouble::DRAG}};
public:
    std::unique_ptr<ControlComponent> createEdit(std::string editType)
    {
        EditTypeDouble edit = EditTypeDouble::SLIDER;
        if (converter.contains(editType)) {
            edit = converter[editType];
        }
        return prototypes_[edit]->clone();
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
    std::unique_ptr<ControlComponent> createEdit(std::string type)
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
    bool openedWindow;
    Attributes *attributes_;
    std::vector<std::unique_ptr<ControlComponent>> components_;
    std::map<AttributeType, Factory*> decision_;
    std::map<std::string,AttributeType> converter_ =  {{"INT", AttributeType::INT},{"DOUBLE", AttributeType::DOUBLE},{"CHAR",AttributeType::CHAR}};
    std::map<std::string,std::function<bool(nlohmann::json&)>> decision2_ =  { 
        {"INT", [&](nlohmann::json& tempJson) {
            for (auto& it : tempJson) {
                if (!this->addAttribute(it["Attribute name"].get<std::string>(),AttributeType::INT,it["Minimum"].get<int>(),it["Maximum"].get<int>(),it["Value"].get<int>())) {
                    return false;
                }
            }
            return true;
        }
    }
    };

public:
    Formular(Attributes *attributes);

    void addAttribute(std::string name, 
                     std::string editType, 
                     AttributeType type, 
                     AttributeTypeVariant min, 
                     AttributeTypeVariant max);
    
    bool addAttribute(std::string name,  
                     AttributeType type, 
                     AttributeTypeVariant min, 
                     AttributeTypeVariant max,
                     AttributeTypeVariant value);

    bool addControlType(std::string atributeName, std::string edtitType);
    
    void draw();
    inline int getNumberOfAttributes() { return attributes_->getSize(); }
    inline int getNumberOfComponents() { return components_.size();}
    int readFileDescriptions(const char *path);
    bool readFileControlTypes(const char *path);
    void saveToFile();
    bool sameName(std::string name);
    bool showWarning();
    bool isEmpty() { return components_.empty(); };
    

// ==========



};
