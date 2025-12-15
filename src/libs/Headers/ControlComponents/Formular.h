#pragma once
#include "Attributes.h"
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
    Config config;


private:
    bool mainWindows = true;
    bool openedWindow = false;
    bool selectedMenu = false;
    bool editWindow = false;
    int numberOfLoadedAtributes = INT_MAX;
    int numberOfLoadedControls = INT_MAX;
    int selected = 0;
    char buffer[40] = "Atribut";
    char bufferMin[40] = "0";
    char bufferMax[40] = "50";
    bool nameExists = false;
    int typeChoise = 0;
    int controlChoice = 0;
    std::string infoMessage = "";
    bool decision = false;
    const char *numericTypeChoice[3] = {"Int", "Double", "Float"};
    const char *textTypeChoice[2] = {"Char", "String"};
    const char *controls[3] = {"Slider", "VS_Slider", "Drag"};
    AttributeType numAttributeType[2] = {AttributeType::INT, AttributeType::DOUBLE};
    AttributeType textAttributeType[1] = {AttributeType::CHAR};

private:
    std::unique_ptr<Attributes> attributes_;
    std::vector<std::unique_ptr<ControlComponent>> components_;
    std::map<AttributeType,std::string> enumToString =  {{AttributeType::INT,"INT"},{AttributeType::DOUBLE,"DOUBLE"},{AttributeType::CHAR,"CHAR"}};
    std::map<std::string,AttributeType> stringToEnum =  {{"INT",AttributeType::INT},{"DOUBLE",AttributeType::DOUBLE},{"CHAR",AttributeType::CHAR}};
    
private:
    /*std::map<std::string,std::function<bool(nlohmann::json&,std::string agentName, std::string &outputMessage)>> decision2_ =  { 
        {"INT", [&](nlohmann::json& tempJson, std::string agentName,std::string &outputMessage) {
            for (auto& it : tempJson) {
                if (!it["Minimum"].is_number_integer() || !it["Maximum"].is_number_integer()) {
                    outputMessage = "Bounds must be integer value!";
                    return false;
                }
                if (attributes_->contains(it["Attribute name"].get<std::string>(),agentName)) {
                    return false;
                }
                this->addAttribute(it["Attribute name"].get<std::string>(),AttributeType::INT,agentName,it["Minimum"].get<int>(),it["Maximum"].get<int>());
            }
            return true;
        }
    }
    };*/

    std::map<AttributeType, std::function<bool(nlohmann::json&, Attribute*, std::string&)>>  saveAdditionalInfoToFile_ {
        {AttributeType::INT, [&](nlohmann::json &json, Attribute* attribute, std::string &outputMessage) {
            if(!dynamic_cast<AttributeInt*>(attribute)) {
                outputMessage = "Object of attribute does not equal it's type!";
                return false;
            }
            AttributeInt* attributeint = dynamic_cast<AttributeInt*>(attribute);
            
            return true;
        }

        }
    };

public:
    Formular();

    void addAttribute(std::string name, 
                     std::string editType, 
                     AttributeType type, 
                     AttributeTypeVariant min, 
                     AttributeTypeVariant max);
    
    void addAttribute(std::string attributeName,  
                     AttributeType type,
                     std::string agentName, 
                     AttributeTypeVariant min, 
                     AttributeTypeVariant max);

    bool addControlType(std::string atributeName, std::string agentName,std::string edtitType, std::string &outputMessage);
    bool addControlType(Attribute *attribute, std::string &outputMessage);
    void showControls();
    void showAttributes();
    void deleteAttribute(Attribute* attribute, std::string &outputMessage);
    void showEditWindow();
    void draw();
    inline int getNumberOfAttributes() { return attributes_->getSize(); }
    inline int getNumberOfComponents() { return components_.size();}
    int readFileDescriptions(const char *path,std::string &outputMessage);
    int readFileControlTypes(const char *path,std::string &outputMessage);
    bool saveToFile(std::string &outputMessage);
    bool sameName(std::string name);
    bool showWarning(std::string message);
    bool isEmpty() { return components_.empty(); };
    

// ==========



};