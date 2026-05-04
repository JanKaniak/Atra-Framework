#pragma once
#include "json.hpp"
#include "DescriptionFactory.h"
#include "GlobalLastIdOfObject.h"

#include <vector>
#include <memory>
#include <map>
#include <iostream>

/// Container for attribute descriptions and nested cluster handling.
///
/// Manages ownership of descriptions, template registration, and search by path.
class AttributesDescriptionsContainer
{
private:
    std::vector<std::unique_ptr<AttributeDescription>> attributeDescs_;
    DescFactory *descFactory_;
    GlobalLastIdOfObject *lastId_;

public:
    AttributesDescriptionsContainer();

    /// Create a new attribute description from type and JSON, then append it.
    bool addDescription(AttributeType type, nlohmann::ordered_json &json, std::vector<Message> *messagesHistory);

    /// Add a description to a nested path using a dot-separated cluster path.
    bool addDescription(std::string path, AttributeType type, std::vector<Message> *messagesHistory);

    /// Create and add a description in a nested container by path and name.
    bool addDescriptionByPath(std::string path, std::string attributeName, AttributeType type, std::vector<Message> *messagesHistory);

    /// Append an existing attribute description instance.
    bool addDescription(std::unique_ptr<AttributeDescription> descriptionPtr);

    /// Merge descriptions from another container.
    bool addDescriptions(AttributesDescriptionsContainer *container, std::vector<Message> *messageHistory);

    /// Find a description by name in this container.
    AttributeDescription *getDescription(std::string name);

    inline AttributeDescription *getDescription(int i) { return (i >= 0 && i < attributeDescs_.size()) ? attributeDescs_.at(i).get() : nullptr; }
    inline int getSize() { return attributeDescs_.size(); }
    AttributeDescription *getLast();
    /// Remove a description by pointer.
    bool deleteDescription(AttributeDescription *description);

    /// Remove a description by name and reset ID counter if empty.
    bool deleteDescription(std::string_view name);

    /// Return all registered description types and categories from the factory.
    inline std::vector<AttributeTypeC> getRegisteredDescriptionsTypes() { return descFactory_->getRegisteredDescriptionsTypes(); }

    /// Remove the most recently added description.
    bool deleteLastDescription(std::vector<Message> *messagesHistory);

    /// Check whether a description with the given name exists.
    bool existsDescription(std::string_view name);

    /// Collect descriptions matching a specific attribute type.
    void findDescriptionsByType(std::vector<AttributeDescription *> &vector, AttributeType type);

    /// Find a nested container for a description by name and ID.
    AttributesDescriptionsContainer *findDescriptionContainer(std::string_view descriptionName, uint64_t descriptionId);

    ~AttributesDescriptionsContainer();

    /// Find a nested container by name and ID, including clusters.
    AttributesDescriptionsContainer *getDescriptionContainer(std::string_view descriptionName, uint64_t descriptionId);

    /// Remove all contained attribute descriptions.
    void deleteAllDescriptions(std::vector<Message> *messageHistory);
    /// Resolve a nested description by a dot-separated cluster path.
    ///
    /// If path is empty, returns a top-level description by name.
    AttributeDescription *getDescriptionByPath(std::string path, std::string descriptionName, std::vector<Message> &messagesHistory);

    /// Delete a nested description by dot-separated cluster path.
    bool deleteDescriptionByPath(std::string path, std::string name);
};

/// Wrapper for a named template of attribute descriptions.
class TemplateAttributesDescription
{
private:
    std::string name_;
    std::unique_ptr<AttributesDescriptionsContainer> templateDescriptionContainer_;

public:
    TemplateAttributesDescription()
    {
        templateDescriptionContainer_ = std::make_unique<AttributesDescriptionsContainer>();
    }
    TemplateAttributesDescription(std::string name) : name_(name), templateDescriptionContainer_(std::make_unique<AttributesDescriptionsContainer>()) {}

    std::string getName() { return name_; }
    AttributesDescriptionsContainer *getContainer() { return templateDescriptionContainer_.get(); }
};

/// Singleton container for named attribute description templates.
class TemplateAttributesDescriptionContainer
{
private:
    static TemplateAttributesDescriptionContainer *instance_;
    std::vector<std::unique_ptr<TemplateAttributesDescription>> templateDescriptions_;
    TemplateAttributesDescriptionContainer() = default;

public:
    static TemplateAttributesDescriptionContainer *getInstance();

    /// Add a new template description with a unique name.
    bool addTemplateDescription(std::string_view name, std::vector<Message> *messageHistory);

    /// Check whether a template with the given name already exists.
    bool templateExists(std::string_view name);

    /// Return the container for a named template.
    AttributesDescriptionsContainer *getContainer(std::string_view name);
    /// Return the number of registered templates.
    int getSize() { return templateDescriptions_.size(); }

    /// Return a template name by position.
    std::string getNameByPosition(int position);

    /// Return a template object by position.
    TemplateAttributesDescription *getTemplateByPosition(int position);

    /// Remove a template by pointer.
    bool removeTemplateDescription(TemplateAttributesDescription *templateDescription);

    /// Remove a template by name.
    bool removeTemplateDescription(std::string_view name);
};