#include "ImplementedAttributeDescriptions.h"

#include <format>

// INTEGER NUMBERS -------------------------------------------
template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool IntegerNumberBaseClass<TypeT, ImGuiDataTypeT, TypeEnumT>::setLimit(TypeT minimum, TypeT maximum, std::vector<Message> &messagesHistory)
{
    if (minimum < maximum)
    {
        min_ = minimum;
        max_ = maximum;
        return true;
    }
    messagesHistory.emplace_back(Message("Minimum must be lower value than maximum!"));
    return false;
}

template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool IntegerNumberBaseClass<TypeT, ImGuiDataTypeT, TypeEnumT>::jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
{
    if (json.find("Minimum") == json.end() || json.find("Maximum") == json.end() || json.find("Attribute name") == json.end())
    {
        messagesHistory.emplace_back(Message("Incorrect json format!"));
        return false;
    }
    if ((!json["Minimum"].is_number_integer() && json["Minimum"].type() != TypeEnumT) || (!json["Maximum"].is_number_integer() && json["Maximum"].type() != TypeEnumT))
    {
        messagesHistory.emplace_back(Message(std::format("{} Bounds must be number value!", json["Attribute name"].get<std::string>())));
        return false;
    }

    if (!json["Attribute name"].is_string())
    {
        messagesHistory.emplace_back(Message("Name must be string type!"));
        return false;
    }

    setName(json["Attribute name"].get<std::string>());
    return setLimit(json["Minimum"].get<TypeT>(), json["Maximum"].get<TypeT>(), messagesHistory);
}

template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool IntegerNumberBaseClass<TypeT, ImGuiDataTypeT, TypeEnumT>::drawInputForChangingLimits(std::vector<Message> &messagesHistory)
{
    if (!ImGui::IsPopupOpen("Edit limit for description"))
    {
        ImGui::OpenPopup("Edit limit for description");
    }

    ImGui::SetNextWindowSize(ImVec2(400, 300));
    if (ImGui::BeginPopupModal("Edit limit for description"), nullptr, ImGuiWindowFlags_AlwaysAutoResize)
    {
        static TypeT tmpMin = 0;
        static TypeT tmpMax = 0;
        ImGui::InputScalar("Minimum", ImGuiDataTypeT, &tmpMin, nullptr, nullptr, nullptr, ImGuiInputTextFlags_CharsDecimal);
        ImGui::InputScalar("Maximum", ImGuiDataTypeT, &tmpMax, nullptr, nullptr, nullptr, ImGuiInputTextFlags_CharsDecimal);

        if (ImGui::Button("Save"))
        {
            if (setLimit(tmpMin, tmpMax, messagesHistory))
            {
                ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
                return false;
            }
            tmpMin = 0;
            tmpMax = 0;
            return true;
        }

        ImGui::SameLine();
        if (ImGui::Button("Close"))
        {
            tmpMin = 0;
            tmpMax = 0;
            ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
            return false;
        }
        ImGui::EndPopup();
    }

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsPopupOpen("Edit limit for description"))
    {
        ImGui::EndPopup();
        return false;
    }
    return true;
}

//------------------------------------------------------

// DECIMAL NUMBERS -----------------------------------------------------
template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool DecimalNumberBaseClass<TypeT, ImGuiDataTypeT, TypeEnumT>::setLimit(TypeT minimum, TypeT maximum, std::vector<Message> &messagesHistory)
{

    if (minimum < maximum)
    {
        min_ = minimum;
        max_ = maximum;
        return true;
    }
    messagesHistory.emplace_back(Message("Minimum must be lower value than maximum!"));
    return false;
}

template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool DecimalNumberBaseClass<TypeT, ImGuiDataTypeT, TypeEnumT>::jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
{
    if (json.find("Minimum") == json.end() || json.find("Maximum") == json.end() || json.find("Attribute name") == json.end())
    {
        messagesHistory.emplace_back(Message("Incorrect json format!"));
        return false;
    }

    if (!json["Attribute name"].is_string())
    {
        messagesHistory.emplace_back(Message("Name must be string type!"));
        return false;
    }

    if ((!json["Minimum"].is_number_float() && json["Minimum"].type() != TypeEnumT) || (!json["Minimum"].is_number_float() && json["Maximum"].type() != TypeEnumT))
    {
        messagesHistory.emplace_back(Message("Bounds must be number value!"));
        return false;
    }

    setName(json["Attribute name"].get<std::string>());
    return setLimit(json["Minimum"].get<TypeT>(), json["Maximum"].get<TypeT>(), messagesHistory);
}

