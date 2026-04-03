#include "ControlComponent.h"
#include "Factory.h"

class ControlComponentsContainer
{
private:
    AttributesContainer *attributesContainer_;
    std::vector<std::unique_ptr<ControlComponent>> components_;
    bool updatedTable_;
    ImVec2 dimensions_;

public:
    ControlComponentsContainer()
    {
        updatedTable_ = true;
        dimensions_ = ImVec2(-1,-1);
    }
    ControlComponentsContainer(AttributesContainer *attributesContainer)
    {
        attributesContainer_ = attributesContainer;
        updatedTable_ = true;
        dimensions_ = ImVec2(-1,-1);
    }
    ImVec2 getDimensions() { return dimensions_;}
    bool existControlType(std::string attributeName);
    std::string getControlTypeByAttributeName(std::string attributeName);
    int positionOfComponentByAttributeName(std::string attributeName);
    ControlComponent *getComponent(int position) { return components_.at(position).get(); }
    int getSize() { return components_.size(); }
    void addControl(std::unique_ptr<ControlComponent> control, Attribute *attribute);
    void addControl(int position, std::unique_ptr<ControlComponent> control, Attribute *attribute);
    bool isEmpty() { return components_.empty(); }
    bool deleteControlComponent(Attribute *attribute);
    bool swapControlComponent(int position, std::unique_ptr<ControlComponent> control, Attribute *attribute);
    void clear() { components_.clear(); }
    ControlComponent *getControlComponentByAttribute(Attribute *attribute);
    void deleteAttribute(Attribute *attribute, AttributesContainer *attributesContainer, std::vector<Message> &messageHistory);
    void draw(std::vector<Message> &messageHistory);
    void changeAttributesContainer(AttributesContainer *attributesContainer) { attributesContainer_ = attributesContainer; }
    bool isTableUpdated() { return updatedTable_;}
    void setTableUpdated(bool update) { updatedTable_ = update;}
    void deleteAllControlComponents(std::vector<Message> &messageHistory);
    void setDefaultControls(Config *config, std::vector<Message> &messageHistory);
};