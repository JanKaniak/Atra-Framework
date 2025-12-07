#include "Formular.h"

// Class Formular
Formular::Formular()
{
    attributes_ = std::make_unique<Attributes>();
    decision_.emplace(AttributeType::INT, IntEditFactory::getInstance());
}

void Formular::addAttribute(std::string name, std::string editType, AttributeType type, AttributeTypeVariant min, AttributeTypeVariant max)
{
    attributes_->addAttribute("", name, type, min, max);
    components_.push_back(decision_[type]->createEdit(editType));
    components_.at(components_.size() - 1)->setAttribute(attributes_->getLast());
}
void Formular::addAttribute(std::string attributeName, AttributeType type, std::string agentName, AttributeTypeVariant min, AttributeTypeVariant max)
{
    attributes_->addAttribute(agentName, attributeName, type, min, max);
}

bool Formular::addControlType(std::string attributeName, std::string agentName, std::string editType, std::string &outputMessage)
{
    if (attributes_->contains(attributeName, agentName))
    {
        outputMessage = std::format("Attribute %s does not exist for agent %s!", attributeName, agentName);
        return false;
    }

    if (!sameName(attributeName))
    {
        components_.push_back(decision_[attributes_->giveAttributeByName(attributeName)->getType()]->createEdit(editType));
        components_.at(components_.size() - 1)->setAttribute(attributes_->giveAttributeByName(attributeName));
    }
    else
    {
        outputMessage = "Control for this attribute already exists!";
        return false;
    }
    return true;
}

void Formular::showControls()
{
    static float f = 0.0f;
    static int counter = 0;

    int minHeight = (getNumberOfComponents() * 30) + 100;
    // ImGui::SetNextWindowSizeConstraints(ImVec2(500, minHeight), ImVec2(FLT_MAX, FLT_MAX));
    ImGuiViewport *mainViewPort = ImGui::GetMainViewport();
    ImVec2 pos = mainViewPort->Pos;
    ImVec2 size = mainViewPort->Size;
    ImGui::SetNextWindowPos(pos);
    ImGui::SetNextWindowSize(ImVec2(size.x / 3, size.y));
    ImGui::Begin("Main", &mainWindows, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar);
    ImGui::BeginMenuBar();
    if (ImGui::MenuItem("Load", "L", &selectedMenu))
    {
        selectedMenu = true;
    }
    ImGui::EndMenuBar();
    if (ImGui::Button("Add an atribute"))
    {
        editWindow = true;
    }

    // 2.1 Výpis
    ImGui::SetNextWindowPos(ImVec2(pos.x + (size.x / 3) + 5, pos.y));
    ImGui::SetNextWindowSize(ImVec2(size.x / 3, size.y));
    // ImGui::SameLine();
    ImGui::Begin("Atributes", &mainWindows, ImGuiWindowFlags_NoCollapse);
    draw();
    ImGui::End();

    if (ImGui::Button("Load Attribute description", ImVec2(150, 30)))
    {
        numberOfLoadedAtributes = readFileDescriptions("atributy.json", infoMessage);
    }

    if (ImGui::Button("Load Control types", ImVec2(150, 30)))
    {
        numberOfLoadedControls = readFileControlTypes("controlTypes.json", infoMessage);
    }

    if (numberOfLoadedAtributes == -1 || numberOfLoadedControls == -1)
    {
        if (showWarning(infoMessage))
        {
            numberOfLoadedAtributes = INT_MAX;
            numberOfLoadedControls = INT_MAX;
            infoMessage = "";
        }
        ImGui::End();
    }
    else if (numberOfLoadedAtributes > 0 && numberOfLoadedAtributes != INT_MAX)
    {
        ImGui::Begin("Info");
        ImGui::Text("Successfully loaded %d attributes", numberOfLoadedAtributes);
        if (ImGui::Button("OK", ImVec2(70, 50)))
        {
            numberOfLoadedAtributes = INT_MAX;
        }
        ImGui::End();
    }

    if (ImGui::Button("Save", ImVec2(70, 30)))
    {
        saveToFile();
    }

    ImVec2 windowSize = ImGui::GetWindowSize();
    ImGui::SetCursorPos(ImVec2(20, windowSize.y - 20));
    if (getNumberOfAttributes() < 500000)
    {
        ImGui::Text("Current number of atributes: %d", getNumberOfAttributes());
    }
    else
    {
        ImGui::Text("Current number of atributes: 500000+");
    }

    if (editWindow)
    {
        showEditWindow();
    }
    ImGui::End();
}

