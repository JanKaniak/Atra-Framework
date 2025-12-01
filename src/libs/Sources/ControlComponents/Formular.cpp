#include "Formular.h"

// Class Formular
Formular::Formular(Attributes *attributes)
{
    openedWindow = true;
    attributes_ = attributes;
    decision_.emplace(AttributeType::INT, IntEditFactory::getInstance());
}

void Formular::addAttribute(std::string name, std::string editType, AttributeType type, AttributeTypeVariant min, AttributeTypeVariant max)
{
    attributes_->addAttribute(name, type, min, max);
    components_.push_back(decision_[type]->createEdit(editType));
    components_.at(components_.size() - 1)->setAttribute(attributes_->getLast());
}
bool Formular::addAttribute(std::string name, AttributeType type, AttributeTypeVariant min, AttributeTypeVariant max, AttributeTypeVariant value)
{
    if (!sameName(name))
    {
        attributes_->addAttribute(name, type, min, max);
        attributes_->setValueOfLast(type, value);
        return true;
    }
    return false;
}

bool Formular::addControlType(std::string attributeName, std::string editType)
{
    if (sameName(attributeName))
    {
        auto attribute = attributes_->giveAttributeByName(attributeName);
        components_.push_back(decision_[attribute->getType()]->createEdit(editType));
        components_.at(components_.size() - 1)->setAttribute(attributes_->getLast());
        return true;
    }
    return false;
}

void Formular::draw()
{
    for (auto &component : components_)
    {
        component->draw();
        ImVec2 actucalPosition = ImGui::GetCursorPos();
        ImGui::SetCursorPos(ImVec2(actucalPosition.x, actucalPosition.y + 30));
    }
}

int Formular::readFileDescriptions(const char *path)
{
    std::ifstream file(path);
    nlohmann::json jsonFile = nlohmann::json::parse(file);
    file.close();

    for (auto &it : jsonFile)
    {
        if (it["Attributes"].is_array())
        {
            if (!decision2_[it["Attribute type"].get<std::string>()](it["Attributes"]))
            {
                return attributes_->getSize();
            }
        }
    }
    return attributes_->getSize();
}

bool Formular::readFileControlTypes(const char *path) {
    std::ifstream file(path);
    nlohmann::json jsonFile = nlohmann::json::parse(file);
    file.close();

    for (auto &object : jsonFile)
    {
        for (auto &pair : object.items()) {
            if (attributes_->contains(pair.key())) {
                return true;
            }
            addControlType(pair.key(),pair.value().get<std::string>());
        }
    }
    return false;
}

void Formular::saveToFile()
{
    /*nlohmann::json jsonTemp;
    for (int i = 0; i < values_->getSize(); i++)
    {
        jsonTemp.push_back({{"Atribute name", values_->giveAtribute(i)->getName()}, {"Atribute type", static_cast<int>(values_->giveAtribute(i)->getType())}, {"Minimum", values_->giveAtribute(i)->getDescription()->getMin()}, {"Maximum", values_->giveAtribute(i)->getDescription()->getMax()}, {"Value",values_->giveAtribute(i)->getValue()}});
    }

    std::ofstream file("output.json");
    file << jsonTemp;
    file.close();*/
}

IntEditFactory *IntEditFactory::instance = nullptr;

IntEditFactory::IntEditFactory()
{
    this->registerPrototype<IntSlider>();
    this->registerPrototype<IntVSSlider>();
    this->registerPrototype<IntDrag>();
}

IntEditFactory *IntEditFactory::getInstance()
{
    if (instance == nullptr)
    {
        instance = new IntEditFactory();
    }

    return instance;
}

template <typename EditTypeIntT>
inline void IntEditFactory::registerPrototype()
{
    prototypes_[EditTypeIntT::type_] = std::move(std::make_unique<EditTypeIntT>());
}

bool Formular::sameName(std::string name)
{
    for (auto &component : components_)
    {
        if (component->getName().compare(name) == 0)
        {
            return true;
        }
    }
    return false;
}

bool Formular::showWarning()
{
    ImGui::SetNextWindowSize(ImVec2(500, 400));
    // ImGui::SetNextWindowPos()
    if (ImGui::Begin("Warning window", &openedWindow, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
    {
        ImGui::Text("There has been some error with your file!");
        ImGui::Text("Please ensure that your atributes names are unique!");
        if (ImGui::Button("OK", ImVec2(70, 50)))
        {
            return true;
        }
    }
    return false;
}