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

class Formular
{
    

private:
    

private:
    bool openedWindow_;
    bool addDescriptionWindow_;
    bool useDefaultControls_;
    bool overWriteExistingControls_;
    bool saveWindow_;
    
private:
    ImVec2 showAttributesWindowSize_;

private:
    int numberOfLoadedAtributes_;
    int numberOfLoadedControls_;

private:
    std::unique_ptr<AttributesDescriptionsContainer> attributeDescs_;
    std::unique_ptr<AttributesContainer> attributes_;
    std::unique_ptr<ControlComponentsContainer> components_;
    std::vector<Message> messageHistory_;
    TemplateAttributesDescriptionContainer* templateDescriptions_;
    AttributesDescriptionsContainer* chosenAttributesDescription_;

public:
    Formular();
    void showControls();
    void showAttributes();
    bool loadDescriptions(nlohmann::ordered_json json);
    int loadControlTypes(nlohmann::json json);
    nlohmann::ordered_json saveOutput();
    bool addControlTypeByNames(std::string atributeName, std::string edtitType);
    bool addDefaultControlType(Attribute *attribute);
    bool ReplaceControlType(Attribute *attribute);
    bool replaceControlType(Attribute *attribute, std::string controlType);
    AttributeDescription* addDescription(std::string attributeName, AttributeType type);
    AttributeDescription* addDescription(std::unique_ptr<AttributeDescription> attributeDescription);
    bool createAttributes();
private:
    void showSettings();
    void showLogger();
    void editAttribute(Attribute *attribute);
    void deleteAttribute(Attribute *attribute);
    void showAddDescriptionWindow(AttributesDescriptionsContainer* attributeDesc, bool isCreatingAttributesOutsideClusterAllowed);
    void showModifyControlTypesWindow();
    void showCreateTemplateAttribute();
    void showCreateAttributesFromTemplates();
    inline int getNumberOfAttributes() { return attributes_->getSize(); }
    int readFileDescriptions();
    int readFileControlTypes();
    void saveToFile();
    bool showWarning(std::string message);
    void showWindowManageTemplates();
    bool addLogMessage(std::string message);
    bool clearLogger();
    
};