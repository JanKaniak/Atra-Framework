#include "Formular.h"
#include "nfd.h"
#include "imgui_internal.h"

#include <time.h>

// Class Formular

/// Initialize the formular manager, its attribute descriptions, runtime attributes, and UI components.
Formular::Formular()
{
    attributeDescs_ = std::make_unique<AttributesDescriptionsContainer>();
    attributes_ = std::make_unique<AttributesContainer>(attributeDescs_.get());
    components_ = std::make_unique<ControlComponentsContainer>(attributes_.get());
    showAttributesWindowSize_ = ImVec2(600, 800);
    templateDescriptions_ = TemplateAttributesDescriptionContainer::getInstance();
    chosenAttributesDescription_ = attributeDescs_.get();

    addDescriptionWindow_ = false;
    saveWindow_ = false;
    useDefaultControls_ = true;
    openedWindow_ = false;
    overWriteExistingControls_ = false;

    numberOfLoadedAtributes_ = INT_MAX;
    numberOfLoadedControls_ = INT_MAX;
}

/// Add a control type to the formular by matching an attribute path and edit control type name.
bool Formular::addControlTypeByNames(std::string_view path, std::string editType)
{
    if (attributes_->getAttributeByPath(path.data()) == nullptr)
    {
        &messageHistory_.emplace_back(Message(std::format("Attribute with name {} does not exist!", path.data())));
        return false;
    }
    return components_->addControlTypeByNames(path.data(), editType, messageHistory_);
}

/// Assign a default control type to an attribute identified by its path.
bool Formular::addDefaultControlType(std::string_view path)
{
    if (attributes_->getAttributeByPath(path.data()) == nullptr)
    {
        &messageHistory_.emplace_back("Attribute pointer can't be null!");
        return false;
    }
    return components_->addDefaultControlType(path.data(), messageHistory_);
}

/// Replace the control type for an existing attribute using a raw attribute pointer.
bool Formular::replaceControlType(Attribute *attribute, std::string editType)
{
    if (attribute == nullptr)
    {
        &messageHistory_.emplace_back("Attribute pointer can't be null!");
        return false;
    }
    return components_->swapControlComponentByAttribute(attribute, editType, messageHistory_);
}

/// Replace the control type for an attribute identified by its path string.
bool Formular::replaceControlType(std::string_view path, std::string editType)
{
    Attribute *tmpAttribute = attributes_->getAttributeByPath(path.data());
    if (tmpAttribute == nullptr)
    {
        &messageHistory_.emplace_back("Attribute pointer can't be null!");
        return false;
    }
    return components_->swapControlComponentByAttribute(tmpAttribute, editType, messageHistory_);
}

/// Add a new attribute description under the given path and return the created description.
AttributeDescription *Formular::addDescription(std::string_view path,std::string_view attributeName, AttributeType type)
{
    if (attributeDescs_->addDescriptionByPath(path.data(),attributeName.data(), type, &messageHistory_))
    {
        return attributeDescs_->getLast();
    }
    return nullptr;
}

/// Add an attribute description object to the formular and return it if successful.
AttributeDescription *Formular::addDescription(std::unique_ptr<AttributeDescription> attributeDescription)
{
    if (attributeDescs_->addDescription(std::move(attributeDescription)))
    {
        return attributeDescs_->getLast();
    }
    return nullptr;
}

/// Create runtime attribute instances from the registered attribute descriptions.
bool Formular::createAttributes()
{
    return attributes_->createAttributes(messageHistory_);
}

