#pragma once
#include "json.hpp"
#include "Factory.h"
#include "AttributesContainer.h"
#include "ControlComponentsContainer.h"


#include <iostream>
#include <map>
#include <memory>
#include <functional>
#include <variant>
#include <fstream>
#include <format>

using AttributeTypeVariant = std::variant<int, double, char>;

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
    bool saveWindow_;

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
private:
    std::unique_ptr<AttributesContainer> attributes_;
    std::unique_ptr<ControlComponentsContainer> components_;
    std::vector<Message> messageHistory_;

public:
    Formular();
    void showControls();
    void showAttributes();
    bool loadDescriptions(nlohmann::ordered_json json);
    int loadControlTypes(nlohmann::json json);
    nlohmann::ordered_json saveOutput();
    void addLogMessage(std::string_view time, std::string_view message);

private:
    bool addControlType(std::string atributeName, std::string edtitType);
    bool addControlType(Attribute *attribute);
    bool addOrReplaceControlTypeByVector(std::vector<std::string> controlTypesVector);
    bool replaceControlType(Attribute *attribute, std::string controlType);
    void showSettings();
    void showLogger();
    void editAttribute(Attribute *attribute);
    void deleteAttribute(Attribute *attribute);
    void showAddDescriptionWindow();
    void showModifyControlTypesWindow();
    void draw();
    inline int getNumberOfAttributes() { return attributes_->getSize(); }
    int readFileDescriptions();
    int readFileControlTypes();
    void saveToFile();
    bool showWarning(std::string message);
    
    

    // ==========
};

// pridavanie description do zoznamu
// editor aj pre control type
// agent prec
// lepsie nazvy
// aktualizovat uml