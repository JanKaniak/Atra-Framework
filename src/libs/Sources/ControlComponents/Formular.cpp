#include "Formular.h"
#include "nfd.h"

// Class Formular
Formular::Formular()
{
    attributes_ = std::make_unique<Attributes>();
}

/*void Formular::addAttribute(std::string name, std::string editType, AttributeType type, AttributeTypeVariant min, AttributeTypeVariant max)
{
    attributes_->addAttribute("", name, type, min, max);
    components_.push_back(factoryChoice_[type]->createEdit(editType));
    components_.at(components_.size() - 1)->setAttribute(attributes_->getLast());
}*/

/*void Formular::addAttribute(std::string attributeName, AttributeType type, std::string agentName, AttributeTypeVariant min, AttributeTypeVariant max)
{
    attributes_->addAttribute(agentName, attributeName, type, min, max);
}*/

bool Formular::addControlType(std::string attributeName, std::string agentName, std::string editType, std::string &outputMessage)
{
    if (!attributes_->contains(attributeName, agentName))
    {
        outputMessage = std::format("Attribute %s does not exist for agent %s!", attributeName, agentName);
        return false;
    }

    if (!sameName(attributeName))
    {
        Factory *factory = config.getFactory(attributes_->giveAttributeByName(attributeName)->getType());
        if (factory == nullptr)
        {
            outputMessage = "Attribute type does not exist!";
            return false;
        }
        components_.push_back(factory->createEdit(editType));
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
    Factory *factory = config.getFactory(attribute->getType());
    if (factory == nullptr)
    {
        outputMessage = "Attribute type does not exist!";
        return false;
    }
    components_.push_back(config.getFactory(attribute->getType())->createEdit(""));
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
    ImGui::Begin("Main", &mainWindows, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);

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
    else if (!infoMessage.empty())
    {
        ImGui::Begin("Info", (bool *)__null, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("%s", infoMessage.c_str());
        if (ImGui::Button("OK", ImVec2(70, 50)))
        {
            numberOfLoadedAtributes = INT_MAX;
            numberOfLoadedControls = INT_MAX;
            infoMessage = "";
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

    /*if (editWindow)
    {
        showEditWindow();
    }*/
    ImGui::End();
}

/*void Formular::showEditWindow()
{
    if (ImGui::Begin("Edtiacne okno", &editWindow, ImGuiWindowFlags_NoBringToFrontOnFocus))
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
}*/

void Formular::showAttributes()
{
    // ImGui::SetNextWindowSize(ImVec2(300,500));
    ImGui::Begin("Atributes", &mainWindows, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
    std::string agent = "";
    bool tableCreated = false;
    for (auto &component : components_)
    {
        if (component == nullptr)
        {
            continue;
        }
        if (agent.empty())
        {
            agent = component->getAgent();
            ImGui::Text("%s", agent.c_str());
            ImGui::BeginTable(agent.c_str(), 5, ImGuiTableFlags_BordersOuter);
            ImGui::TableSetupColumn("Attribute name");
            ImGui::TableSetupColumn("Input");
            ImGui::TableSetupColumn("Attribute type");
            ImGui::TableSetupColumn("EditButton");
            ImGui::TableSetupColumn("DeleteButton");
            ImGui::TableHeadersRow();
        }
        else if (component->getAgent().compare(agent) != 0)
        {
            agent = component->getAgent();
            ImGui::EndTable();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);
            ImGui::Text("%s", agent.c_str());
            ImGui::BeginTable(agent.c_str(), 5, ImGuiTableFlags_BordersOuter);
            ImGui::TableSetupColumn("Attribute name");
            ImGui::TableSetupColumn("Input");
            ImGui::TableSetupColumn("Attribute type");
            ImGui::TableSetupColumn("EditButton");
            ImGui::TableSetupColumn("DeleteButton");
            ImGui::TableHeadersRow();
        }

        ImGui::TableNextColumn();
        ImGui::Text("%s", component->getName().c_str());
        ImGui::TableNextColumn();
        component->draw();
        ImGui::TableNextColumn();
        ImGui::Text("%s", enumToString[component->getType()].c_str());
        ImGui::TableNextColumn();
        if (ImGui::Button(std::format("Edit##{}{}", component->getName(), component->getAgent()).c_str(), ImVec2(50, 30)))
        {
            drawed = true;
            chosenAttribute = component.get()->getAttribute();
        }

        ImGui::TableNextColumn();
        if (ImGui::Button(std::format("Delete##{}{}", component->getName(), component->getAgent()).c_str(), ImVec2(50, 30)))
        {
            deleteAttribute(component->getAttribute(), infoMessage);
        }
    }
    ImGui::EndTable();
    if (drawed) {
        ImGui::OpenPopup("Edit window");
        drawed = false;
    }
    
    if (ImGui::BeginPopup("Edit window"))
        {
            if (editBuffer != chosenAttribute->getName())
            {
                strcpy(editBuffer, chosenAttribute->getName().c_str());
            }
            ImGui::Text("Agent: %s", chosenAttribute->getAgent().c_str());
            ImGui::InputText("Attribute name", editBuffer, sizeof(editBuffer));
            ImGui::Text("Attribute type: %s", enumToString[chosenAttribute->getType()].c_str());

            if (ImGui::Button("Close",ImVec2(60,30))) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

    ImGui::End();
}

void Formular::editAttribute(Attribute *attribute, std::string &outputMessage)
{
    if (chosenAttribute == nullptr)
    {
        return;
    }
}

void Formular::deleteAttribute(Attribute *attribute, std::string &outputMessage)
{
    for (auto it = components_.begin(); it < components_.end(); it++)
    {
        if (attribute->getName().compare(it->get()->getName()) == 0 && attribute->getAgent().compare(it->get()->getAgent()) == 0)
        {
            components_.erase(it);
            break;
        }
    }
    if (!attributes_->deleteAttribute(attribute))
    {
        outputMessage = "Attribute does not exist!";
    }
    else
    {

        outputMessage = "Attribute was deleted!";
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
    std::string outputPath_ = path;
    NFD_Init();
    nfdu8char_t *outputPath;
    nfdu8filteritem_t filters[1] = {{"Json file", "json"}};
    nfdopendialogu8args_t args = {0};
    args.filterList = filters;
    args.filterCount = 1;
    nfdresult_t result = NFD_OpenDialogU8_With(&outputPath, &args);
    if (result == NFD_OKAY)
    {
        puts("Success!");
        puts(outputPath);
        outputPath_ = outputPath;
        NFD_FreePathU8(outputPath);
    }
    else if (result == NFD_CANCEL)
    {
        puts("User pressed cancel.");
    }
    else
    {
        printf("Error: %s\n", NFD_GetError());
    }

    NFD_Quit();
    std::ifstream file(outputPath_);
    if (!file.is_open())
    {
        outputMessage = "File does not exist!";
        return -1;
    }
    nlohmann::ordered_json jsonFile = nlohmann::ordered_json::parse(file);
    file.close();
    for (auto agent = jsonFile.begin(); agent != jsonFile.end(); ++agent) // agent name = agent.key
    {
        auto agentDescriptions = agent.value();
        for (auto descriptions = agentDescriptions.begin(); descriptions != agentDescriptions.end(); ++descriptions) // attributeDescriptions = list of attributes, attributeTypeKey = attribute type
        {
            if (!attributes_->addDescriptions(stringToEnum[descriptions.key()], descriptions.value(), agent.key(), outputMessage))
            {
                return -1;
            }
        }
    }
    attributes_->createAttributes();
    outputMessage = std::format("Successfully loaded {} attributes", attributes_->getSize());
    attributes_.get()->vypis();
    return attributes_->getSize();
}

int Formular::readFileControlTypes(const char *path, std::string &outputMessage)
{
    std::string outputPath_ = path;
    NFD_Init();
    nfdu8char_t *outputPath;
    nfdu8filteritem_t filters[1] = {{"Json file", "json"}};
    nfdopendialogu8args_t args = {0};
    args.filterList = filters;
    args.filterCount = 1;
    nfdresult_t result = NFD_OpenDialogU8_With(&outputPath, &args);
    if (result == NFD_OKAY)
    {
        puts("Success!");
        puts(outputPath);
        outputPath_ = outputPath;
        NFD_FreePathU8(outputPath);
    }
    else if (result == NFD_CANCEL)
    {
        puts("User pressed cancel.");
    }
    else
    {
        printf("Error: %s\n", NFD_GetError());
    }

    NFD_Quit();
    std::ifstream file(outputPath_);
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
        if (!jsonFile.contains(attributes_->giveAttribute(i)->getAgent()))
        {
            addControlType(attributes_->giveAttribute(i), outputMessage);
            continue;
        }
        auto agent = jsonFile.find(attributes_->giveAttribute(i)->getAgent());
        if (agent.value().contains(attributes_->giveAttribute(i)->getName()))
        {
            auto editType = agent.value().find(attributes_->giveAttribute(i)->getName());
            if (!editType.value().is_string())
            {
                components_.clear();
                outputMessage = std::format("Edit type's name must be a string!", attributes_->giveAttribute(i)->getAgent());
                return -1;
            }
            addControlType(attributes_->giveAttribute(i)->getName(), agent.key(), editType.value(), outputMessage);
            tmpNumberOfLoadedControls++;
        }
        else
        {
            if (!addControlType(attributes_->giveAttribute(i), outputMessage))
            {
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
        outputMessage = std::format("Successfully loaded {} controls", tmpNumberOfLoadedControls);
    }
    return tmpNumberOfLoadedControls;
}

bool Formular::saveToFile(std::string &outputMessage)
{
    nlohmann::ordered_json jsonTemp;
    for (int i = 0; i < attributes_->getSize(); ++i)
    {
        Attribute *attribute = attributes_->giveAttribute(i);
        if (!jsonTemp.contains(attribute->getAgent()))
        {

            jsonTemp += nlohmann::ordered_json::object_t::value_type(attribute->getAgent(), nlohmann::ordered_json::object());
        }

        auto agent = jsonTemp.find(attribute->getAgent());
        if (agent == jsonTemp.end())
        {
            return false;
        }

        if (!agent.value().contains(enumToString[attribute->getType()]))
        {
            agent.value().push_back(nlohmann::ordered_json::object_t::value_type(enumToString[attribute->getType()], nlohmann::ordered_json::array()));
        }

        auto attributeType = agent.value().find(enumToString[attribute->getType()]);
        if (attributeType == agent.value().end())
        {
            return false;
        }

        attributeType.value().push_back(nlohmann::ordered_json::object());
        attributeType.value()[attributeType.value().size() - 1].push_back(nlohmann::ordered_json::object_t::value_type("Attribute name", attribute->getName()));
        attribute->saveToJson(attributeType.value()[attributeType.value().size() - 1], outputMessage);
    }

    std::ofstream file("output.json");
    file << jsonTemp;
    file.close();
    return true;
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

// save + load virtualna metoda
// dependency injection
// rozdelit pridavanie descriptions a attributovy