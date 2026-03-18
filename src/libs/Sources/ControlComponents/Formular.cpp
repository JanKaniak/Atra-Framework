#include "Formular.h"
#include "nfd.h"
#include "imgui_internal.h"

#include <time.h>

// Class Formular
Formular::Formular()
{
    attributeDescs_ = std::make_unique<AttributeDescriptionsContainer>();
    attributes_ = std::make_unique<AttributesContainer>(attributeDescs_.get());
    config = Config::getInstance();
    components_ = std::make_unique<ControlComponentsContainer>(attributes_.get());
    showAttributesWindowSize_ = ImVec2(600, 800);

    showSettingWindow_ = false;
    saveWindow_ = false;

    attributes_->addDescriptions("x", AttributeType::FLOAT, messageHistory_);
    attributes_->addDescriptions("y", AttributeType::FLOAT, messageHistory_);
    attributes_->addDescriptions("velX", AttributeType::FLOAT, messageHistory_);
    attributes_->addDescriptions("velY", AttributeType::FLOAT, messageHistory_);
    attributes_->createAttributes(messageHistory_);
    components_->addControl(config->getFactory(AttributeType::FLOAT)->createDefaultEdit(), attributes_->giveAttribute(0));
    components_->addControl(config->getFactory(AttributeType::FLOAT)->createDefaultEdit(), attributes_->giveAttribute(1));
    components_->addControl(config->getFactory(AttributeType::FLOAT)->createDefaultEdit(), attributes_->giveAttribute(2));
    components_->addControl(config->getFactory(AttributeType::FLOAT)->createDefaultEdit(), attributes_->giveAttribute(3));
}

bool Formular::addControlType(std::string attributeName, std::string editType)
{
    if (!attributes_->contains(attributeName))
    {
        messageHistory_.emplace_back(Message(std::format("Attribute with name %s does not exist!", attributeName)));
        return false;
    }

    if (!components_->existControlType(attributeName))
    {
        Factory *factory = config->getFactory(attributes_->giveAttributeByName(attributeName)->getType());
        if (factory == nullptr)
        {
            messageHistory_.emplace_back(Message(std::format("Controls for {}  attribute type does not exist!", AttributeTypeConverter::EnumToString(attributes_->giveAttributeByName(attributeName)->getType()))));
            return false;
        }
        if (components_->isEmpty())
        {
            components_->addControl(factory->createEdit(editType), attributes_->giveAttributeByName(attributeName));

            return true;
        }
        int position = attributes_->getPosition(attributeName);
        if (position < 0)
        {
            messageHistory_.emplace_back(Message("Attribute with this name does not exists!"));
            return false;
        }

        if (position >= components_->getSize())
        {
            components_->addControl(factory->createEdit(editType), attributes_->giveAttributeByName(attributeName));

            return true;
        }

        components_->addControl(position, factory->createEdit(editType), attributes_->giveAttributeByName(attributeName));
    }
    else
    {
        messageHistory_.emplace_back(Message("Control for this attribute already exists!"));
        return false;
    }
    return true;
}

bool Formular::addControlType(Attribute *attribute)
{
    Factory *factory = config->getFactory(attribute->getType());
    if (factory == nullptr)
    {
        messageHistory_.emplace_back(Message("Attribute type does not exist!"));
        return false;
    }
    if (components_->isEmpty())
    {
        components_->addControl(factory->createDefaultEdit(), attributes_->giveAttributeByName(attribute->getName()));
        return true;
    }
    int position = attributes_->getPosition(attribute->getName());
    if (position < 0)
    {
        messageHistory_.emplace_back(Message("Attribute with this name does not exists!"));
        return false;
    }

    if (position >= components_->getSize())
    {
        components_->addControl(factory->createDefaultEdit(), attributes_->giveAttributeByName(attribute->getName()));
        return true;
    }

    components_->addControl(position, factory->createDefaultEdit(), attributes_->giveAttributeByName(attribute->getName()));

    return true;
}

