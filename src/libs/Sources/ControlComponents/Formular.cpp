#include "Formular.h"
#include "nfd.h"

#include <time.h>

// Class Formular
Formular::Formular()
{
    attributes_ = std::make_unique<Attributes>();
}

bool Formular::addControlType(std::string attributeName, std::string editType, std::string &outputMessage)
{
    if (!attributes_->contains(attributeName))
    {
        outputMessage = std::format("Attribute with name %s does not exist!", attributeName);
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
        if (components_.empty())
        {
            components_.push_back(factory->createEdit(editType));
            components_.at(components_.size() - 1)->setAttribute(attributes_->giveAttributeByName(attributeName));
            return true;
        }
        int position = attributes_->getPosition(attributeName);
        if (position < 0)
        {
            outputMessage = "Attribute with this name does not exists!";
            return false;
        }

        if (position >= components_.size())
        {
            components_.push_back(factory->createEdit(editType));
            components_.at(components_.size() - 1)->setAttribute(attributes_->giveAttributeByName(attributeName));
            return true;
        }

        components_.emplace(components_.begin() + position, factory->createEdit(editType));
        components_.at(position)->setAttribute(attributes_->giveAttributeByName(attributeName));
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
    if (components_.empty())
    {
        components_.push_back(factory->createEdit(""));
        components_.at(components_.size() - 1)->setAttribute(attributes_->giveAttributeByName(attribute->getName()));
        return true;
    }
    int position = attributes_->getPosition(attribute->getName());
    if (position < 0)
    {
        outputMessage = "Attribute with this name does not exists!";
        return false;
    }

    if (position >= components_.size())
    {
        components_.push_back(factory->createEdit(""));
        components_.at(components_.size() - 1)->setAttribute(attributes_->giveAttributeByName(attribute->getName()));
        return true;
    }

    components_.emplace(components_.begin() + position, factory->createEdit(""));
    components_.at(position)->setAttribute(attributes_->giveAttributeByName(attribute->getName()));

    return true;
}

bool Formular::addOrReplaceControlTypeByVector(std::vector<std::string> controlTypesVector, std::string &outputMessage)
{
    if (controlTypesVector.size() != attributes_->getSize())
    {
        outputMessage = "Temporary vector for storing control types of attributes must be the same size as vector of attributes!";
        return false;
    }
    for (int i = 0; i < controlTypesVector.size(); ++i)
    {
        if (controlTypesVector.at(i).empty())
        {
            continue;
        }
        Factory *factory = config.getFactory(attributes_->giveAttribute(i)->getType());
        if (!existControlType(attributes_->giveAttribute(i)->getName()))
        {
            if (components_.empty())
            {
                components_.push_back(factory->createEdit(""));
                components_.at(components_.size() - 1)->setAttribute(attributes_->giveAttribute(i));
                return true;
            }

            if (i >= components_.size())
            {
                components_.push_back(factory->createEdit(""));
                components_.at(components_.size() - 1)->setAttribute(attributes_->giveAttribute(i));
                return true;
            }

            components_.emplace(components_.begin() + i, factory->createEdit(""));
            components_.at(i)->setAttribute(attributes_->giveAttribute(i));
        }
        else
        {
            std::string type = getControlTypeByAttributeName(attributes_->giveAttribute(i)->getName());
            if (type.compare(controlTypesVector.at(i)) == 0)
            {
                continue;
            }

            int position = positionOfComponentByAttributeName(attributes_->giveAttribute(i)->getName());
            if (position < 0)
            {
                outputMessage = "Control type does not exist for this attribtue!";
                return false;
            }

            components_.at(i) = factory->createEdit(controlTypesVector.at(i));
            components_.at(i)->setAttribute(attributes_->giveAttribute(i));
        }
    }
    return true;
}

bool Formular::replaceControlType(Attribute *attribute, std::string &outputMessage)
{
    Factory *factory = config.getFactory(attribute->getType());
    if (factory == nullptr)
    {
        outputMessage = "Attribute type does not exist!";
        return false;
    }
    if (components_.empty())
    {
        components_.push_back(factory->createEdit(""));
        components_.at(components_.size() - 1)->setAttribute(attributes_->giveAttributeByName(attribute->getName()));
        return true;
    }
    int position = attributes_->getPosition(attribute->getName());
    if (position < 0)
    {
        outputMessage = "Attribute with this name does not exists!";
        return false;
    }

    if (position >= components_.size())
    {
        components_.push_back(factory->createEdit(""));
        components_.at(components_.size() - 1)->setAttribute(attributes_->giveAttributeByName(attribute->getName()));
        return true;
    }

    components_.emplace(components_.begin() + position, factory->createEdit(""));
    components_.at(position)->setAttribute(attributes_->giveAttributeByName(attribute->getName()));

    return true;
}

void Formular::showControls()
{
    static float f = 0.0f;
    static int counter = 0;

    int minHeight = (getNumberOfComponents() * 30) + 100;
    static ImVec2 size = ImGui::GetMainViewport()->Size;
    ImGui::SetNextWindowSize(ImVec2(0 / 3, size.y));
    if (ImGui::Begin("Main", nullptr, ImGuiWindowFlags_NoCollapse))
    {

        showLogger();

        if (ImGui::Button("Load Attribute description", ImVec2(0, 30)))
        {
            numberOfLoadedAtributes = readFileDescriptions("atributy.json", infoMessage);
        }

        if (ImGui::Button("Add description", ImVec2(0, 30)))
        {
            ImGui::OpenPopup("Edtiacne okno", ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_NoReopen);
        }

        ImGui::BeginDisabled(attributes_->getNumberOfDescriptions() == 0);
        if (ImGui::Button("Generate attributes from descriptions", ImVec2(0, 30)))
        {
            time_t now = time(NULL);
            struct tm *t = localtime(&now);
            char buffer[100];
            strftime(buffer, sizeof(buffer), "%H:%M:%S", t);
            static int size;
            static bool changed = false;
            attributes_->createAttributes();
            if (size == 0)
            {
                size = attributes_->getSize();
                changed = true;
            }
            else if (attributes_->getSize() != size)
            {
                size = attributes_->getSize();
                changed = true;
            }

            if (changed)
            {
                infoMessage = std::format("{}  Attributes were successfuly generated from descriptions!", buffer, size);
                changed = false;
            }
            else
            {
                infoMessage = std::format("{}  All attributes with actual descriptions are generated!", buffer, size);
            }
        }
        ImGui::EndDisabled();

        ImGui::BeginDisabled(attributes_->getSize() == 0);
        if (ImGui::Button("Load Control types", ImVec2(0, 30)))
        {
            numberOfLoadedControls = readFileControlTypes("controlTypes.json", infoMessage);
        }
        ImGui::SameLine();
        ImGui::Checkbox("Use default controls", &useDefaultControls);
        ImGui::SameLine();
        ImGui::Checkbox("Overwrite existing controls", &overWriteExistingControls);

        if (ImGui::Button("Modify control types", ImVec2(0, 30)))
        {
            ImGui::OpenPopup("Modify control types window", ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_NoReopen);
        }

        if (ImGui::Button("Save", ImVec2(0, 30)))
        {
            saveToFile(infoMessage);
        }

        ImGui::EndDisabled();

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

        showAddDescriptionWindow();
        showModifyControlTypesWindow();

        ImGui::End();
    }
}

void Formular::showLogger()
{
    static std::vector<std::string> messageHistory;
    float width = ImGui::GetContentRegionAvail().x;

    if (!infoMessage.empty())
    {
        messageHistory.emplace_back(infoMessage);
        infoMessage = "";
    }

    ImGui::BeginChild("Logger", ImVec2(width * 0.999999f, 300), ImGuiChildFlags_Border, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);
    for (int i = 0; i < messageHistory.size(); ++i)
    {
        ImGui::TextWrapped("%s", messageHistory.at(i).c_str());
    }

    if (messageHistory.size() > 1000)
    {
        messageHistory.erase(messageHistory.begin());
    }
    ImGui::EndChild();
}

void Formular::showAddDescriptionWindow()
{
    static char buffer[40] = "Attribute";
    static int selected;
    static std::string chosenType;
    static std::string category = "NUMERIC";
    if (ImGui::BeginPopup("Edtiacne okno", ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (ImGui::RadioButton("Numeric", selected == 0))
        {
            selected = 0;
        }
        ImGui::SameLine();
        if (ImGui::RadioButton("Text", selected == 1))
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
            if (ImGui::BeginCombo("Attribute type", chosenType.c_str()))
            {
                for (int i = 0; i < attributes_->getRegisteredDescriptionsTypes().size(); ++i)
                {
                    if (attributes_->getRegisteredDescriptionsTypes().at(i).getCategory().compare(category) != 0)
                    {
                        continue;
                    }
                    bool selected = (chosenType == enumToString[attributes_->getRegisteredDescriptionsTypes().at(i).getType()].c_str());
                    if (ImGui::Selectable(enumToString[attributes_->getRegisteredDescriptionsTypes().at(i).getType()].c_str(), selected))
                    {
                        chosenType = enumToString[attributes_->getRegisteredDescriptionsTypes().at(i).getType()].c_str();
                    }
                    if (selected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }

                ImGui::EndCombo();
            }
            break;

        case 1:
            break;

        default:
            break;
        }
        if (ImGui::Button("Save"))
        {

            nameExists = sameName(buffer);
            if (!nameExists)
            {
                attributes_->addDescriptions(std::string(buffer), stringToEnum[chosenType], infoMessage);
                addDescriptionWindow = false;
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Close"))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void Formular::showModifyControlTypesWindow()
{
    static std::vector<std::string> chosenTypeVector;
    static bool overWrite;
    if (attributes_->getSize() == 0)
    {
        return;
    }
    if (chosenTypeVector.size() < attributes_->getSize())
    {
        chosenTypeVector.resize(attributes_->getSize());
        overWrite = true;
    }

    if (numberOfLoadedControls > 0 && numberOfLoadedControls < INT_MAX)
    {
        overWrite = true;
    }

    if (overWrite)
    {
        for (int i = 0; i < attributes_->getSize(); ++i)
        {
            std::string type = getControlTypeByAttributeName(attributes_->giveAttribute(i)->getName());
            if (!type.empty())
            {
                chosenTypeVector.at(i) = type;
            }
        }
        overWrite = false;
    }
    if (ImGui::BeginPopup("Modify control types window", ImGuiWindowFlags_AlwaysAutoResize))
    {
        for (int i = 0; i < attributes_->getSize(); ++i)
        {
            // ImGui::BeginChild(attributes_->giveAttribute(i)->getName().c_str(),ImVec2(0,400));
            ImGui::Text("%s", attributes_->giveAttribute(i)->getName().c_str());
            ImGui::SameLine();
            ImGui::Text("%s", enumToString[attributes_->giveAttribute(i)->getType()].c_str());
            ImGui::SameLine();
            Factory *factory = config.getFactory(attributes_->giveAttribute(i)->getType());
            if (ImGui::BeginCombo(std::format("Control Type##{}", attributes_->giveAttribute(i)->getName()).c_str(), chosenTypeVector.at(i).c_str()))
            {
                for (int j = 0; j < factory->getNameOfControlTypesVector().size(); ++j)
                {
                    bool selected = (chosenTypeVector.at(i).compare(factory->getNameOfControlTypesVector().at(j)) == 0);
                    if (ImGui::Selectable(factory->getNameOfControlTypesVector().at(j).c_str(), selected))
                    {
                        chosenTypeVector.at(i) = factory->getNameOfControlTypesVector().at(j);
                    }
                    if (selected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }

                ImGui::EndCombo();
            }
            // ImGui::EndChild();
            ImGui::Dummy(ImVec2(30, 30));
        }
        if (ImGui::Button("Save", ImVec2(0, 30)))
        {
            addOrReplaceControlTypeByVector(chosenTypeVector, infoMessage);
        }

        if (ImGui::Button("Close", ImVec2(0, 30)))
        {
            overWrite = true;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void Formular::showAttributes()
{
    if (components_.size() == 0)
    {
        return;
    }
    if (ImGui::Begin("Atributes", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
    {
        bool tableCreated = false;
        for (auto &component : components_)
        {
            if (component == nullptr)
            {
                continue;
            }
            ImGui::BeginTable("Attributes", 5, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_SizingFixedFit);
            ImGui::TableSetupColumn("Attribute name");
            ImGui::TableSetupColumn("Input", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Attribute type");
            ImGui::TableSetupColumn("EditButton");
            ImGui::TableSetupColumn("DeleteButton");
            ImGui::TableHeadersRow();
            ImGui::TableNextColumn();
            ImGui::Text("%s", component->getName().c_str());
            ImGui::TableNextColumn();
            component->draw();
            ImGui::TableNextColumn();
            ImGui::Text("%s", enumToString[component->getAttribute()->getType()].c_str());
            ImGui::TableNextColumn();
            if (ImGui::Button("Edit", ImVec2(0, 30)))
            {
                drawed = true;
                chosenAttribute = component.get()->getAttribute();
            }
            ImGui::TableNextColumn();
            if (ImGui::Button("Delete", ImVec2(0, 30)))
            {
                deleteAttribute(component->getAttribute(), infoMessage);
            }
            ImGui::EndTable();
        }
    }

    if (drawed)
    {
        ImGui::OpenPopup("Edit window");
        drawed = false;
    }

    if (ImGui::BeginPopup("Edit window"))
    {
        static bool exist;
        char editBuffer[40];
        ImGui::InputText("Attribute name", editBuffer, sizeof(editBuffer));
        if (exist)
        {
            ImGui::Text("%s", "Attribute with this name already exists!");
        }
        ImGui::Text("Attribute type: %s", enumToString[chosenAttribute->getType()].c_str());

        if (ImGui::Button("Save", ImVec2(0, 30)))
        {
            if (!exist)
            {
                strcpy(editBuffer, chosenAttribute->getName().c_str());
                exist = false;
                ImGui::CloseCurrentPopup();
            }
            else
            {
                exist = true;
            }
        }

        if (ImGui::Button("Close", ImVec2(0, 30)))
        {
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
        if (attribute->getName().compare(it->get()->getName()) == 0)
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
        outputPath_ = outputPath;
        NFD_FreePathU8(outputPath);
    }
    else if (result == NFD_CANCEL)
    {
    }
    else
    {
        outputMessage = std::format("Error: %s\n", NFD_GetError());
        return -1;
    }

    NFD_Quit();
    if (outputPath_.empty())
    {
        return INT_MAX;
    }
    std::ifstream file(outputPath_);
    if (!file.is_open())
    {
        outputMessage = "File does not exist!";
        return -1;
    }
    nlohmann::ordered_json jsonFile = nlohmann::ordered_json::parse(file);
    file.close();
    for (auto &descriptions : jsonFile) // attributeDescriptions = list of attributes, attributeTypeKey = attribute type
    {

        for (auto &descriptionsOfTheSameType : descriptions.items())
        {
            if (!attributes_->addDescriptions(stringToEnum[descriptionsOfTheSameType.key()], descriptionsOfTheSameType.value(), outputMessage))
            {
                return -1;
            }
        }
    }
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", t);
    outputMessage = std::format("{}  Successfully loaded {} attributes descriptions!", buffer, attributes_->getNumberOfDescriptions());
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
        outputPath_ = outputPath;
        NFD_FreePathU8(outputPath);
    }
    else if (result == NFD_CANCEL)
    {
    }
    else
    {
        outputMessage = std::format("Error: %s\n", NFD_GetError());
        return -1;
    }

    NFD_Quit();
    if (outputPath_.empty())
    {
        return INT_MAX;
    }
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
        auto editType = jsonFile.find(attributes_->giveAttribute(i)->getName());
        if (editType == jsonFile.end())
        {
            if (!useDefaultControls)
            {
                continue;
            }

            if (existControlType(attributes_->giveAttribute(i)->getName()))
            {
                if (!overWriteExistingControls)
                {
                    continue;
                }

                if (!replaceControlType(attributes_->giveAttribute(i), outputMessage))
                {
                    return -1;
                }
                continue;
            }

            if (!addControlType(attributes_->giveAttribute(i), outputMessage))
            {
                return -1;
            }
            continue;
        }

        if (existControlType(editType.key()))
        {
            if (!overWriteExistingControls)
            {
                continue;
            }

            if (!replaceControlType(attributes_->giveAttributeByName(editType.key()), outputMessage))
            {
                return -1;
            }
            continue;
        }

        if (!editType.value().is_string())
        {
            components_.clear();
            outputMessage = "Edit type's name must be a string!";
            return -1;
        }
        if (!addControlType(attributes_->giveAttribute(i)->getName(), editType.value(), outputMessage))
        {
            return -1;
        }
        tmpNumberOfLoadedControls++;
    }
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", t);
    if (tmpNumberOfLoadedControls == 0)
    {
        outputMessage = std::format("{}  Either control types in file have incorrect names or you're trying to overwrite existing control types, check you file or enable overwritting.", buffer);
        return -1;
    }
    if (tmpNumberOfLoadedControls < components_.size())
    {
        outputMessage = std::format("{}  Successfully loaded {} controls and some attributes were given default control types because they were missing in a file!", buffer, tmpNumberOfLoadedControls);
    }
    else if (tmpNumberOfLoadedControls == components_.size())
    {

        outputMessage = std::format("{}  Successfully loaded {} control!s", buffer, tmpNumberOfLoadedControls);
    }
    return tmpNumberOfLoadedControls;
}

bool Formular::saveToFile(std::string &outputMessage)
{
    nlohmann::ordered_json jsonTemp;
    jsonTemp = nlohmann::ordered_json::array();
    int positionInArray = 0;
    for (int i = 0; i < attributes_->getSize(); ++i)
    {
        Attribute *attribute = attributes_->giveAttribute(i);
        jsonTemp.push_back(nlohmann::ordered_json::object());
        jsonTemp[positionInArray][enumToString[attribute->getType()]] = nlohmann::ordered_json::array();
        if (jsonTemp.empty())
        {
            return false;
        }
        for (int j = i; j < attributes_->getSize(); ++j)
        {
            if (attributes_->giveAttribute(j)->getType() != attribute->getType())
            {
                i = j - 1;
                positionInArray++;
                break;
            }
            auto attributeType = jsonTemp[positionInArray].find(enumToString[attributes_->giveAttribute(j)->getType()]);
            if (jsonTemp[positionInArray].end() == attributeType)
            {
                outputMessage = "Attribute type does not exist in this file yet!";
                return false;
            }
            attributeType.value().push_back(nlohmann::ordered_json::object());
            attributes_->giveAttribute(j)->saveToJson(attributeType.value()[attributeType.value().size() - 1], outputMessage);
        }
    }

    std::ofstream file("output.json");
    file << jsonTemp;
    file.close();
    outputMessage = "Attributes were successfully saved in the file!";
    return true;
}

bool Formular::showWarning(std::string message)
{
    ImGui::SetNextWindowSize(ImVec2(500, 400));
    if (ImGui::Begin("Warning window", &openedWindow, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
    {
        ImGui::Text("There has been some error with your file!");
        ImGui::Text("%s", message.c_str());
        if (ImGui::Button("OK", ImVec2(0, 50)))
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

std::string Formular::getControlTypeByAttributeName(std::string attributeName)
{
    for (auto &component : components_)
    {
        if (component->getAttribute()->getName().compare(attributeName) == 0)
        {
            return component->getType();
        }
    }
    return "";
}

bool Formular::existControlType(std::string attributeName)
{
    for (auto &component : components_)
    {
        if (component->getAttribute()->getName().compare(attributeName) == 0)
        {
            return true;
        }
    }
    return false;
}

int Formular::positionOfComponentByAttributeName(std::string attributeName)
{
    for (int i = 0; i < components_.size(); ++i)
    {
        if (components_.at(i)->getAttribute()->getName().compare(attributeName) == 0)
        {
            return i;
        }
    }
    return -1;
}

// save + load virtualna metoda
// dependency injection
// rozdelit pridavanie descriptions a attributovy