#include "ControlComponentCluster.h"
#include "ControlComponentsContainer.h"

template <EditTypeCluster TYPE>
bool ControlComponentCluster<TYPE>::sameName(std::string_view name)
{
    if (!name.empty() && attribute_->getName().compare(name) == 0)
    {
        return true;
    }
    return false;
}

template <EditTypeCluster TYPE>
std::string ControlComponentCluster<TYPE>::getType(std::string_view name)
{
    if (!name.empty() && sameName(name.data()))
    {
        return EditTypeClusterConverter::EnumToString(type_).data();
    }
    return components_->getControlTypeByAttributeName(name.data());
}

template <EditTypeCluster TYPE>
void ControlComponentCluster<TYPE>::setAttribute(Attribute *attribute)
{
    if (dynamic_cast<AttributeCluster *>(attribute))
    {
        attribute_ = dynamic_cast<AttributeCluster *>(attribute);
        components_ = new ControlComponentsContainer();
        components_->changeAttributesContainer(attribute_->getAttributeContainer());
    }
}

template <EditTypeCluster TYPE>
void ControlComponentCluster<TYPE>::updateLimitValues()
{
    for (int i = 0; i < components_->getSize(); ++i)
    {
        components_->getComponent(i)->updateLimitValues();
    }
}


Tree::Tree() { dimensions_ = ImVec2(0,0);}


void Tree::draw(std::vector<Message> &messageHistory)
{
    if (ImGui::TreeNodeEx(std::format("##{}{}", getName(),attribute_->getDescription()->getID()).c_str()))
    {
        components_->draw(messageHistory);
        dimensions_.x = components_->getDimensions().x;
        dimensions_.y = components_->getDimensions().y * 1.7f;
        ImGui::TreePop();
    } else {
        dimensions_ = ImVec2(ImGui::CalcTextSize("Input").x,(ImGui::CalcTextSize("Input").y * 1.5f));
    }
}
