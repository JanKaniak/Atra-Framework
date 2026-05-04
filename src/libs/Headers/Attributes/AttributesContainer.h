#pragma once
#include "ImplementedAttribute.h"
#include "AttributesDescriptionsContainer.h"
#include <vector>
#include <memory>
#include <map>

//------------------------------------------

/// Container managing attribute instances and their associated descriptions.
///
/// Uses `AttributesDescriptionsContainer` to maintain metadata and supports
/// attribute creation, lookup, deletion, and nested cluster traversal.
class AttributesContainer
{
private:
    AttributesDescriptionsContainer *attributeDescs_;
    std::vector<std::unique_ptr<Attribute>> attributes_;
    AttributeFactory *attributeFactory_;

public:
    /// Default constructor creates an empty container.
    AttributesContainer();

    /// Construct the container with an existing description store.
    AttributesContainer(AttributesDescriptionsContainer *attributeDescs);

    ~AttributesContainer();

    /// Add a description for a new attribute using JSON input.
    bool addDescription(AttributeType type, nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) { return attributeDescs_->addDescription(type, json, &messagesHistory); }

    /// Add a description with a custom attribute name.
    bool addDescription(std::string attributeName, AttributeType type, std::vector<Message> &messagesHistory) { return attributeDescs_->addDescription(attributeName, type, &messagesHistory); }

    /// Create attribute instances for all registered descriptions.
    bool createAttributes(std::vector<Message> &messagesHistory);

    /// Return the last attribute added to the container.
    inline Attribute *getLast() { return attributes_.at(attributes_.size() - 1).get(); }

    /// Return the number of attribute instances.
    inline int getSize() { return attributes_.size(); }

    /// Return the number of registered descriptions.
    inline int getNumberOfDescriptions() { return attributeDescs_->getSize(); }

    /// Return the attribute at the given index.
    inline Attribute *giveAttribute(int rank) { return attributes_.at(rank).get(); }

    /// Find an attribute by its name.
    Attribute *giveAttributeByName(std::string name);

    /// Determine whether an attribute with the given name exists.
    bool contains(std::string attributeName);

    /// Delete a specific attribute and its description entry.
    bool deleteAttribute(Attribute *attribute);
    /// Delete an attribute by its name and remove the matching description.
    bool deleteAttribute(std::string_view name);

    /// Delete an attribute referenced by a hierarchical path through clusters.
    bool deleteAttributeByPath(std::string path);

    /// Reverse the order of stored attributes.
    void reverseOrder() { std::reverse(attributes_.begin(), attributes_.end()); }

    /// Return the types of registered descriptions.
    inline std::vector<AttributeTypeC> getRegisteredDescriptionsTypes() { return attributeDescs_->getRegisteredDescriptionsTypes(); }

    /// Find the index of an attribute by name.
    int getPosition(std::string attributeName);

    /// Retrieve the description object for a stored attribute.
    AttributeDescription *getDescription(int rank) { return attributeDescs_->getDescription(rank); }

    /// Remove the most recently added description.
    bool deleteLastDescription(std::vector<Message> &messagesHistory) { return attributeDescs_->deleteLastDescription(&messagesHistory); }

    /// Replace the underlying description container used by this attribute container.
    void changeDescriptionContainer(AttributesDescriptionsContainer *descs) { attributeDescs_ = descs; }

    /// Assign control components for each managed attribute.
    void setControlTypes(ControlComponentsContainer *components, std::vector<Message> &messagehistory);

    /// Check whether a description exists with the given name.
    bool existDescription(std::string_view name) { return attributeDescs_->existsDescription(name); }

    /// Collect descriptions that match a specific attribute type.
    void findDescriptionsByType(std::vector<AttributeDescription *> &vector, AttributeType type)
    {
        attributeDescs_->findDescriptionsByType(vector, type);
    }

    /// Remove all attributes from this container.
    void deleteAllAttributes(std::vector<Message> &messageHistory);

    /// Find an attribute by a dotted hierarchical path.
    Attribute *getAttributeByPath(std::string path);

    /// Return raw pointers to all current attributes.
    const std::vector<Attribute *> getAttributes() const;
};