bool Formular::addOrReplaceControlTypeByVector(std::vector<std::string> controlTypesVector)
{
    if (controlTypesVector.size() != attributes_->getSize())
    {
        messageHistory_.emplace_back(Message("Temporary vector for storing control types of attributes must be the same size as vector of attributes!"));
        return false;
    }
    for (int i = 0; i < controlTypesVector.size(); ++i)
    {
        if (controlTypesVector.at(i).empty())
        {
            continue;
        }
        Factory *factory = config->getFactory(attributes_->giveAttribute(i)->getType());
        if (!components_->existControlType(attributes_->giveAttribute(i)->getName()))
        {
            if (components_->isEmpty())
            {
                components_->addControl(factory->createEdit(controlTypesVector.at(i)), attributes_->giveAttribute(i));
                continue;
            }

            if (i >= components_->getSize())
            {
                components_->addControl(factory->createEdit(controlTypesVector.at(i)), attributes_->giveAttribute(i));
                continue;
            }

            components_->addControl(i, factory->createEdit(controlTypesVector.at(i)), attributes_->giveAttribute(i));
        }
        else
        {
            std::string type = components_->getControlTypeByAttributeName(attributes_->giveAttribute(i)->getName());
            if (type.compare(controlTypesVector.at(i)) == 0)
            {
                continue;
            }

            int position = components_->positionOfComponentByAttributeName(attributes_->giveAttribute(i)->getName());
            if (position < 0)
            {
                messageHistory_.emplace_back(Message("Control type does not exist for this attribtue!"));
                return false;
            }

            components_->swapControlComponent(i, factory->createEdit(controlTypesVector.at(i)), attributes_->giveAttribute(i));
        }
    }
    return true;
}

bool Formular::replaceControlType(Attribute *attribute, std::string controlType)
{
    Factory *factory = config->getFactory(attribute->getType());
    if (factory == nullptr)
    {
        messageHistory_.emplace_back(Message("Attribute type does not exist!"));
        return false;
    }

    int position = attributes_->getPosition(attribute->getName());
    if (position < 0)
    {
        messageHistory_.emplace_back(Message("Attribute with this name does not exists!"));
        return false;
    }

    std::unique_ptr<ControlComponent> tmpControl = factory->createEdit(controlType);
    if (controlType.compare(tmpControl->getType(attribute->getName())) == 0)
    {
        return false;
    }
    if (components_->isEmpty())
    {
        components_->addControl(std::move(tmpControl), attributes_->giveAttributeByName(attribute->getName()));
        return true;
    }

    if (position >= components_->getSize())
    {
        components_->addControl(std::move(tmpControl), attributes_->giveAttributeByName(attribute->getName()));
        return true;
    }

    components_->swapControlComponent(position, std::move(tmpControl), attributes_->giveAttributeByName(attribute->getName()));

    return true;
}