void Formular::showEditWindow()
{
    if (ImGui::Begin("Edtiacne okno", &editWindow))
    {
        AttributeType chosenType;
        if (ImGui::RadioButton("Numeric", selected == 0))
        {
            selected = 0;
        }
        ImGui::SameLine();
        if (ImGui::RadioButton("Charakter", selected == 1))
        {
            selected = 1;
        }

        ImGui::SameLine();
        if (ImGui::RadioButton("Boolean", selected == 2))
        {
            selected = 2;
        }

        ImGui::InputText("Názov atribútut", buffer, sizeof(buffer));
        if (nameExists)
        {
            ImGui::Text("Meno atributu už existuje!");
        }
        switch (selected)
        {

        case 0:
            ImGui::Combo("Atribute type", &typeChoise, numericTypeChoice, sizeof(numericTypeChoice) / sizeof(numericTypeChoice[0]));
            if (typeChoise == 0)
            {
                ImGui::Combo("Edit type", &controlChoice, controls, sizeof(controls) / sizeof(controls[0]));
            }

            ImGui::InputText("Minimum", bufferMin, sizeof(bufferMin));
            ImGui::InputText("Maximum", bufferMax, sizeof(bufferMax));

            chosenType = numAttributeType[typeChoise];
            break;

        case 1:
            ImGui::Combo("Atribute type", &typeChoise, textTypeChoice, sizeof(textTypeChoice) / sizeof(textTypeChoice[0]));
            chosenType = textAttributeType[typeChoise];
            break;

        default:
            break;
        }
        if (ImGui::Button("Save"))
        {
            nameExists = sameName(buffer);
            if (!nameExists)
            {
                addAttribute(std::string(buffer), controls[controlChoice], chosenType, std::atoi(bufferMin), std::atoi(bufferMax));
                editWindow = false;
            }
        }

        ImGui::End();
    }
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

int Formular::readFileDescriptions(const char *path, std::string &outputMessage)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        outputMessage = "File does not exist!";
        return -1;
    }
    nlohmann::json jsonFile = nlohmann::json::parse(file);
    file.close();

    for (auto &it : jsonFile)
    {
        for (auto [agentKey, agentValue] : it.items())
        { // agent name = agentKey
            for (auto [attributeGroupKey, attributeGroupValue] : agentValue.items())
            { // attribute type = attributeGroupValue
                for (auto [attributeKey, attributeValue] : attributeGroupValue.items())
                { // attributeValue = list of attributes, attributeKey = attribute type
                    std::cout << agentKey << std::endl;
                    if (!decision2_[attributeKey](attributeValue, agentKey, outputMessage))
                    {
                        outputMessage = "These attributes are already loaded!";
                        return -1;
                    }
                }
            }
        }
    }

    /*for (auto &it : jsonFile)
    {
        if (it["Attributes"].is_array())
        {
            if (!decision2_[it["Attribute type"].get<std::string>()](it["Attributes"],outputMessage))
            {
                return -1;
            }
        }
    }*/
    return attributes_->getSize();
}

int Formular::readFileControlTypes(const char *path, std::string &outputMessage)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        outputMessage = "File does not exist!";
        return -1;
    }
    nlohmann::json jsonFile = nlohmann::json::parse(file);
    file.close();
    int tmpNumberOfLoadedControls = 0;
    auto agent = jsonFile[0];
    //auto attribute = agent.find(attributes_->giveAttribute(0)->getName());
    std::cout << agent << std::endl;
    std::cout << jsonFile[1] << std::endl;
    /*for (int i = 0; i < attributes_->getSize(); i++)
    {
        for (auto &object : jsonFile) {
        if (agent.contains(attributes_->giveAttribute(i)->getAgent()))
        {
            auto attribute = agent.find(attributes_->giveAttribute(i)->getName());
            if (attribute != agent.end())
            {
                if (!attribute.value().is_string())
                {
                    outputMessage = "Slider type must be in a string format!";
                    return -1;
                }
                addControlType(attributes_->giveAttribute(i)->getName(), attribute.key(),attribute.value().get<std::string>());
                tmpNumberOfLoadedControls++;
            }
            addControlType(attributes_->giveAttribute(i)->getName(),"" ,"",outputMessage);
        }
        else
        {
            outputMessage = std::format("Agent %s is not in a file!", attributes_->giveAttribute(i)->getAgent());
            return -1;
        }
}
    }*/
    return tmpNumberOfLoadedControls;
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

bool Formular::showWarning(std::string message)
{
    ImGui::SetNextWindowSize(ImVec2(500, 400));
    // ImGui::SetNextWindowPos()
    if (ImGui::Begin("Warning window", &openedWindow, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
    {
        ImGui::Text("There has been some error with your file!");
        ImGui::Text("%s", message.c_str());
        if (ImGui::Button("OK", ImVec2(70, 50)))
        {
            return true;
        }
    }
    return false;
}