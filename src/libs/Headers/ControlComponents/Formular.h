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

/// Manages attribute descriptions, runtime attributes, control components, and the ImGui formular UI.
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
    /// Initialize the formular, its description containers, attributes, and control components.
    Formular();
    /// Render the main UI for attribute and control management.
    void showControls();
    /// Render the active attribute control panel.
    void showAttributes();
    /// Load attribute descriptions from ordered JSON data.
    bool loadDescriptions(nlohmann::ordered_json json);
    /// Load control type assignments from JSON data.
    int loadControlTypes(nlohmann::json json);
    /// Serialize the current attributes and controls to ordered JSON.
    nlohmann::ordered_json saveOutput();
    /// Add a control by attribute path and edit control type name.
    bool addControlTypeByNames(std::string_view path, std::string editType);
    /// Add a default control type for the attribute at the given path.
    bool addDefaultControlType(std::string_view path);
    /// Replace the control type for a specific attribute pointer.
    bool replaceControlType(Attribute *attribute, std::string editType);
    /// Replace the control type for an attribute referenced by path.
    bool replaceControlType(std::string_view path, std::string editType);
    /// Add a new attribute description under the specified path.
    AttributeDescription* addDescription(std::string_view path,std::string_view attributeName, AttributeType type);
    /// Add an existing attribute description object to the description container.
    AttributeDescription* addDescription(std::unique_ptr<AttributeDescription> attributeDescription);
    /// Create runtime attributes from all registered descriptions.
    bool createAttributes();
    inline int getNumberOfAttributes() { return attributes_->getSize(); }
    /// Retrieve an attribute by path or name.
    Attribute* getAttribute(std::string_view path);
    /// Return all created runtime attributes.
    const std::vector<Attribute*> getAttributes() const { return attributes_->getAttributes();}
    /// Remove all descriptions, attributes, and control components.
    void deleteAll();
    /// Create a reusable template entity for grouped attribute descriptions.
    bool createTemplateEntity(std::string_view name);
    /// Add a description to a named template entity.
    bool addDescriptionToEntity(std::string_view entityName,std::string_view path, std::string_view descriptionName, AttributeType type);
    /// Retrieve a description from a template entity.
    AttributeDescription *getAttributeDescriptionFromEntity(std::string_view entityName, std::string_view path, std::string_view name);
    /// Delete a description from a template entity.
    bool deleteDescriptionFromEntity(std::string_view templateEntityName, std::string_view path, std::string_view name);
    /// Remove an existing template entity.
    bool deleteTemplateEntity(std::string_view name);
    /// Generate runtime attributes from the named template entity.
    bool generateAttributesFromEntity(std::string_view name) {
        chosenAttributesDescription_ = templateDescriptions_->getContainer(name);
        attributeDescs_->addDescriptions(chosenAttributesDescription_, &messageHistory_);
        return attributes_->createAttributes(messageHistory_);
    }
    /// Delete an attribute and its associated control component.
    bool deleteAttribute(std::string_view path) {
        if (path.empty()) {
            messageHistory_.emplace_back("Path cannot be empty!");
            return false;
        }
        Attribute *tmpAttribute = attributes_->getAttributeByPath(path.data()); 
        if (tmpAttribute == nullptr) {
            messageHistory_.emplace_back("Wrong name or path!");
            return false;
        }
        components_->deleteControlComponent(tmpAttribute);
        return attributes_->deleteAttribute(tmpAttribute);
    }
    /// Add a message to the internal logger.
    bool addLogMessage(std::string message);
    /// Clear the internal log history.
    bool clearLogger();
private:
    /// Render the settings panel for the formular.
    void showSettings();
    /// Render the log window showing history messages.
    void showLogger();
    /// Render the attribute edit panel for the selected attribute.
    void editAttribute(Attribute *attribute);
    /// Delete an attribute and its UI control by pointer.
    void deleteAttribute(Attribute *attribute);
    /// Display the popup for adding or editing attribute descriptions.
    void showAddDescriptionWindow(AttributesDescriptionsContainer* attributeDesc, bool isCreatingAttributesOutsideClusterAllowed);
    /// Display the popup to modify control types assigned to existing attributes.
    void showModifyControlTypesWindow();
    /// Display the UI for creating a new attribute template.
    void showCreateTemplateAttribute();
    /// Display the UI for generating attributes from existing templates.
    void showCreateAttributesFromTemplates();
    /// Open a file dialog and read attribute descriptions from JSON.
    int readFileDescriptions();
    /// Open a file dialog and read control type mappings from JSON.
    int readFileControlTypes();
    /// Save the current attributes to a JSON file.
    void saveToFile();
    /// Display an error warning window with a custom message.
    bool showWarning(std::string message);
    /// Show template management controls for editing and deleting templates.
    void showWindowManageTemplates();
    
    
};