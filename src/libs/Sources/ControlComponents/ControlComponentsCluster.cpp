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
    static float width;
    static bool toggled = false;
    ImGui::Text("%f", width);
    ImGui::Text("%s", ((toggled) ? "Toggled" : "Off"));
    if (ImGui::TreeNodeEx(std::format("##{}", getName()).c_str()))
    {
        if (ImGui::is())
        {
            components_->draw(messageHistory);
            width = ImGui::GetItemRectSize().x;
            toggled = true;
        }
        else
        {
            width = 0;
            toggled = false;
        }
        ImGui::TreePop();
    }

    ImGui::Dummy(ImVec2(0, width));
}
