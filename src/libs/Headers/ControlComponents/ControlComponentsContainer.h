#include "ControlComponent.h"
#include "Factory.h"

/// Container for managing UI control components bound to attribute instances.
///
/// This class creates, stores, and updates control components for the
/// configured attribute container while tracking render dimensions and
/// control-type state.
class ControlComponentsContainer
{
private:
    ControlComponentsFactoriesContainer *controlComponentsFactories_;
    AttributesContainer *attributes_;
    std::vector<std::unique_ptr<ControlComponent>> components_;
    bool updatedTable_;
    ImVec2 dimensions_;
public:
    /// Construct an empty control container with the master factory.
    ControlComponentsContainer()
    {
        controlComponentsFactories_ = ControlComponentsFactoriesContainer::getInstance();
        updatedTable_ = true;
        dimensions_ = ImVec2(-1,-1);
    }
    /// Construct a control container bound to an existing attributes container.
    ControlComponentsContainer(AttributesContainer *attributesContainer)
    {
        controlComponentsFactories_ = ControlComponentsFactoriesContainer::getInstance();
        attributes_ = attributesContainer;
        updatedTable_ = true;
        dimensions_ = ImVec2(-1,-1);
    }

    /// Return the current container display dimensions.
    ImVec2 getDimensions() { return dimensions_;}

    /// Check whether a specific attribute has an associated control type.
    bool existControlType(std::string attributeName);
    /// Return the control type string registered for the named attribute.
    std::string getControlTypeByAttributeName(std::string attributeName);

    /// Return the index of the component bound to the named attribute.
    int positionOfComponentByAttributeName(std::string attributeName);

    /// Return the component at the given position.
    ControlComponent *getComponent(int position) { return components_.at(position).get(); }

    /// Find a component by its attribute name.
    ControlComponent *getComponentByName(std::string name) { 
        for (auto &component: components_)
        {
            if (component->getName().compare(name) == 0) {
                return component.get();
            }
        }
        return nullptr;
     }

    /// Return the number of stored control components.
    int getSize() { return components_.size(); }
    /// Add a new control component and bind it to its attribute.
    void addControl(std::unique_ptr<ControlComponent> control, Attribute *attribute);

    /// Insert a new control component at the specified position.
    void addControl(int position, std::unique_ptr<ControlComponent> control, Attribute *attribute);

    /// Create and add a control for the specified attribute using the factory.
    bool addControl(Attribute* attribute, std::vector<Message> &messageHistory);

    /// Return whether there are no control components.
    bool isEmpty() { return components_.empty(); }

    /// Remove the component bound to the given attribute.
    bool deleteControlComponent(Attribute *attribute);
    /// Replace the component at the given position with a new control.
    bool swapControlComponent(int position, std::unique_ptr<ControlComponent> control, Attribute *attribute);

    /// Remove all stored control components.
    void clear() { components_.clear(); }

    /// Find a component bound to the given attribute pointer.
    ControlComponent *getControlComponentByAttribute(Attribute *attribute);

    /// Delete an attribute and its associated controls.
    void deleteAttribute(Attribute *attribute, AttributesContainer *attributesContainer, std::vector<Message> &messageHistory);
    /// Render all control components and process user interaction messages.
    void draw(std::vector<Message> &messageHistory);

    /// Change the bound attributes container for this control set.
    void changeAttributesContainer(AttributesContainer *attributesContainer) { attributes_ = attributesContainer; }

    /// Return whether the rendered table state is out-of-date.
    bool isTableUpdated() { return updatedTable_;}

    /// Mark the table state as updated or stale.
    void setTableUpdated(bool update) { updatedTable_ = update;}

    /// Delete every managed control component.
    void deleteAllControlComponents(std::vector<Message> &messageHistory);
    /// Populate controls from the given factory set using current attributes.
    void setDefaultControls(ControlComponentsFactoriesContainer *controlComponentsFactories, std::vector<Message> &messageHistory);

    /// Assign a control type to an attribute identified by path and edit type.
    bool addControlTypeByNames(std::string path, std::string editType, std::vector<Message> &messageHistory);

    /// Assign a default control type for the attribute at the given path.
    bool addDefaultControlType(std::string path, std::vector<Message> &messageHistory);

    /// Swap the control implementation for an attribute using a new edit type.
    bool swapControlComponentByAttribute(Attribute *attribute, std::string editType, std::vector<Message> &messageHistory);

    /// Return the master control component factory container.
    ControlComponentsFactoriesContainer *getMasterFactory() { return controlComponentsFactories_;}
};