/// Render the main formular UI window with control loading, generation, and template actions.
void Formular::showControls()
{
    static float f = 0.0f;
    static int counter = 0;
    static bool resized = false;

    if (!resized)
    {
        ImGui::SetNextWindowSize(ImVec2(650, 800));
        resized = true;
    }
    if (ImGui::Begin("Main", nullptr, ImGuiWindowFlags_NoCollapse))
    {
        showLogger();

        if (ImGui::BeginChild("First button group", ImVec2(0, 0), ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_Borders))
        {
            if (ImGui::Button("Load Attribute description", ImVec2(190, 30)))
            {
                numberOfLoadedAtributes_ = readFileDescriptions();
            }

            ImGui::BeginDisabled(attributes_->getSize() == 0);
            if (ImGui::Button("Load Control types", ImVec2(190, 30)))
            {
                numberOfLoadedControls_ = readFileControlTypes();
            }
            ImGui::SameLine();
            ImGui::Checkbox("Use default controls", &useDefaultControls_);
            ImGui::SameLine();
            ImGui::Checkbox("Overwrite existing controls", &overWriteExistingControls_);
            ImGui::EndDisabled();

            ImGui::EndChild();
            ImGui::Dummy(ImVec2(190, 30));
        }

        if (ImGui::Button("Add description", ImVec2(190, 30)))
        {
            addDescriptionWindow_ = true;
            chosenAttributesDescription_ = attributeDescs_.get();
        }

        if (ImGui::Button("Create templates", ImVec2(190, 30)))
        {
            ImGui::OpenPopup("Template edit window", ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_NoReopen);
        }

        ImGui::BeginDisabled(templateDescriptions_->getSize() == 0);
        if (ImGui::Button("Create from templates", ImVec2(190, 30)))
        {
            ImGui::OpenPopup("Template create attributes", ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_NoReopen);
        }
        ImGui::EndDisabled();

        ImGui::BeginDisabled(attributes_->getNumberOfDescriptions() == 0);
        if (ImGui::Button("Generate attributes", ImVec2(190, 30)))
        {
            attributes_->createAttributes(messageHistory_);
            &messageHistory_.emplace_back(Message("All attributes with actual descriptions are generated!"));
        }
        ImGui::EndDisabled();
        ImGui::BeginDisabled(templateDescriptions_->getSize() == 0);
        if (ImGui::Button("Manage templates", ImVec2(190, 30)))
        {
            ImGui::OpenPopup("Templates");
        }
        ImGui::EndDisabled();
        ImGui::BeginDisabled(attributes_->getSize() == 0);

        if (ImGui::Button("Modify control types", ImVec2(190, 30)))
        {
            ImGui::OpenPopup("Modify control types window", ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_NoReopen);
        }
        ImGui::EndDisabled();

        ImGui::BeginDisabled(attributeDescs_->getSize() == 0);
        if (ImGui::Button("Delete All", ImVec2(190, 30)))
        {
            components_->deleteAllControlComponents(messageHistory_);
            attributes_->deleteAllAttributes(messageHistory_);
            attributeDescs_->deleteAllDescriptions(&messageHistory_);
        }
        ImGui::EndDisabled();

        ImGui::BeginDisabled(attributes_->getSize() == 0);
        if (ImGui::Button("Save", ImVec2(190, 30)))
        {
            saveWindow_ = true;
        }
        ImGui::EndDisabled();

        showAddDescriptionWindow(chosenAttributesDescription_, true);
        showModifyControlTypesWindow();
        saveToFile();
        showCreateTemplateAttribute();
        showCreateAttributesFromTemplates();
        showWindowManageTemplates();
        ImGui::End();
    }
}

