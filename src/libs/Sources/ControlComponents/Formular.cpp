#include "Formular.h"
#include "nfd.h"

#include <time.h>

// Class Formular
Formular::Formular()
{
    attributes_ = std::make_unique<Attributes>();
    config = Config::getInstance();
    showAttributesWindowSize_ = ImVec2(600, 800);

    showSettingWindow_ = false;
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
        Factory *factory = config->getFactory(attributes_->giveAttributeByName(attributeName)->getType());
        if (factory == nullptr)
        {
            outputMessage = std::format("Controls for {}  attribute type does not exist!", AttributeTypeConverter::getInstance()->convertEnumToString(attributes_->giveAttributeByName(attributeName)->getType()));
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
    Factory *factory = config->getFactory(attribute->getType());
    if (factory == nullptr)
    {
        outputMessage = "Attribute type does not exist!";
        return false;
    }
    if (components_.empty())
    {
        components_.push_back(factory->createDefaultEdit());
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
        components_.push_back(factory->createDefaultEdit());
        components_.at(components_.size() - 1)->setAttribute(attributes_->giveAttributeByName(attribute->getName()));
        return true;
    }

    components_.emplace(components_.begin() + position, factory->createDefaultEdit());
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
        Factory *factory = config->getFactory(attributes_->giveAttribute(i)->getType());
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

bool Formular::replaceControlType(Attribute *attribute, std::string controlType, std::string &outputMessage)
{
    Factory *factory = config->getFactory(attribute->getType());
    if (factory == nullptr)
    {
        outputMessage = "Attribute type does not exist!";
        return false;
    }

    int position = attributes_->getPosition(attribute->getName());
    if (position < 0)
    {
        outputMessage = "Attribute with this name does not exists!";
        return false;
    }

    std::unique_ptr<ControlComponent> tmpControl = factory->createEdit(controlType);
    if (controlType.compare(tmpControl->getType()) == 0)
    {
        return false;
    }
    if (components_.empty())
    {
        components_.push_back(std::move(tmpControl));
        components_.at(components_.size() - 1)->setAttribute(attributes_->giveAttributeByName(attribute->getName()));
        return true;
    }

    if (position >= components_.size())
    {
        components_.push_back(std::move(tmpControl));
        components_.at(components_.size() - 1)->setAttribute(attributes_->giveAttributeByName(attribute->getName()));
        return true;
    }

    components_.at(position) = std::move(tmpControl);
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
    if (ImGui::Begin("Main", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar))
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Load attribute descriptions"))
                {
                    readFileDescriptions(descriptionsPath_, infoMessage);
                }

                if (ImGui::MenuItem("Load control types", nullptr, nullptr, attributes_->getSize() > 0))
                {
                    readFileControlTypes(controlTypesPath_, infoMessage);
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Options"))
            {
                if (ImGui::MenuItem("Settings"))
                {
                    showSettingWindow_ = true;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        showLogger();

        if (ImGui::Button("Load Attribute description", ImVec2(0, 30)))
        {
            numberOfLoadedAtributes = readFileDescriptions(descriptionsPath_, infoMessage);
        }

        if (ImGui::Button("Add description", ImVec2(0, 30)))
        {
            ImGui::OpenPopup("Edtiacne okno", ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_NoReopen);
        }

        ImGui::BeginDisabled(attributes_->getNumberOfDescriptions() == 0);
        if (ImGui::Button("Generate attributes from descriptions", ImVec2(0, 30)))
        {

            if (attributes_->createAttributes(infoMessage))
            {
                time_t now = time(NULL);
                struct tm *t = localtime(&now);
                char buffer[100];
                strftime(buffer, sizeof(buffer), "%H:%M:%S", t);
                static int size;
                static bool changed = false;
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
        }
        ImGui::EndDisabled();

        ImGui::BeginDisabled(attributes_->getSize() == 0);
        if (ImGui::Button("Load Control types", ImVec2(0, 30)))
        {
            numberOfLoadedControls = readFileControlTypes(controlTypesPath_, infoMessage);
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
        showSettings();
        ImGui::End();
    }
}

void Formular::showSettings()
{
    if (!showSettingWindow_)
    {
        return;
    }

    static char descriptionsPath[40] = "atributy.json";
    static char controlTypesPath[40] = "controlTypes.json";
    if (!ImGui::Begin("Settins", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
    {
        return;
    }

    ImGui::InputText("Path for attributes descriptions", descriptionsPath, sizeof(descriptionsPath));
    ImGui::InputText("Path for control types", controlTypesPath, sizeof(controlTypesPath));

    if (ImGui::Button("Save")) {
        if (descriptionsPath[0] != '\0' && controlTypesPath[0] != '\0') {
            descriptionsPath_ = descriptionsPath;
            controlTypesPath_ = controlTypesPath;
            showSettingWindow_ = false;
        }
    }

    if (ImGui::Button("Close")) {
        showSettingWindow_ = false;
    }
    ImGui::End();
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

    if (ImGui::BeginChild("Logger", ImVec2(width * 0.999999f, 300), ImGuiChildFlags_Border, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar))
    {

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

    ImGui::BeginDisabled(messageHistory.size() == 0);
    if (ImGui::Button("Clear logger", ImVec2(0, 30)))
    {
        messageHistory.clear();
    }
    ImGui::EndDisabled();
}

void Formular::showAddDescriptionWindow()
{

    static char buffer[40] = "Attribute";
    static int selected;
    static std::string chosenType;
    static std::string category = "NUMERIC";
    static bool correctMinimum = false;
    static bool correctMaximum = false;


    if (ImGui::BeginPopupModal("Edtiacne okno", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
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
                    bool selected = (chosenType == AttributeTypeConverter::getInstance()->convertEnumToString(attributes_->getRegisteredDescriptionsTypes().at(i).getType()).c_str());
                    if (ImGui::Selectable(AttributeTypeConverter::getInstance()->convertEnumToString(attributes_->getRegisteredDescriptionsTypes().at(i).getType()).c_str(), selected))
                    {
                        chosenType = AttributeTypeConverter::getInstance()->convertEnumToString(attributes_->getRegisteredDescriptionsTypes().at(i).getType()).c_str();
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
        static bool savedAndCorrect = false;
        if (ImGui::Button("Save"))
        {

            nameExists = sameName(buffer);
            if (!nameExists)
            {
                attributes_->addDescriptions(std::string(buffer), AttributeTypeConverter::getInstance()->convertStringtoEnum(chosenType), infoMessage);
                savedAndCorrect = true;
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
        numberOfLoadedControls = INT_MAX;
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
    if (ImGui::BeginPopupModal("Modify control types window", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        for (int i = 0; i < attributes_->getSize(); ++i)
        {
            bool empty = false;
            ImGuiChildFlags flags;
            if (chosenTypeVector[i].empty())
            {
                ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1, 0, 0, 1));
                empty = true;
                flags = ImGuiChildFlags_Border | ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY;
            }
            else
            {
                flags = ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY;
            }
            if (ImGui::BeginChild(std::format("Border##{}", attributes_->giveAttribute(i)->getName()).c_str(), ImVec2(0, 0), flags))
            {
                ImGui::Text("%s", attributes_->giveAttribute(i)->getName().c_str());
                ImGui::SameLine();
                ImGui::Text("%s", AttributeTypeConverter::getInstance()->convertEnumToString(attributes_->giveAttribute(i)->getType()).c_str());
                ImGui::SameLine();
                Factory *factory = config->getFactory(attributes_->giveAttribute(i)->getType());
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
                ImGui::EndChild();
            }
            if (empty)
            {
                ImGui::PopStyleColor();
            }
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
    ImGui::SetNextWindowSize(showAttributesWindowSize_);
    if (ImGui::Begin("Atributes", nullptr, ImGuiWindowFlags_NoCollapse))
    {
        bool tableCreated = false;
        for (auto &component : components_)
        {
            if (component == nullptr)
            {
                continue;
            }
            ImVec2 avaiableSpace = ImGui::GetContentRegionAvail();
            if (ImGui::BeginTable("Attributes", 5, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_ScrollX, ImVec2(0, ImGui::GetFrameHeight() + 5 * (ImGui::GetTextLineHeight() + ImGui::GetStyle().CellPadding.y * 1.5f))))
            {
                ImGui::TableSetupColumn("Attribute name", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("Input", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("Attribute type", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("EditButton", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("DeleteButton", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableHeadersRow();
                ImGui::TableNextColumn();
                ImGui::Text("%s", component->getName().c_str());
                ImGui::TableNextColumn();
                component->draw();
                ImGui::TableNextColumn();
                ImGui::Text("%s", AttributeTypeConverter::getInstance()->convertEnumToString(component->getAttribute()->getType()).c_str());
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
        ImGui::Text("Attribute type: %s", AttributeTypeConverter::getInstance()->convertEnumToString(chosenAttribute->getType()).c_str());

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

int Formular::readFileDescriptions(std::filesystem::path path, std::string &outputMessage)
{
    std::filesystem::path outputPath_ = path;
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
            if (!attributes_->addDescriptions(AttributeTypeConverter::getInstance()->convertStringtoEnum(descriptionsOfTheSameType.key()), descriptionsOfTheSameType.value(), outputMessage))
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

int Formular::readFileControlTypes(std::filesystem::path path, std::string &outputMessage)
{
    std::filesystem::path outputPath_ = path;
    NFD_Init();
    nfdu8char_t *outputPath;
    nfdu8filteritem_t filters[1] = {{"Json file", "json"}};
    nfdopendialogu8args_t args = {0};
    args.filterList = filters;
    args.filterCount = 1;
    nfdresult_t result = NFD_OpenDialogU8_With(&outputPath, &args);

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char buffer[100];

    if (result == NFD_OKAY)
    {
        outputPath_ = outputPath;
        NFD_FreePathU8(outputPath);
    }
    else if (result == NFD_CANCEL)
    {
        outputPath_ = "";
    }
    else
    {
        strftime(buffer, sizeof(buffer), "%H:%M:%S", t);
        outputMessage = std::format("{}  Error: {}, ", buffer, NFD_GetError());
        return -1;
    }

    NFD_Quit();
    if (outputPath_.empty())
    {
        return INT_MAX;
    }
    std::ifstream file(outputPath_);

    strftime(buffer, sizeof(buffer), "%H:%M:%S", t);
    if (!file.is_open())
    {
        outputMessage = std::format("{}  File does not exist!", buffer);
        return -1;
    }

    nlohmann::json jsonFile = nlohmann::json::parse(file);
    file.close();
    int tmpNumberOfLoadedControls = 0;
    int tmpOverWrittedControls = 0;

    strftime(buffer, sizeof(buffer), "%H:%M:%S", t);
    if (attributes_->getSize() == 0)
    {
        outputMessage = std::format("{}  Before creating control types attributes must exist!", buffer);
        return -1;
    }
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
                continue;
            }

            if (!addControlType(attributes_->giveAttribute(i), outputMessage))
            {
                return -1;
            }
            continue;
        }

        if (!editType.value().is_string())
        {
            components_.clear();
            outputMessage = "Control type name must be a string!";
            return -1;
        }

        if (existControlType(editType.key()))
        {
            if (!overWriteExistingControls)
            {
                continue;
            }

            if (!replaceControlType(attributes_->giveAttributeByName(editType.key()), editType.value(), outputMessage))
            {
                return -1;
            }
            tmpOverWrittedControls++;
            continue;
        }

        if (!addControlType(attributes_->giveAttribute(i)->getName(), editType.value(), outputMessage))
        {
            return -1;
        }
        tmpNumberOfLoadedControls++;
    }
    strftime(buffer, sizeof(buffer), "%H:%M:%S", t);
    if (tmpOverWrittedControls > 0)
    {
        outputMessage = std::format("{}  {} controls were successfuly overwritten!", buffer, tmpOverWrittedControls);
        return tmpOverWrittedControls;
    }
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
        jsonTemp[positionInArray][AttributeTypeConverter::getInstance()->convertEnumToString(attribute->getType())] = nlohmann::ordered_json::array();
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
            auto attributeType = jsonTemp[positionInArray].find(AttributeTypeConverter::getInstance()->convertEnumToString(attributes_->giveAttribute(j)->getType()));
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

// bug pri nacitani control typov druhykrat s overwritom tak vznikaju duplikaty