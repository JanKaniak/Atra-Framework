#include "ControlComponent.h"

class ControlComponentsContainer
{
private:
    AttributesContainer* attributesContainer_;
    std::vector<std::unique_ptr<ControlComponent>> components_;
    

public:
    ControlComponentsContainer() = default;
    ControlComponentsContainer(AttributesContainer* attributesContainer) {
        attributesContainer_ = attributesContainer;
    }
    bool existControlType(std::string attributeName);
    std::string getControlTypeByAttributeName(std::string attributeName);
    int positionOfComponentByAttributeName(std::string attributeName);
    ControlComponent *getComponent(int position) { return components_.at(position).get(); }
    int getSize() { return components_.size(); }
    void addControl(std::unique_ptr<ControlComponent> control, Attribute *attribute);
    void addControl(int position, std::unique_ptr<ControlComponent> control, Attribute *attribute);
    bool isEmpty() { return components_.empty(); }
    bool deleteControlComponent(Attribute *attribute);
    bool swapControlComponent(int position, std::unique_ptr<ControlComponent> control, Attribute *attribute) 
    {
        if (control == nullptr)
        {
            return false;
        }

        if (components_.empty() || position >= components_.size())
        {
            components_.emplace_back(std::move(control));
            components_.at(components_.size()-1)->setAttribute(attribute);
            return true;
        }

        components_.at(position) = std::move(control);
        components_.at(position)->setAttribute(attribute);
        return true;
    }
    void clear() { components_.clear(); }
    ControlComponent *getControlComponentByAttribute(Attribute *attribute) {
        for (int i = 0; i < components_.size(); ++i)
        {
            if (components_.at(i)->getAttribute(attribute->getName()) != nullptr) {
                return components_.at(i).get();
            }
        }
        return nullptr;
        
    }
    void deleteAttribute(Attribute *attribute, AttributesContainer* attributesContainer, std::vector<Message>& messageHistory);
    void draw(std::vector<Message> &messageHistory);
    void changeAttributesContainer(AttributesContainer* attributesContainer) { attributesContainer_ = attributesContainer;}
};