/// Render the logger panel showing recent user messages and errors.
void Formular::showLogger()
{
    float width = ImGui::GetContentRegionAvail().x;
    if (ImGui::BeginChild("Logger", ImVec2(width * 0.999999f, 300), ImGuiChildFlags_Borders, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar))
    {

        for (int i = 0; i < messageHistory_.size(); ++i)
        {
            ImGui::Text("%s", messageHistory_.at(i).getTimeString().c_str());
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

/// Display the popup window used to add or edit attribute descriptions.
void Formular::showAddDescriptionWindow(AttributesDescriptionsContainer *attributeDesc, bool isCreatingAttributesOutsideClusterAllowed)
{

    if (!ImGui::IsPopupOpen("Edit window") && addDescriptionWindow_)
    {
        ImGui::OpenPopup("Edit window");
        addDescriptionWindow_ = false;
    }

    static char buffer[40] = "Attribute";
    static int selected;
    static std::string chosenType;
    static std::string chosenLevelName;
    static uint64_t chosenLevelNameId;
    static std::string category = "NUMERIC";
    static bool addedAndCorrect = false;
    static std::vector<AttributeDescription *> clusterDescriptions;
    static AttributesDescriptionsContainer *descriptionContainer;
    static bool nameExists = false;

    if (ImGui::BeginPopupModal("Edit window", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (clusterDescriptions.empty())
        {
            clusterDescriptions.push_back(nullptr);
            attributeDesc->findDescriptionsByType(clusterDescriptions, AttributeType::CLUSTER);
            chosenLevelName = "NULL";
        }

        if (isCreatingAttributesOutsideClusterAllowed)
        {
            ImGui::BeginDisabled(addedAndCorrect);
        }
        else
        {
            ImGui::BeginDisabled(addedAndCorrect && (chosenLevelName.compare("NULL") == 0));
        }

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
                for (int i = 0; i < attributeDesc->getRegisteredDescriptionsTypes().size(); ++i)
                {
                    if (attributeDesc->getRegisteredDescriptionsTypes().at(i).getCategory().compare(category) != 0)
                    {
                        continue;
                    }
                    bool selected = (chosenType == AttributeTypeConverter::EnumToString(attributeDesc->getRegisteredDescriptionsTypes().at(i).getType()));
                    if (ImGui::Selectable(std::string(AttributeTypeConverter::EnumToString(attributeDesc->getRegisteredDescriptionsTypes().at(i).getType())).c_str(), selected))
                    {
                        chosenType = AttributeTypeConverter::EnumToString(attributeDesc->getRegisteredDescriptionsTypes().at(i).getType());
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
            if (ImGui::Button("Add description", ImVec2(190, 30)))
            {
                if (descriptionContainer == nullptr)
                {
                    descriptionContainer = attributeDesc->getDescriptionContainer(chosenLevelName, chosenLevelNameId);
                }

                nameExists = descriptionContainer->existsDescription(buffer);
                if (!nameExists)
                {
                    descriptionContainer->addDescription(std::string(buffer), AttributeTypeConverter::StringToEnum(chosenType), &messageHistory_);
                    addedAndCorrect = true;
                }
            }
            ImGui::EndDisabled();
        }
        else
        {
            addedAndCorrect = descriptionContainer->getLast()->drawInputForChangingLimits(&messageHistory_);
            if (!addedAndCorrect)
            {
                chosenLevelName = "NULL";
                descriptionContainer = nullptr;
                clusterDescriptions.clear();
            }
        }
        if (!addedAndCorrect)
        {
            ImGui::SameLine();
        }
        if (ImGui::Button("Close", ImVec2(190, 30)))
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

/// Display the popup for modifying control types assigned to existing attributes.
void Formular::showModifyControlTypesWindow()
{
    static ImVec2 size = ImVec2(400, 300);
    static bool sizeSet = false;
    if (!sizeSet)
    {
        ImGui::SetNextWindowSize(size);
        sizeSet = true;
    }

    if (ImGui::BeginPopupModal("Modify control types window", nullptr))
    {
        if (ImGui::BeginTable("Control types", 3))
        {
            ImGui::TableSetupColumn("Attribute name");
            ImGui::TableSetupColumn("Attribute type");
            ImGui::TableSetupColumn("Control type");
            ImGui::TableHeadersRow();
            attributes_->setControlTypes(components_.get(), messageHistory_);
            ImGui::EndTable();
        }

        if (ImGui::Button("Close", ImVec2(190, 30)))
        {
            sizeSet = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

/// Display the UI for creating a new attribute template description.
void Formular::showCreateTemplateAttribute()
{
    static char buffer[40];
    static bool successfullyAdded = true;
    static bool openWindow = false;
    if (ImGui::BeginPopupModal("Template edit window", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        openWindow = true;
        ImGui::InputText("Template name", buffer, sizeof(buffer));
        if (ImGui::Button("Add description", ImVec2(190, 30)))
        {
            templateDescriptions_->addTemplateDescription(buffer, &messageHistory_);
            chosenAttributesDescription_ = templateDescriptions_->getContainer(buffer);
            addDescriptionWindow_ = true;
        }
        ImGui::SameLine();
        if (ImGui::Button("Close", ImVec2(190, 30)))
        {
            openWindow = false;
            chosenAttributesDescription_ = attributeDescs_.get();
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

/// Display the popup for selecting a template and generating attributes from it.
void Formular::showCreateAttributesFromTemplates()
{

    if (ImGui::BeginPopupModal("Template create attributes"))
    {
        static bool created = false;
        static std::string chosenTemplate;
        if (chosenTemplate.empty())
        {
            templateDescriptions_->getNameByPosition(0);
        }
        if (ImGui::BeginCombo("##Template attribute descriptions", chosenTemplate.c_str()))
        {
            for (int i = 0; i < templateDescriptions_->getSize(); ++i)
            {
                bool open = (chosenTemplate == templateDescriptions_->getTemplateByPosition(i)->getName());
                if (ImGui::Selectable(templateDescriptions_->getTemplateByPosition(i)->getName().c_str(), open))
                {
                    chosenTemplate = templateDescriptions_->getNameByPosition(i);
                }

                if (open)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        if (ImGui::Button("OK"))
        {
            if (!chosenTemplate.empty())
            {
                chosenAttributesDescription_ = templateDescriptions_->getContainer(chosenTemplate);
                chosenTemplate = "";
                ImGui::CloseCurrentPopup();
                created = true;
            }
        }
        ImGui::EndPopup();

        if (created)
        {
            attributeDescs_->addDescriptions(chosenAttributesDescription_, &messageHistory_);
            attributes_->createAttributes(messageHistory_);
            created = false;
        }
    }
}

/// Render the attribute control window once controls have been created.
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

/// Load attribute descriptions from JSON data into the formular.
bool Formular::loadDescriptions(nlohmann::ordered_json json)
{
    for (auto &descriptions : json) // attributeDescriptions = list of attributes, attributeTypeKey = attribute type
    {

        for (auto &descriptionsOfTheSameType : descriptions.items())
        {
            if (!attributes_->addDescription(AttributeTypeConverter::StringToEnum(descriptionsOfTheSameType.key()), descriptionsOfTheSameType.value(), messageHistory_))
            {
                return false;
            }
        }
    }
    &messageHistory_.emplace_back(Message(std::format("Successfully loaded {} attributes descriptions!", attributes_->getNumberOfDescriptions())));
    return true;
}

/// Prompt the user to select a JSON file and read attribute descriptions from it.
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
        &messageHistory_.emplace_back(Message(std::format("Error: {}", NFD_GetError())));
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
        &messageHistory_.emplace_back(Message("File does not exist!"));
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

/// Prompt the user to select a JSON file and read control type definitions from it.
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
        &messageHistory_.emplace_back(Message(std::format("Error: {}, ", NFD_GetError())));
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
        &messageHistory_.emplace_back(Message("File does not exist!"));
        return -1;
    }

    nlohmann::json jsonFile = nlohmann::json::parse(file);
    file.close();
    return loadControlTypes(jsonFile);
}
/// Load control types from JSON data and apply them to existing attributes.
int Formular::loadControlTypes(nlohmann::json json)
{
    int tmpNumberOfLoadedControls = 0;
    int tmpOverWrittedControls = 0;
    if (attributes_->getSize() == 0)
    {
        &messageHistory_.emplace_back(Message("Before creating control types attributes must exist!"));
        return -1;
    }
    for (int i = 0; i < attributes_->getSize(); i++)
    {
        auto editType = json.find(attributes_->giveAttribute(i)->getName());
        if (editType == json.end())
        {
            if (!useDefaultControls_)
            {
                continue;
            }

            if (components_->existControlType(attributes_->giveAttribute(i)->getName()))
            {
                continue;
            }

            if (!components_->addControl(attributes_->giveAttribute(i), messageHistory_))
            {
                return -1;
            }
            continue;
        }

        if (!editType.value().is_string())
        {
            components_->clear();
            &messageHistory_.emplace_back(Message("Control type name must be a string!"));
            return -1;
        }

        if (components_->existControlType(editType.key()))
        {
            if (!overWriteExistingControls_)
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

        if (!components_->addControlTypeByNames(attributes_->giveAttribute(i)->getName(), editType.value(), messageHistory_))
        {
            return -1;
        }
        tmpNumberOfLoadedControls++;
    }
    if (tmpOverWrittedControls > 0)
    {
        &messageHistory_.emplace_back(Message(std::format("{} controls were successfuly overwritten!", tmpOverWrittedControls)));
        return tmpOverWrittedControls;
    }
    if (tmpNumberOfLoadedControls == 0)
    {
        &messageHistory_.emplace_back(Message("Either control types in file have incorrect names or you're trying to overwrite existing control types, check you file or enable overwritting."));
        return -1;
    }
    if (tmpNumberOfLoadedControls < components_->getSize())
    {
        &messageHistory_.emplace_back(Message(std::format("Successfully loaded {} controls and some attributes were given default control types because they were missing in a file!", tmpNumberOfLoadedControls)));
    }
    else if (tmpNumberOfLoadedControls == components_->getSize())
    {
        &messageHistory_.emplace_back(Message(std::format("Successfully loaded {} control!s", tmpNumberOfLoadedControls)));
    }
    return tmpNumberOfLoadedControls;
}

/// Serialize the current attribute set to ordered JSON for saving to disk.
nlohmann::ordered_json Formular::saveOutput()
{
    nlohmann::ordered_json tempJson;
    tempJson = nlohmann::ordered_json::array();
    int positionInArray = 0;
    for (int i = 0; i < attributes_->getSize(); ++i)
    {
        tempJson.push_back(nlohmann::ordered_json::object());
        tempJson[tempJson.size() - 1][AttributeTypeConverter::EnumToFileString(attributes_->giveAttribute(i)->getType())] = nlohmann::ordered_json::array();
        auto attributeType = tempJson[i].find(AttributeTypeConverter::EnumToFileString(attributes_->giveAttribute(i)->getType()));
        if (tempJson[tempJson.size() - 1].end() == attributeType)
        {
            &messageHistory_.emplace_back(Message("Attribute type does not exist in this file yet!"));
            return nullptr;
        }
        attributeType.value().push_back(nlohmann::ordered_json::object());
        attributes_->giveAttribute(i)->saveToJson(attributeType.value()[attributeType.value().size() - 1], messageHistory_);
    }

    return tempJson;
}

/// Manage the save dialog and write the current attributes to a JSON file.
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
            &messageHistory_.emplace_back(Message(std::format("Error: {}", NFD_GetError())));
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
        if (ImGui::Button("OK", ImVec2(100, 30)))
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
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(100, 30)))
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
            if (ImGui::Button("Yes", ImVec2(100, 30)))
            {
                chosen = true;
                outputPath_ = completedPath;
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("No", ImVec2(100, 30)))
            {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        ImGui::EndPopup();
    }

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsPopupOpen("File name window"))
    {
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
            &messageHistory_.emplace_back(Message("Nothing to be saved!"));
            file.close();
            return;
        }
        file << json.dump(4);
        file.close();
        &messageHistory_.emplace_back(Message(std::format("Attributes were successfully saved in the file, located in {}!", outputPath_.string())));
        chosen = false;
        saveWindow_ = false;
        outputPath_.clear();
    }
}

/// Display a warning window with a custom error message.
bool Formular::showWarning(std::string message)
{
    ImGui::SetNextWindowSize(ImVec2(500, 400));
    if (ImGui::Begin("Warning window", &openedWindow_, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
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

/// Render the template management popup, allowing template editing and deletion.
void Formular::showWindowManageTemplates()
{
    static ImVec2 size = ImVec2(400, 300);
    static TemplateAttributesDescription *templateContainer = nullptr;
    static bool open = false;
    static bool editing = false;
    static bool sizeSet = false;
    if (templateDescriptions_->getSize() == 0)
    {
        return;
    }

    if (!sizeSet)
    {
        ImGui::SetNextWindowSize(size);
        sizeSet = true;
    }
    if (ImGui::BeginPopup("Templates", ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (ImGui::BeginTable("Template table", 3))
        {
            ImGui::TableSetupColumn("Template name");
            ImGui::TableSetupColumn("Edit");
            ImGui::TableSetupColumn("Delete");
            ImGui::TableHeadersRow();
            for (int i = 0; i < templateDescriptions_->getSize(); ++i)
            {
                ImGui::TableNextRow();
                if (templateDescriptions_->getTemplateByPosition(i) == nullptr)
                {
                    continue;
                }

                ImGui::TableNextColumn();
                ImGui::Text("%s", templateDescriptions_->getTemplateByPosition(i)->getName().c_str());
                ImGui::TableNextColumn();
                ImGui::BeginDisabled(templateDescriptions_->getTemplateByPosition(i)->getContainer()->getSize() == 0);
                if (ImGui::Button("Edit", ImVec2(60, 30)))
                {
                    templateContainer = templateDescriptions_->getTemplateByPosition(i);
                    open = true;
                }
                ImGui::EndDisabled();
                ImGui::TableNextColumn();
                if (ImGui::Button("Delete", ImVec2(60, 30)))
                {
                    templateDescriptions_->removeTemplateDescription(templateDescriptions_->getTemplateByPosition(i));
                }
            }

            ImGui::EndTable();
        }

        if (open && !ImGui::IsPopupOpen("Edit template"))
        {
            ImGui::OpenPopup("Edit template");
            open = false;
        }
        static ImVec2 sizeEditTemplate = ImVec2(400, 300);
        static bool sizeSetEditTemplate = false;
        if (!sizeSetEditTemplate)
        {
            ImGui::SetNextWindowSize(size);
            sizeSetEditTemplate = true;
        }
        if (ImGui::BeginPopupModal("Edit template", nullptr))
        {
            static AttributeDescription *chosenDescription = nullptr;

            if (ImGui::BeginTable("Descriptions of template", 3))
            {
                ImGui::TableSetupColumn("Attribute description name");
                ImGui::TableSetupColumn("Edit");
                ImGui::TableSetupColumn("Delete");
                ImGui::TableHeadersRow();
                for (int i = 0; i < templateContainer->getContainer()->getSize(); ++i)
                {
                    ImGui::TableNextRow();
                    if (templateContainer->getContainer()->getDescription(i) == nullptr)
                    {
                        continue;
                    }
                    ImGui::TableNextColumn();
                    ImGui::Text("%s", templateContainer->getContainer()->getDescription(i)->getName().c_str());
                    ImGui::TableNextColumn();
                    if (ImGui::Button("Edit", ImVec2(60, 30)))
                    {
                        chosenDescription = templateContainer->getContainer()->getDescription(i);
                        editing = true;
                    }
                    ImGui::TableNextColumn();
                    if (ImGui::Button("Delete", ImVec2(60, 30)))
                    {
                        templateContainer->getContainer()->deleteDescription(templateContainer->getContainer()->getDescription(i));
                    }
                }

                ImGui::EndTable();
            }

            if (editing)
            {
                editing = chosenDescription->drawInputForChangingLimits(&messageHistory_);
            }
            if (ImGui::Button("Close", ImVec2(80, 30)))
            {
                open = false;
                sizeSetEditTemplate = false;
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        if (ImGui::Button("Close", ImVec2(80, 30)))
        {
            sizeSet = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

/// Add a new log message to the formular's internal history.
bool Formular::addLogMessage(std::string message)
{
    if (message.empty())
    {
        &messageHistory_.emplace_back("Message can't be empty!");
        return false;
    }
    &messageHistory_.emplace_back(message);
    return true;
}

/// Clear all stored logger entries from the formular.
bool Formular::clearLogger()
{
    messageHistory_.clear();
    return true;
}

/// Retrieve an attribute by path, supporting both direct names and nested path notation.
Attribute *Formular::getAttribute(std::string_view path)
{
    if (path.empty())
    {
        return nullptr;
    }

    if (path.find_first_of(".", 0) == path.npos)
    {
        return attributes_->giveAttributeByName(path.data());
    }

    return attributes_->getAttributeByPath(path.data());
}

/// Delete all control components, runtime attributes, and attribute descriptions.
void Formular::deleteAll()
{
    components_->deleteAllControlComponents(messageHistory_);
    attributes_->deleteAllAttributes(messageHistory_);
    attributeDescs_->deleteAllDescriptions(&messageHistory_);
}

/// Create a named template entity for reusable attribute description groups.
bool Formular::createTemplateEntity(std::string_view name) {
    if (name.empty()) {
        messageHistory_.emplace_back("Name cannot be empty!");
        return false;
    }
    return templateDescriptions_->addTemplateDescription(name,&messageHistory_);
}
/// Add a description to an existing template entity by path and type.
bool Formular::addDescriptionToEntity(std::string_view entityName,std::string_view path, std::string_view descriptionName, AttributeType type) {
    if (descriptionName.empty()) {
        messageHistory_.emplace_back("Name cannot be empty!");
        return false;
    }
    AttributesDescriptionsContainer *tmpContainer = templateDescriptions_->getContainer(entityName);
    if (tmpContainer == nullptr) {
        messageHistory_.emplace_back("Template container does not exists!");
        return false;
    }
    return tmpContainer->addDescriptionByPath(path.data(),descriptionName.data(),type,&messageHistory_);
}
/// Retrieve an attribute description from a template entity using path and name.
AttributeDescription *Formular::getAttributeDescriptionFromEntity(std::string_view entityName, std::string_view path, std::string_view name) {
    if (entityName.empty()) {
        messageHistory_.emplace_back("Description name cannot be empty!");
        return nullptr;
    }
    AttributesDescriptionsContainer *tmpContainer = templateDescriptions_->getContainer(entityName);
    if (tmpContainer == nullptr) {
        messageHistory_.emplace_back("Template container does not exists!");
        return nullptr;
    }
    return tmpContainer->getDescriptionByPath(path.data(),name.data(), messageHistory_);
}
/// Delete a description from a named template entity.
bool Formular::deleteDescriptionFromEntity(std::string_view entityName, std::string_view path, std::string_view name) {
    if (name.empty() || entityName.empty()) {
        messageHistory_.emplace_back("Description name or entity name cannot be empty!");
        return false;
    }
    AttributesDescriptionsContainer *tmpContainer = templateDescriptions_->getContainer(entityName);
    if (tmpContainer == nullptr) {
        messageHistory_.emplace_back("Template container does not exists!");
        return false;
    }
    return tmpContainer->deleteDescriptionByPath(path.data(),name.data());
}
/// Delete a named template entity from the formular.
bool Formular::deleteTemplateEntity(std::string_view name) {
    if (name.empty()) {
        messageHistory_.emplace_back("Name cannot be empty!");
        return false;
    }
    return templateDescriptions_->removeTemplateDescription(name);
}