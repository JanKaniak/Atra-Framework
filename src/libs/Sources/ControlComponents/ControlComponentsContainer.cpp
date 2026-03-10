#include "ControlComponentsContainer.h"

std::string ControlComponentsContainer::getControlTypeByAttributeName(std::string attributeName)
{
    for (auto &component : components_)
    {
        if (!component->getType(attributeName).empty())
        {
            return component->getType(attributeName);
        }
    }
    return "";
}

bool ControlComponentsContainer::existControlType(std::string attributeName)
{
    for (auto &component : components_)
    {
        if (component->sameName(attributeName)) {
            return true;
        }
    }
    return false;
}

int ControlComponentsContainer::positionOfComponentByAttributeName(std::string attributeName)
{
    for (int i = 0; i < components_.size(); ++i)
    {
        if (components_.at(i)->sameName(attributeName))
        {
            return i;
        }
    }
    return -1;
}

void ControlComponentsContainer::addControl(std::unique_ptr<ControlComponent> control, Attribute *attribute)
{
    if (control != nullptr)
    {
        components_.push_back(std::move(control));
    }

    if (attribute != nullptr) {
        components_.at(components_.size()-1)->setAttribute(attribute);
    }
}
void ControlComponentsContainer::addControl(int position, std::unique_ptr<ControlComponent> control, Attribute *attribute)
{
    if (position < 0) {
        return;
    }
    if (position < components_.size())
    {
        components_.emplace(components_.begin() + position, std::move(control));
    } else {
        components_.emplace_back(std::move(control));
    }

    if (attribute != nullptr) {
        components_.at(components_.size()-1)->setAttribute(attribute);
    }
}

bool ControlComponentsContainer::deleteControlComponent(Attribute *attribute) {
    for(auto it = components_.begin(); it != components_.end(); ++it) {
        if (it->get()->getAttribute(attribute->getName()) != nullptr) {
            components_.erase(it);
            return true;
        }
    }
    return false;
}