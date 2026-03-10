#include "Formular.h"
#include "nfd.h"
#include "imgui_internal.h"

#include <time.h>

// Class Formular
Formular::Formular()
{
    attributes_ = std::make_unique<AttributesContainer>();
    config = Config::getInstance();
    components_ = std::make_unique<ControlComponentsContainer>();
    showAttributesWindowSize_ = ImVec2(600, 800);

    showSettingWindow_ = false;
    saveWindow_ = false;

    attributes_->addDescriptions("Address", AttributeType::CLUSTER, messageHistory_);
    AttributeDescriptionCluster *tmp = dynamic_cast<AttributeDescriptionCluster *>(attributes_->getDescription(0));
    tmp->getDescription()->addDescriptions("City Name", AttributeType::INT, messageHistory_);
    tmp->getDescription()->addDescriptions("hora7plast", AttributeType::FLOAT, messageHistory_);

    attributes_->addDescriptions("TRUTH", AttributeType::INT, messageHistory_);
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

        if (ImGui::Button("Load Attribute description", ImVec2(0, 30)))
        {
            numberOfLoadedAtributes = readFileDescriptions();
        }

        if (ImGui::Button("Add description", ImVec2(0, 30)))
        {
            ImGui::OpenPopup("Edit window", ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_NoReopen);
        }

        ImGui::BeginDisabled(attributes_->getNumberOfDescriptions() == 0);
        if (ImGui::Button("Generate attributes from descriptions", ImVec2(0, 30)))
        {
            int size = messageHistory_.size();
            if (attributes_->createAttributes(messageHistory_))
            {
                messageHistory_.emplace_back(Message("Attributes were successfuly generated from descriptions!"));
            }
            else
            {
                if (size == messageHistory_.size())
                {
                    messageHistory_.emplace_back(Message("All attributes with actual descriptions are generated!"));
                }
            }
        }
        ImGui::EndDisabled();

        ImGui::BeginDisabled(attributes_->getSize() == 0);
        if (ImGui::Button("Load Control types", ImVec2(0, 30)))
        {
            numberOfLoadedControls = readFileControlTypes();
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
            saveWindow_ = true;
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
    if (ImGui::Button("Clear logger", ImVec2(0, 30)))
    {
        messageHistory_.clear();
    }
    ImGui::EndDisabled();
}

void Formular::showAddDescriptionWindow()
{

    static char buffer[40] = "Attribute";
    static int selected;
    static std::string chosenType;
    static std::string category = "NUMERIC";
    static bool addedAndCorrect = false;

    if (ImGui::BeginPopupModal("Edit window", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::BeginDisabled(addedAndCorrect);
        if (ImGui::RadioButton("Numeric", selected == 0))
        {
            selected = 0;
            category = "NUMERIC";
            chosenType = "";
        }
        ImGui::SameLine();
        if (ImGui::RadioButton("Text", selected == 1))
        {
            selected = 1;
            category = "TEXT";
            chosenType = "";
        }

        ImGui::SameLine();
        if (ImGui::RadioButton("Logic", selected == 2))
        {
            selected = 2;
            category = "LOGIC";
            chosenType = "";
        }
        ImGui::SameLine();
        if (ImGui::RadioButton("Other", selected == 3))
        {
            selected = 3;
            category = "OTHER";
            chosenType = "";
        }
        ImGui::EndDisabled();

        ImGui::InputText("Attribute name", buffer, sizeof(buffer));
        if (nameExists)
        {
            ImGui::Text("Attribute with this name already exists!");
        }

        if (!addedAndCorrect)
        {
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
                break;

            case 1:
                break;
            case 2:
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
                break;
            case 3:
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
                break;

            default:
                break;
            }
        }
        else
        {
            ImGui::Text("%s", attributes_->getDescription(attributes_->getNumberOfDescriptions() - 1)->getTypeString().data());
        }

        if (!addedAndCorrect)
        {
            if (ImGui::Button("Add description"))
            {

                nameExists = attributes_->existDescription(buffer);
                if (!nameExists)
                {
                    attributes_->addDescriptions(std::string(buffer), AttributeTypeConverter::StringToEnum(chosenType), messageHistory_);
                    addedAndCorrect = true;
                }
            }
        }
        else
        {
            addedAndCorrect = attributes_->getDescription(attributes_->getNumberOfDescriptions() - 1)->drawInputForChangingLimits(messageHistory_);
            if (ImGui::Button("Save"))
            {
                addedAndCorrect = false;
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Close"))
        {
            ImGui::CloseCurrentPopup();
            addedAndCorrect = false;
        }
        ImGui::EndPopup();
    }
}

void Formular::showModifyControlTypesWindow()
{
    if (ImGui::BeginPopupModal("Modify control types window", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        attributes_->setControlTypes(components_.get(), config, messageHistory_);

        if (ImGui::Button("Close", ImVec2(0, 30)))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void Formular::showAttributes()
{
    if (components_->getSize() == 0)
    {
        return;
    }
    ImGui::SetNextWindowSize(showAttributesWindowSize_);
    if (ImGui::Begin("Atributes", nullptr, ImGuiWindowFlags_NoCollapse))
    {
        bool tableCreated = false;
        for (int i = 0; i < components_->getSize(); ++i)
        {
            if (components_->getComponent(i) == nullptr)
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
                ImGui::Text("%s", components_->getComponent(i)->getName().c_str());
                ImGui::TableNextColumn();
                components_->getComponent(i)->draw();
                ImGui::TableNextColumn();
                ImGui::Text("%s", AttributeTypeConverter::EnumToString(components_->getComponent(i)->getAttribute(components_->getComponent(i)->getName())->getType()).data());
                ImGui::TableNextColumn();
                if (ImGui::Button("Edit", ImVec2(0, 30)))
                {
                    drawed = true;
                    chosenAttribute = components_->getComponent(i)->getAttribute(components_->getComponent(i)->getName());
                }
                ImGui::TableNextColumn();
                if (ImGui::Button("Delete", ImVec2(0, 30)))
                {
                    deleteAttribute(components_->getComponent(i)->getAttribute(components_->getComponent(i)->getName()));
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

    static ControlComponent *component;
    static char editBuffer[40] = "";
    if (ImGui::BeginPopup("Edit window"))
    {
        static bool exist;
        static bool changingLimits = false;
        if (component == nullptr)
        {
            component = components_->getControlComponentByAttribute(chosenAttribute);
        }
        if (editBuffer[0] == '\0')
        {
            strcpy(editBuffer, chosenAttribute->getName().c_str());
        }
        ImGui::InputText("Attribute name", editBuffer, sizeof(editBuffer));
        if (exist)
        {
            ImGui::Text("%s", "Attribute with this name already exists!");
        }
        ImGui::Text("Attribute type: %s", AttributeTypeConverter::EnumToString(chosenAttribute->getType()).data());

        if (ImGui::Button("Save", ImVec2(0, 30)))
        {
            if (attributes_->giveAttributeByName(chosenAttribute->getName()) == chosenAttribute)
            {
                exist = false;
            }
            else
            {
                exist = (attributes_->giveAttributeByName(editBuffer) == nullptr) ? false : true;
            }

            if (!exist)
            {
                exist = false;
                attributes_->giveAttributeByName(chosenAttribute->getName())->getDescription()->setName(editBuffer);
                component = nullptr;
                ImGui::CloseCurrentPopup();
            }
            else
            {
                exist = true;
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Edit description"))
        {
            changingLimits = true;
        }
        ImGui::SameLine();
        if (changingLimits)
        {
            changingLimits = chosenAttribute->getDescription()->drawInputForChangingLimits(messageHistory_);
        }
        if (ImGui::Button("Close", ImVec2(0, 30)))
        {
            component = nullptr;
            ImGui::CloseCurrentPopup();
            std::memset(editBuffer, 0, sizeof(editBuffer[0]));
        }
        else
        {
            if (component != nullptr)
            {
                component->updateLimitValues();
            }
        }
        ImGui::EndPopup();
    }

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsPopupOpen("Edit window"))
    {
        component = nullptr;
        std::memset(editBuffer, 0, sizeof(editBuffer[0]));
    }

    ImGui::End();
}

void Formular::editAttribute(Attribute *attribute)
{
    if (chosenAttribute == nullptr)
    {
        return;
    }
}

void Formular::deleteAttribute(Attribute *attribute)
{
    components_->deleteControlComponent(attribute);
    if (!attributes_->deleteAttribute(attribute))
    {
        messageHistory_.emplace_back(Message("Attribute does not exist!"));
    }
    else
    {
        messageHistory_.emplace_back(Message("Attribute was deleted!"));
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
        Attribute *attribute = attributes_->giveAttribute(i);
        tempJson.push_back(nlohmann::ordered_json::object());
        tempJson[positionInArray][AttributeTypeConverter::EnumToFileString(attribute->getType())] = nlohmann::ordered_json::array();
        if (tempJson.empty())
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
            auto attributeType = tempJson[positionInArray].find(AttributeTypeConverter::EnumToFileString(attributes_->giveAttribute(j)->getType()));
            if (tempJson[positionInArray].end() == attributeType)
            {
                messageHistory_.emplace_back(Message("Attribute type does not exist in this file yet!"));
                return false;
            }
            attributeType.value().push_back(nlohmann::ordered_json::object());
            attributes_->giveAttribute(j)->saveToJson(attributeType.value()[attributeType.value().size() - 1], messageHistory_);
        }
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