void Formular::showControls()
{
    static float f = 0.0f;
    static int counter = 0;

    int minHeight = (components_->getSize() * 30) + 100;
    static ImVec2 size = ImGui::GetMainViewport()->Size;

    ImGui::SetNextWindowSize(ImVec2(0 / 3, size.y));
    if (ImGui::Begin("Main", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar))
    {
        showLogger();

        if (ImGui::BeginChild("First button group", ImVec2(0, 0), ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_Borders))
        {
            if (ImGui::Button("Load Attribute description", ImVec2(190, 30)))
            {
                numberOfLoadedAtributes = readFileDescriptions();
            }

            ImGui::BeginDisabled(attributes_->getSize() == 0);
            if (ImGui::Button("Load Control types", ImVec2(190, 30)))
            {
                numberOfLoadedControls = readFileControlTypes();
            }
            ImGui::SameLine();
            ImGui::Checkbox("Use default controls", &useDefaultControls);
            ImGui::SameLine();
            ImGui::Checkbox("Overwrite existing controls", &overWriteExistingControls);
            ImGui::EndDisabled();

            ImGui::EndChild();
            ImGui::Dummy(ImVec2(190, 30));
        }

        if (ImGui::Button("Add description", ImVec2(190, 30)))
        {
            ImGui::OpenPopup("Edit window", ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_NoReopen);
        }

        ImGui::BeginDisabled(attributes_->getNumberOfDescriptions() == 0);
        if (ImGui::Button("Generate attributes", ImVec2(190, 30)))
        {
            attributes_->createAttributes(messageHistory_);
            messageHistory_.emplace_back(Message("All attributes with actual descriptions are generated!"));
        }
        ImGui::EndDisabled();

        ImGui::BeginDisabled(attributes_->getSize() == 0);
        if (ImGui::Button("Modify control types", ImVec2(190, 30)))
        {
            ImGui::OpenPopup("Modify control types window", ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_NoReopen);
        }

        if (ImGui::Button("Save", ImVec2(190, 30)))
        {
            saveWindow_ = true;
        }

        ImGui::EndDisabled();

        showAddDescriptionWindow();
        showModifyControlTypesWindow();
        showSettings();
        saveToFile();
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

    if (ImGui::Button("Save"))
    {
        if (descriptionsPath[0] != '\0' && controlTypesPath[0] != '\0')
        {
            descriptionsPath_ = descriptionsPath;
            controlTypesPath_ = controlTypesPath;
            showSettingWindow_ = false;
        }
    }

    if (ImGui::Button("Close"))
    {
        showSettingWindow_ = false;
    }
    ImGui::End();
}

void Formular::showLogger()
{
    float width = ImGui::GetContentRegionAvail().x;
    if (ImGui::BeginChild("Logger", ImVec2(width * 0.999999f, 300), ImGuiChildFlags_Borders, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar))
    {

        for (int i = 0; i < messageHistory_.size(); ++i)
        {
            ImGui::Text("%s", messageHistory_.at(i).getTime().c_str());
            ImGui::SameLine();
            ImGui::Bullet();
            ImGui::SameLine();
            ImGui::TextWrapped("%s", messageHistory_.at(i).getMessage().c_str());
        }

        if (messageHistory_.size() > 1000)
        {
            messageHistory_.erase(messageHistory_.begin());
        }
        ImGui::EndChild();
    }

    ImGui::BeginDisabled(messageHistory_.size() == 0);
    if (ImGui::Button("Clear logger", ImVec2(190, 30)))
    {
        messageHistory_.clear();
    }
    ImGui::Dummy(ImVec2(190, 30));
    ImGui::EndDisabled();
}

void Formular::showAddDescriptionWindow()
{

    static char buffer[40] = "Attribute";
    static int selected;
    static std::string chosenType;
    static std::string chosenLevelName;
    static uint64_t chosenLevelNameId;
    static std::string category = "NUMERIC";
    static bool addedAndCorrect = false;
    static std::vector<AttributeDescription *> clusterDescriptions;
    static AttributeDescriptionsContainer *descriptionContainer;

    if (ImGui::BeginPopupModal("Edit window", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (clusterDescriptions.empty())
        {
            clusterDescriptions.push_back(nullptr);
            attributes_->findDescriptionsByType(clusterDescriptions, AttributeType::CLUSTER);
            chosenLevelName = "NULL";
        }

        ImGui::BeginDisabled(addedAndCorrect);
        if (ImGui::RadioButton("Numeric", selected == 0))
        {
            selected = 0;
            category = "NUMERIC";
            chosenType.clear();
        }
        ImGui::SameLine();
        if (ImGui::RadioButton("Text", selected == 1))
        {
            selected = 1;
            category = "TEXT";
            chosenType.clear();
        }

        ImGui::SameLine();
        if (ImGui::RadioButton("Logic", selected == 2))
        {
            selected = 2;
            category = "LOGIC";
            chosenType.clear();
        }
        ImGui::SameLine();
        if (ImGui::RadioButton("Other", selected == 3))
        {
            selected = 3;
            category = "OTHER";
            chosenType.clear();
        }
        ImGui::EndDisabled();

        ImGui::InputText("Attribute name", buffer, sizeof(buffer));
        if (nameExists)
        {
            ImGui::Text("%s", "Attribute with this name already exists!");
        }

        if (ImGui::BeginCombo("Attribute level", chosenLevelName.c_str()))
        {
            for (auto descrption : clusterDescriptions)
            {
                if (descrption == nullptr)
                {
                    bool selected = (chosenLevelName == "NULL");
                    if (ImGui::Selectable("NULL", selected))
                    {
                        chosenLevelName = "NULL";
                        chosenLevelNameId = 0;
                    }
                    if (selected)
                    {
                        ImGui::SetItemDefaultFocus();
                        descriptionContainer = nullptr;
                    }
                    continue;
                }
                bool selected = (chosenLevelName == descrption->getName());
                if (ImGui::Selectable(std::format("{}##{}", descrption->getName(), descrption->getID()).c_str(), selected))
                {
                    chosenLevelName = descrption->getName();
                    chosenLevelNameId = descrption->getID();
                }
                if (selected)
                {
                    ImGui::SetItemDefaultFocus();
                    descriptionContainer = nullptr;
                }
            }
            ImGui::EndCombo();
        }

        if (!addedAndCorrect)
        {
            if (ImGui::BeginCombo("Attribute type", chosenType.c_str()))
            {
                for (int i = 0; i < attributes_->getRegisteredDescriptionsTypes().size(); ++i)
                {
                    if (attributes_->getRegisteredDescriptionsTypes().at(i).getCategory().compare(category) != 0)
                    {
                        continue;
                    }
                    bool selected = (chosenType == AttributeTypeConverter::EnumToString(attributes_->getRegisteredDescriptionsTypes().at(i).getType()));
                    if (ImGui::Selectable(std::string(AttributeTypeConverter::EnumToString(attributes_->getRegisteredDescriptionsTypes().at(i).getType())).c_str(), selected))
                    {
                        chosenType = AttributeTypeConverter::EnumToString(attributes_->getRegisteredDescriptionsTypes().at(i).getType());
                    }
                    if (selected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }

                ImGui::EndCombo();
            }
        }
        else
        {
            ImGui::Text("%s", descriptionContainer->getLast()->getTypeString().data());
        }

        if (!addedAndCorrect)
        {

            ImGui::BeginDisabled(chosenType.empty());
            if (ImGui::Button("Add description"))
            {
                if (descriptionContainer == nullptr)
                {
                    descriptionContainer = attributes_->getDescriptionContainer(chosenLevelName, chosenLevelNameId);
                }

                nameExists = descriptionContainer->existsDescription(buffer);
                if (!nameExists)
                {
                    descriptionContainer->addDescriptions(std::string(buffer), AttributeTypeConverter::StringToEnum(chosenType), messageHistory_);
                    addedAndCorrect = true;
                }
            }
            ImGui::EndDisabled();
        }
        else
        {
            addedAndCorrect = descriptionContainer->getLast()->drawInputForChangingLimits(messageHistory_);
            if (!addedAndCorrect)
            {
                chosenLevelName = "NULL";
                descriptionContainer = nullptr;
                clusterDescriptions.clear();
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Close"))
        {
            ImGui::CloseCurrentPopup();
            addedAndCorrect = false;
            chosenType.clear();
            chosenLevelName = "NULL";
            descriptionContainer = nullptr;
            clusterDescriptions.clear();
        }

        ImGui::EndPopup();
    }
}

void Formular::showModifyControlTypesWindow()
{
    if (ImGui::BeginPopupModal("Modify control types window", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        attributes_->setControlTypes(components_.get(), config, messageHistory_);
        if (ImGui::Button("Close", ImVec2(190, 30)))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void Formular::showAttributes()
{
    static bool isWindowSizeSet = false;
    if (components_->getSize() == 0)
    {
        isWindowSizeSet = false;
        return;
    }
    if (!isWindowSizeSet)
    {
        ImGui::SetNextWindowSize(showAttributesWindowSize_);
        isWindowSizeSet = true;
    }
    if (ImGui::Begin("Atributes", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_HorizontalScrollbar))
    {
        components_->draw(messageHistory_);
        ImGui::End();
    }
}

bool Formular::loadDescriptions(nlohmann::ordered_json json)
{
    for (auto &descriptions : json) // attributeDescriptions = list of attributes, attributeTypeKey = attribute type
    {

        for (auto &descriptionsOfTheSameType : descriptions.items())
        {
            if (!attributes_->addDescriptions(AttributeTypeConverter::StringToEnum(descriptionsOfTheSameType.key()), descriptionsOfTheSameType.value(), messageHistory_))
            {
                return false;
            }
        }
    }
    messageHistory_.emplace_back(Message(std::format("Successfully loaded {} attributes descriptions!", attributes_->getNumberOfDescriptions())));
    return true;
}

int Formular::readFileDescriptions()
{
    std::filesystem::path outputPath_;
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
        messageHistory_.emplace_back(Message(std::format("Error: {}", NFD_GetError())));
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
        messageHistory_.emplace_back(Message("File does not exist!"));
        return -1;
    }
    nlohmann::ordered_json jsonFile = nlohmann::ordered_json::parse(file);
    file.close();
    if (!loadDescriptions(jsonFile))
    {
        return -1;
    }
    return attributes_->getSize();
}

int Formular::readFileControlTypes()
{
    std::filesystem::path outputPath_;
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
        outputPath_ = "";
    }
    else
    {
        messageHistory_.emplace_back(Message(std::format("Error: {}, ", NFD_GetError())));
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
        messageHistory_.emplace_back(Message("File does not exist!"));
        return -1;
    }

    nlohmann::json jsonFile = nlohmann::json::parse(file);
    file.close();
    return loadControlTypes(jsonFile);
}
int Formular::loadControlTypes(nlohmann::json json)
{
    int tmpNumberOfLoadedControls = 0;
    int tmpOverWrittedControls = 0;
    if (attributes_->getSize() == 0)
    {
        messageHistory_.emplace_back(Message("Before creating control types attributes must exist!"));
        return -1;
    }
    for (int i = 0; i < attributes_->getSize(); i++)
    {
        auto editType = json.find(attributes_->giveAttribute(i)->getName());
        if (editType == json.end())
        {
            if (!useDefaultControls)
            {
                continue;
            }

            if (components_->existControlType(attributes_->giveAttribute(i)->getName()))
            {
                continue;
            }

            if (!addControlType(attributes_->giveAttribute(i)))
            {
                return -1;
            }
            continue;
        }

        if (!editType.value().is_string())
        {
            components_->clear();
            messageHistory_.emplace_back(Message("Control type name must be a string!"));
            return -1;
        }

        if (components_->existControlType(editType.key()))
        {
            if (!overWriteExistingControls)
            {
                continue;
            }

            if (!replaceControlType(attributes_->giveAttributeByName(editType.key()), editType.value()))
            {
                return -1;
            }
            tmpOverWrittedControls++;
            continue;
        }

        if (!addControlType(attributes_->giveAttribute(i)->getName(), editType.value()))
        {
            return -1;
        }
        tmpNumberOfLoadedControls++;
    }
    if (tmpOverWrittedControls > 0)
    {
        messageHistory_.emplace_back(Message(std::format("{} controls were successfuly overwritten!", tmpOverWrittedControls)));
        return tmpOverWrittedControls;
    }
    if (tmpNumberOfLoadedControls == 0)
    {
        messageHistory_.emplace_back(Message("Either control types in file have incorrect names or you're trying to overwrite existing control types, check you file or enable overwritting."));
        return -1;
    }
    if (tmpNumberOfLoadedControls < components_->getSize())
    {
        messageHistory_.emplace_back(Message(std::format("Successfully loaded {} controls and some attributes were given default control types because they were missing in a file!", tmpNumberOfLoadedControls)));
    }
    else if (tmpNumberOfLoadedControls == components_->getSize())
    {
        messageHistory_.emplace_back(Message(std::format("Successfully loaded {} control!s", tmpNumberOfLoadedControls)));
    }
    return tmpNumberOfLoadedControls;
}

nlohmann::ordered_json Formular::saveOutput()
{
    nlohmann::ordered_json tempJson;
    tempJson = nlohmann::ordered_json::array();
    int positionInArray = 0;
    for (int i = 0; i < attributes_->getSize(); ++i)
    {
        tempJson.push_back(nlohmann::ordered_json::object());
        tempJson[tempJson.size()-1][AttributeTypeConverter::EnumToFileString(attributes_->giveAttribute(i)->getType())] = nlohmann::ordered_json::array();
        auto attributeType = tempJson[i].find(AttributeTypeConverter::EnumToFileString(attributes_->giveAttribute(i)->getType()));
        if (tempJson[tempJson.size()-1].end() == attributeType)
        {
            messageHistory_.emplace_back(Message("Attribute type does not exist in this file yet!"));
            return nullptr;
        }
        attributeType.value().push_back(nlohmann::ordered_json::object());
        attributes_->giveAttribute(i)->saveToJson(attributeType.value()[attributeType.value().size() - 1], messageHistory_);
        
    }

    return tempJson;
}

void Formular::saveToFile()
{
    if (!saveWindow_)
    {
        return;
    }

    static std::filesystem::path outputPath_;
    static bool chosen = false;
    static char buffer[40] = "output";
    if (outputPath_.empty())
    {
        NFD_Init();
        nfdu8char_t *outputPath;
        nfdresult_t result = NFD_PickFolder(&outputPath, nullptr);
        if (result == NFD_OKAY)
        {
            outputPath_ = outputPath;
            NFD_FreePathU8(outputPath);
            ImGui::OpenPopup("File name window", ImGuiPopupFlags_NoReopen);
        }
        else if (result == NFD_CANCEL)
        {
            saveWindow_ = false;
            outputPath_.clear();
            return;
        }
        else
        {
            messageHistory_.emplace_back(Message(std::format("Error: {}", NFD_GetError())));
            saveWindow_ = false;
            return;
        }

        NFD_Quit();
        strcpy(buffer, "output");
    }

    if (ImGui::BeginPopup("File name window", ImGuiWindowFlags_AlwaysAutoResize))
    {

        static std::filesystem::path completedPath;
        ImGui::InputText("File name", buffer, sizeof(buffer));
        if (ImGui::Button("OK"))
        {

            completedPath = outputPath_ / std::string(buffer).append(".json");

            if (std::filesystem::exists(completedPath))
            {
                ImGui::OpenPopup("File overwrite");
            }
            else
            {
                std::fill(&buffer[0], &buffer[0] + sizeof(buffer), 0);
                outputPath_ = completedPath;
                chosen = true;
                ImGui::CloseCurrentPopup();
            }
        }
        if (ImGui::Button("Cancel"))
        {
            std::fill(&buffer[0], &buffer[0] + sizeof(buffer), 0);
            saveWindow_ = false;
            outputPath_.clear();
            ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
            return;
        }

        if (ImGui::BeginPopup("File overwrite", ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("Do you wish to overwrite existing file? Path and name of the file is: %s", completedPath.string().c_str());
            if (ImGui::Button("Yes"))
            {
                chosen = true;
                outputPath_ = completedPath;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Button("No"))
            {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        ImGui::EndPopup();
    }

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsPopupOpen("File name window"))
    {
        std::cout << ImGui::IsPopupOpen("File name window") << std::endl;
        std::fill(&buffer[0], &buffer[0] + sizeof(buffer), 0);
        saveWindow_ = false;
        outputPath_.clear();
        return;
    }

    if (chosen)
    {
        std::ofstream file(outputPath_);
        nlohmann::ordered_json json = saveOutput();
        if (json.empty())
        {
            messageHistory_.emplace_back(Message("Nothing to be saved!"));
            file.close();
            return;
        }
        file << json.dump(4);
        file.close();
        messageHistory_.emplace_back(Message(std::format("Attributes were successfully saved in the file, located in {}!", outputPath_.string())));
        chosen = false;
        saveWindow_ = false;
        outputPath_.clear();
    }
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
