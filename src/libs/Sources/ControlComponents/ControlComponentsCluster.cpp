#include "ControlComponentCluster.h"
#include "ControlComponentsContainer.h"

template <EditTypeCluster TYPE>
/// Check whether this cluster component is bound to the given attribute name.
bool ControlComponentCluster<TYPE>::sameName(std::string_view name)
{
    if (!name.empty() && attribute_->getName().compare(name) == 0)
    {
        return true;
    }
    return false;
}

template <EditTypeCluster TYPE>
/// Return the cluster control type string when the name matches, otherwise
/// delegate to the nested component container.
std::string ControlComponentCluster<TYPE>::getType(std::string_view name)
{
    if (!name.empty() && sameName(name.data()))
    {
        return EditTypeClusterConverter::EnumToString(type_).data();
    }
    return components_->getControlTypeByAttributeName(name.data());
}

template <EditTypeCluster TYPE>
/// Bind a cluster attribute and initialize a nested control container for it.
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
/// Refresh limit values for all nested controls in the cluster.
void ControlComponentCluster<TYPE>::updateLimitValues()
{
    for (int i = 0; i < components_->getSize(); ++i)
    {
        components_->getComponent(i)->updateLimitValues();
    }
}

/// Default construct a tree cluster control with zero dimensions.
Tree::Tree() { dimensions_ = ImVec2(0, 0); }

/// Render the tree node for the cluster and draw nested controls when open.
void Tree::draw(std::vector<Message> &messageHistory)
{
    if (ImGui::TreeNodeEx(std::format("##{}{}", getName(), attribute_->getDescription()->getID()).c_str()))
    {
        components_->draw(messageHistory);
        if (components_->getDimensions().x > ImGui::CalcTextSize("Input").x && components_->getDimensions().y * 1.7f > ImGui::CalcTextSize("Input").y * 1.5f)
        {
            dimensions_ = ImVec2(components_->getDimensions().x, components_->getDimensions().y * 1.7f);
        }
        else
        {
            dimensions_ = ImVec2(ImGui::CalcTextSize("Input").x, (ImGui::CalcTextSize("Input").y * 1.5f));
        }
        ImGui::TreePop();
    }
    else
    {
        dimensions_ = ImVec2(ImGui::CalcTextSize("Input").x, (ImGui::CalcTextSize("Input").y * 1.5f));
    }
}
