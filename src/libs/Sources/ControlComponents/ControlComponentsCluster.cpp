#include "ControlComponentCluster.h"
#include "ControlComponentsContainer.h"

template <EditTypeCluster TYPE>
bool ControlComponentCluster<TYPE>::sameName(std::string name)
{
    if (attributecluster_->getName().compare(name) == 0)
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
        attributecluster_ = dynamic_cast<AttributeCluster *>(attribute);
        components_ = new ControlComponentsContainer();
        components_->changeAttributesContainer(attributecluster_->getAttributeContainer());
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

void Tree::draw(std::vector<Message> &messageHistory)
{
    static Attribute *chosenAttribute;
    if (ImGui::TreeNode(attributecluster_->getName().c_str()))
    {
        for (int i = 0; i < components_->getSize(); ++i)
        {
            if (ImGui::TreeNodeEx(components_->getComponent(i)->getName().c_str(), ImGuiTreeNodeFlags_Leaf))
            {
                components_->draw(messageHistory);
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }
}
