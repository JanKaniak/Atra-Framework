#pragma once
#include "NumericInput.h"
#include "CharacterInput.h"
#include "json.hpp"
#include "Factory.h"

#include <iostream>
#include <map>
#include <memory>
#include <functional>
#include <variant>
#include <fstream>
#include <format>

using AttributeTypeVariant = std::variant<int,double,char>;








class Formular
{
private:
    Config *config;


private:
    bool mainWindows = true;
    bool openedWindow = false;
    bool selectedMenu = false;
    bool addDescriptionWindow = false;
    bool modifyControlTypesWindow = false;
    bool useDefaultControls = true;
    bool overWriteExistingControls = false;
    bool nameExists = false;
    bool drawed = false;
    bool decision = false;
    bool showSettingWindow_;

private:
    ImVec2 showAttributesWindowSize_;

private:
    
    int numberOfLoadedAtributes = INT_MAX;
    int numberOfLoadedControls = INT_MAX;

private:
    char bufferMin[40] = "0";
    char bufferMax[40] = "50";
    std::filesystem::path descriptionsPath_;
    std::filesystem::path controlTypesPath_;
    
private:
    std::string infoMessage = "";
   
private:
    AttributeType numAttributeType[2] = {AttributeType::INT, AttributeType::DOUBLE};
    AttributeType textAttributeType[1] = {AttributeType::CHAR};
    Attribute *chosenAttribute;


private:
    std::unique_ptr<Attributes> attributes_;
    std::vector<std::unique_ptr<ControlComponent>> components_;
    //std::map<AttributeType,std::string> enumToString =  {{AttributeType::INT,"INT"},{AttributeType::DOUBLE,"DOUBLE"},{AttributeType::FLOAT,"FLOAT"}};
    std::map<std::string,AttributeType> stringToEnum =  {{"INT",AttributeType::INT},{"DOUBLE",AttributeType::DOUBLE},{"FLOAT",AttributeType::FLOAT}};
    

public:
    Formular();
    bool addControlType(std::string atributeName, std::string edtitType, std::string &outputMessage);
    bool addControlType(Attribute *attribute, std::string &outputMessage);
    bool addOrReplaceControlTypeByVector(std::vector<std::string> controlTypesVector, std::string &outputMessage);
    bool replaceControlType(Attribute *attribute, std::string controlType ,std::string &outputMessage);
    void showControls();
    void showSettings();
    void showLogger();
    void showAttributes();
    void editAttribute(Attribute* attribute, std::string &outputMessage);
    void deleteAttribute(Attribute* attribute, std::string &outputMessage);
    void showAddDescriptionWindow();
    void showModifyControlTypesWindow();
    void draw();
    inline int getNumberOfAttributes() { return attributes_->getSize(); }
    inline int getNumberOfComponents() { return components_.size();}
    int readFileDescriptions(std::filesystem::path path,std::string &outputMessage);
    int readFileControlTypes(std::filesystem::path path,std::string &outputMessage);
    bool saveToFile(std::string &outputMessage);
    bool sameName(std::string name);
    bool showWarning(std::string message);
    bool isEmpty() { return components_.empty(); };
    bool existControlType(std::string attributeName);
    std::string getControlTypeByAttributeName(std::string attributeName);
    int positionOfComponentByAttributeName(std::string attributeName);
    

// ==========



};




//pridavanie description do zoznamu
//editor aj pre control type
//agent prec
//lepsie nazvy
//aktualizovat uml