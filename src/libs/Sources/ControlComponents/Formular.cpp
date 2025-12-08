#include "Formular.h"

// Class Formular
Formular::Formular()
{
    attributes_ = std::make_unique<Attributes>();
    factoryChoice_.emplace(AttributeType::INT, IntEditFactory::getInstance());
}

void Formular::addAttribute(std::string name, std::string editType, AttributeType type, AttributeTypeVariant min, AttributeTypeVariant max)
{
    attributes_->addAttribute("", name, type, min, max);
    components_.push_back(factoryChoice_[type]->createEdit(editType));
    components_.at(components_.size() - 1)->setAttribute(attributes_->getLast());
}
void Formular::addAttribute(std::string attributeName, AttributeType type, std::string agentName, AttributeTypeVariant min, AttributeTypeVariant max)
{
    attributes_->addAttribute(agentName, attributeName, type, min, max);
}

bool Formular::addControlType(std::string attributeName, std::string agentName, std::string editType, std::string &outputMessage)
{
    if (!attributes_->contains(attributeName, agentName))
    {
        outputMessage = std::format("Attribute %s does not exist for agent %s!", attributeName, agentName);
        return false;
    }

    if (!sameName(attributeName))
    {
        components_.push_back(factoryChoice_[attributes_->giveAttributeByName(attributeName)->getType()]->createEdit(editType));
        components_.at(components_.size() - 1)->setAttribute(attributes_->giveAttributeByName(attributeName));
    }
    else
    {
        outputMessage = "Control for this attribute already exists!";
        return false;
    }
    return true;
}

bool Formular::addControlType(Attribute *attribute, std::string &outputMessage)
{
    components_.push_back(factoryChoice_[attribute->getType()]->createEdit(""));
    components_.at(components_.size() - 1)->setAttribute(attribute);
    return true;
}

void Formular::showControls()
{
    static float f = 0.0f;
    static int counter = 0;

    int minHeight = (getNumberOfComponents() * 30) + 100;
    // ImGui::SetNextWindowSizeConstraints(ImVec2(500, minHeight), ImVec2(FLT_MAX, FLT_MAX));
    ImGuiViewport *mainViewPort = ImGui::GetMainViewport();
    ImVec2 size = mainViewPort->Size;
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
        ImGui::Text("%s", infoMessage.c_str());
        if (ImGui::Button("OK", ImVec2(70, 50)))
        {
            numberOfLoadedAtributes = INT_MAX;
        }
        ImGui::End();
    }

    if (ImGui::Button("Save", ImVec2(70, 30)))
    {
        bool gg = saveToFile(infoMessage);
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

void Formular::showAttributes()
{
    ImGui::Begin("Atributes", &mainWindows, ImGuiWindowFlags_NoCollapse);
    std::string agent = "";
    bool endOfAgent = false;
    for (auto &component : components_)
    {
        if (agent.empty())
        {
            agent = component->getAgent();
            ImGui::BeginTable(agent.c_str(), 3, ImGuiTableFlags_BordersOuter);
            ImGui::TableSetupColumn("Attribute name");
            ImGui::TableSetupColumn("Input");
            ImGui::TableSetupColumn("Attribute type");
            ImGui::TableHeadersRow();
        }
        else if (component->getAgent().compare(agent) != 0)
        {
            agent = component->getAgent();
            ImGui::EndTable();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);
            ImGui::BeginTable(agent.c_str(), 3, ImGuiTableFlags_BordersOuter);
            ImGui::TableSetupColumn("Attribute name");
            ImGui::TableSetupColumn("Input");
            ImGui::TableSetupColumn("Attribute type");
            ImGui::TableHeadersRow();
        }

        ImGui::TableNextColumn();
        ImGui::Text("%s", component->getName().c_str());
        ImGui::TableNextColumn();
        component->draw();
        ImGui::TableNextColumn();
        ImGui::Text("%s", enumToString[component->getType()].c_str());
    }
    ImGui::EndTable();
    ImGui::End();
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

    for (auto [agentKey, agentValue] : jsonFile.items()) //agent name = agentKey
    { 
        for (auto [attributeGroupKey, attributeGroupValue] : agentValue.items()) // attribute type = attributeGroupValue
        { 
            for (auto [attributeTypeKey, attributeDescriptions] : agentValue.items()) // attributeDescriptions = list of attributes, attributeTypeKey = attribute type
            { 
                if (!decision2_[attributeTypeKey](attributeDescriptions, agentKey, outputMessage))
                {
                    outputMessage = "These attributes are already loaded!";
                    return -1;
                }
            }
        }
    }

    outputMessage = std::format("Successfully loaded {} attributes", attributes_->getSize());
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
    for (int i = 0; i < attributes_->getSize(); i++)
    {
        for (auto &object : jsonFile)
        {
            if (object.contains(attributes_->giveAttribute(i)->getAgent()))
            {
                auto agent = object.find(attributes_->giveAttribute(i)->getAgent());
                for (auto &controlTypes : agent.value())
                {
                    if (!controlTypes.contains(attributes_->giveAttribute(i)->getName()))
                    {
                        addControlType(attributes_->giveAttribute(i), outputMessage);
                    }
                    addControlType(attributes_->giveAttribute(i)->getName(), agent.key(), controlTypes.find(attributes_->giveAttribute(i)->getName()).value(), outputMessage);
                    tmpNumberOfLoadedControls++;
                }
            }
            else
            {
                outputMessage = std::format("Agent %s is not in a file!", attributes_->giveAttribute(i)->getAgent());
                return -1;
            }
        }
    }
    if (tmpNumberOfLoadedControls < components_.size())
    {
        outputMessage = "Some attributes were given default control types because they were missing in a file!";
    }
    else if (tmpNumberOfLoadedControls == components_.size())
    {
        outputMessage = std::format("Successfully loaded %d controls", tmpNumberOfLoadedControls);
    }
    return tmpNumberOfLoadedControls;
}

bool Formular::saveToFile(std::string &outputMessage)
{
    nlohmann::json jsonTemp;
    for (int i = 0; i < attributes_->getSize(); i++)
    {
        Attribute* attribute = attributes_->giveAttribute(i);
        if (!jsonTemp.contains(attribute->getAgent()))
        {
            
            jsonTemp += nlohmann::json::object_t::value_type(attribute->getAgent(),nlohmann::json::object());
        }
        

        auto agent = jsonTemp.find(attribute->getAgent());
        if(agent == jsonTemp.end()) {
            return false;
        }

        if (!agent.value().contains(enumToString[attribute->getType()])) {
            agent.value().push_back(nlohmann::json::object_t::value_type(enumToString[attribute->getType()],nlohmann::json::array()));
        }

        auto attributeType = agent.value().find(enumToString[attribute->getType()]);
        if (attributeType == agent.value().end()) {
            return false;
        }

        attributeType.value().push_back(nlohmann::json::object());
        attributeType.value()[attributeType.value().size()-1].push_back(nlohmann::json::object_t::value_type("Attribute name",attribute->getName()));
        saveAdditionalInfoToFile_[attribute->getType()](attributeType.value()[attributeType.value().size()-1],attribute,outputMessage);
    }

    
    std::ofstream file("output.json");
    file << jsonTemp;
    file.close();
    return true;
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