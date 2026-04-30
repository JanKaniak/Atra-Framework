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
    bool addControlTypeByNames(std::string_view path, std::string editType);
    bool addDefaultControlType(std::string_view path);
    bool replaceControlType(Attribute *attribute, std::string editType);
    bool replaceControlType(std::string_view path, std::string editType);
    AttributeDescription* addDescription(std::string_view path,std::string_view attributeName, AttributeType type);
    AttributeDescription* addDescription(std::unique_ptr<AttributeDescription> attributeDescription);
    bool createAttributes();
    inline int getNumberOfAttributes() { return attributes_->getSize(); }
    Attribute* getAttribute(std::string_view path);
    const std::vector<Attribute*> getAttributes() const { return attributes_->getAttributes();}
    void deleteAll();
    bool createTemplateEntity(std::string_view name);
    bool addDescriptionToEntity(std::string_view entityName,std::string_view path, std::string_view descriptionName, AttributeType type);
    AttributeDescription *getAttributeDescriptionFromEntity(std::string_view entityName, std::string_view path, std::string_view name);
    bool deleteDescriptionFromEntity(std::string_view templateEntityName, std::string_view path, std::string_view name);
    bool deleteTemplateEntity(std::string_view name);
    bool generateAttributesFromEntity(std::string_view name) {
        chosenAttributesDescription_ = templateDescriptions_->getContainer(name);
        attributeDescs_->addDescriptions(chosenAttributesDescription_, &messageHistory_);
        return attributes_->createAttributes(messageHistory_);
    }
    bool deleteAttribute(std::string_view path) { 
        if (path.empty()) {
            messageHistory_.emplace_back("Path cannot be empty!");
            return false;
        }
        return attributes_->deleteAttributeByPath(path.data());
    }
private:
    void showSettings();
    void showLogger();
    void editAttribute(Attribute *attribute);
    void deleteAttribute(Attribute *attribute);
    void showAddDescriptionWindow(AttributesDescriptionsContainer* attributeDesc, bool isCreatingAttributesOutsideClusterAllowed);
    void showModifyControlTypesWindow();
    void showCreateTemplateAttribute();
    void showCreateAttributesFromTemplates();
    int readFileDescriptions();
    int readFileControlTypes();
    void saveToFile();
    bool showWarning(std::string message);
    void showWindowManageTemplates();
    bool addLogMessage(std::string message);
    bool clearLogger();
    
};