template <typename TypeT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool DecimalNumberBaseClass<TypeT, ImGuiDataTypeT, TypeEnumT>::drawInputForChangingLimits(std::vector<Message> &messagesHistory)
{
    if (!ImGui::IsPopupOpen("Edit limit for description"))
    {
        ImGui::OpenPopup("Edit limit for description");
    }

    ImGui::SetNextWindowSize(ImVec2(400, 300));
    if (ImGui::BeginPopupModal("Edit limit for description"), nullptr, ImGuiWindowFlags_AlwaysAutoResize)
    {
        static TypeT tmpMin = 0;
        static TypeT tmpMax = 0;
        ImGui::InputScalar("Minimum", ImGuiDataTypeT, &tmpMin, nullptr, nullptr, nullptr, ImGuiInputTextFlags_CharsDecimal);
        ImGui::InputScalar("Maximum", ImGuiDataTypeT, &tmpMax, nullptr, nullptr, nullptr, ImGuiInputTextFlags_CharsDecimal);

        if (ImGui::Button("Save"))
        {
            if (setLimit(tmpMin, tmpMax, messagesHistory))
            {
                ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
                return false;
            }
            tmpMin = 0;
            tmpMax = 0;
            return true;
        }

        ImGui::SameLine();
        if (ImGui::Button("Close"))
        {
            tmpMin = 0;
            tmpMax = 0;
            ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
            return false;
        }
        ImGui::EndPopup();
    }

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsPopupOpen("Edit limit for description"))
    {
        ImGui::EndPopup();
        return false;
    }
    return true;
}

//-------------------------------------------------------------

// BOOL --------------------------------------------------------

bool AttributeDescription_bool::jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
{
    if (json.find("Attribute name") == json.end())
    {
        messagesHistory.emplace_back(Message("Incorrect json format!"));
        return false;
    }

    if (!json["Attribute name"].is_string())
    {
        messagesHistory.emplace_back(Message("Name must be string type!"));
        return false;
    }

    setName(json["Attribute name"].get<std::string>());
    return true;
}

//----------------------------------------------------------------

// CLUSTER --------------------------------------------------------

bool AttributeDescriptionCluster::jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) { return false; }

bool AttributeDescriptionCluster::drawInputForChangingLimits(std::vector<Message> &messagesHistory)
{

    static char buffer[40] = "Attribute";
    static int selected;
    static std::string chosenType;
    static std::string category = "NUMERIC";
    static bool addedAndCorrect = false;
    static bool nameExists = false;

    if (!ImGui::IsPopupOpen(std::format("Edit window##{}", name_).c_str()))
    {
        ImGui::OpenPopup(std::format("Edit window for cluster attribute##{}", name_).c_str());
    }

    if (ImGui::BeginPopupModal(std::format("Edit window for cluster attribute##{}", name_).c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
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
                    for (int i = 0; i < descriptions_->getRegisteredDescriptionsTypes().size(); ++i)
                    {
                        if (descriptions_->getRegisteredDescriptionsTypes().at(i).getCategory().compare(category) != 0)
                        {
                            continue;
                        }
                        bool selected = (chosenType == AttributeTypeConverter::EnumToString(descriptions_->getRegisteredDescriptionsTypes().at(i).getType()));
                        if (ImGui::Selectable(std::string(AttributeTypeConverter::EnumToString(descriptions_->getRegisteredDescriptionsTypes().at(i).getType())).c_str(), selected))
                        {
                            chosenType = AttributeTypeConverter::EnumToString(descriptions_->getRegisteredDescriptionsTypes().at(i).getType());
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
                    for (int i = 0; i < descriptions_->getRegisteredDescriptionsTypes().size(); ++i)
                    {
                        if (descriptions_->getRegisteredDescriptionsTypes().at(i).getCategory().compare(category) != 0)
                        {
                            continue;
                        }
                        bool selected = (chosenType == AttributeTypeConverter::EnumToString(descriptions_->getRegisteredDescriptionsTypes().at(i).getType()));
                        if (ImGui::Selectable(std::string(AttributeTypeConverter::EnumToString(descriptions_->getRegisteredDescriptionsTypes().at(i).getType())).c_str(), selected))
                        {
                            chosenType = AttributeTypeConverter::EnumToString(descriptions_->getRegisteredDescriptionsTypes().at(i).getType());
                        }
                        if (selected)
                        {
                            ImGui::SetItemDefaultFocus();
                        }
                    }

                    ImGui::EndCombo();
                }

            default:
                break;
            }
        }
        else
        {
            ImGui::Text("%s", descriptions_->getDescription(descriptions_->getNumberOfDescriptions() - 1)->getTypeString().data());
        }

        if (!addedAndCorrect)
        {
            if (ImGui::Button("Add description"))
            {

                nameExists = (descriptions_->getDescription(buffer) != nullptr) ? true : false;
                if (!nameExists)
                {
                    descriptions_->addDescriptions(std::string(buffer), AttributeTypeConverter::StringToEnum(chosenType), messagesHistory);
                    addedAndCorrect = true;
                }
            }
        }
        else
        {
            addedAndCorrect = descriptions_->getDescription(descriptions_->getNumberOfDescriptions() - 1)->drawInputForChangingLimits(messagesHistory);
            if (ImGui::Button("Save"))
            {
                addedAndCorrect = false;
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Close"))
        {
            addedAndCorrect = false;
            ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
            return false;
        }
        ImGui::EndPopup();
    }
    return true;
}

std::unique_ptr<AttributeDescription> AttributeDescription_int::clone() { return std::make_unique<AttributeDescription_int>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescription_double::clone() { return std::make_unique<AttributeDescription_double>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescription_float::clone() { return std::make_unique<AttributeDescription_float>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescription_long::clone() { return std::make_unique<AttributeDescription_long>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescription_uint::clone() { return std::make_unique<AttributeDescription_uint>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescription_char::clone() { return std::make_unique<AttributeDescription_char>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescription_bool::clone() { return std::make_unique<AttributeDescription_bool>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescriptionCluster::clone() { return std::make_unique<AttributeDescriptionCluster>(*this); }
