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
    ControlComponentsFactoriesContainer *controlComponentsFactories_;

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
    void addLogMessage(std::string_view time, std::string_view message);
    bool addControlType(std::string atributeName, std::string edtitType);
    bool addControlType(Attribute *attribute);
    bool addOrReplaceControlTypeByVector(std::vector<std::string> controlTypesVector);
    bool replaceControlType(Attribute *attribute, std::string controlType);
    AttributeDescription* addDescription(std::string attributeName, AttributeType type);
    bool addDescription(std::string attributeName, AttributeType type, std::string * clusterAttributeName);
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
    
};