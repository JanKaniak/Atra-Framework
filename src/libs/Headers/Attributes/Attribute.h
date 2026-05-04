#pragma once
#include "ImplementedAttributeDescriptions.h"

#include <string>
#include <limits.h>
#include <iostream>
#include <variant>
#include <stdexcept>
#include <memory>

class ControlComponentsFactoriesContainer;
class ControlComponentsContainer;

/// Abstract interface for an attribute instance.
///
/// Concrete attributes provide metadata, serialization, UI control options, and value updates.
class Attribute
{
public:
    /// Return the attribute name.
    virtual std::string getName() = 0;

    /// Return the attribute type enum.
    virtual AttributeType getType() = 0;

    /// Return the associated attribute description.
    virtual AttributeDescription *getDescription() = 0;

    /// Virtual destructor for derived attribute cleanup.
    virtual ~Attribute() = 0;

    /// Clone this attribute polymorphically.
    virtual std::unique_ptr<Attribute> clone() = 0;

    /// Set the description and collect any validation messages.
    virtual void setDescription(AttributeDescription *desc, std::vector<Message> &messagesHistory) = 0;

    /// Serialize the attribute into JSON and record any save messages.
    virtual bool saveToJson(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) = 0;

    /// Create control UI options for this attribute at the given position.
    virtual void controlOptions(int position, ControlComponentsContainer *components, ControlComponentsFactoriesContainer *controlComponentsFactories, std::vector<Message> &messagesHistory) = 0;

    /// Update the attribute's current value from its controls or state.
    virtual void updateValue() = 0;
};
