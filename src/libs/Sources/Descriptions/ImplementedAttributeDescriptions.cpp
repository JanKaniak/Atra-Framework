#include "ImplementedAttributeDescriptions.h"

#include <format>

AttributeDescription::~AttributeDescription() = default;



// INTEGER NUMBERS -------------------------------------------
template <typename TypeT, AttributeType AttributeTypeEnumT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool IntegerNumberBaseClass<TypeT, AttributeTypeEnumT, ImGuiDataTypeT, TypeEnumT>::setLimit(TypeT minimum, TypeT maximum, std::vector<Message> &messagesHistory)
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

template <typename TypeT, AttributeType AttributeTypeEnumT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool IntegerNumberBaseClass<TypeT, AttributeTypeEnumT, ImGuiDataTypeT, TypeEnumT>::jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
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

template <typename TypeT, AttributeType AttributeTypeEnumT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool IntegerNumberBaseClass<TypeT, AttributeTypeEnumT, ImGuiDataTypeT, TypeEnumT>::drawInputForChangingLimits(std::vector<Message> &messagesHistory)
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

template <typename TypeT, AttributeType AttributeTypeEnumT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
void IntegerNumberBaseClass<TypeT, AttributeTypeEnumT, ImGuiDataTypeT, TypeEnumT>::addItselfToVectorByCondition(std::vector<AttributeDescription*>& vector,AttributeType type) {
    if (type == AttributeTypeEnumT) {
        vector.emplace_back(this);
    }
}

//------------------------------------------------------

// DECIMAL NUMBERS -----------------------------------------------------
template <typename TypeT, AttributeType AttributeTypeEnumT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool DecimalNumberBaseClass<TypeT, AttributeTypeEnumT, ImGuiDataTypeT, TypeEnumT>::setLimit(TypeT minimum, TypeT maximum, std::vector<Message> &messagesHistory)
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

template <typename TypeT, AttributeType AttributeTypeEnumT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool DecimalNumberBaseClass<TypeT, AttributeTypeEnumT, ImGuiDataTypeT, TypeEnumT>::jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
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

template <typename TypeT, AttributeType AttributeTypeEnumT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool DecimalNumberBaseClass<TypeT, AttributeTypeEnumT, ImGuiDataTypeT, TypeEnumT>::drawInputForChangingLimits(std::vector<Message> &messagesHistory)
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

template <typename TypeT, AttributeType AttributeTypeEnumT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
void DecimalNumberBaseClass<TypeT, AttributeTypeEnumT, ImGuiDataTypeT, TypeEnumT>::addItselfToVectorByCondition(std::vector<AttributeDescription*>& vector,AttributeType type) {
    if (type == AttributeTypeEnumT) {
        vector.emplace_back(this);
    }
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

void AttributeDescription_bool::addItselfToVectorByCondition(std::vector<AttributeDescription*>& vector,AttributeType type) {
    if (type == type_) {
        vector.emplace_back(this);
    }
}

//----------------------------------------------------------------

// CLUSTER --------------------------------------------------------

bool AttributeDescriptionCluster::jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory) { 
    if (json.find("Attribute name") == json.end() || json.find("Attribute descriptions") == json.end())
    {
        messagesHistory.emplace_back(Message("Incorrect json format!"));
        return false;
    }

    if (!json["Attribute name"].is_string())
    {
        messagesHistory.emplace_back(Message("Name must be string type!"));
        return false;
    }

    if (!json["Attribute descriptions"].is_array())
    {
        messagesHistory.emplace_back(Message("Attribute descriptions must be in array!"));
        return false;
    }

    setName(json["Attribute name"].get<std::string>());
    nlohmann::ordered_json theJson = json.find("Attribute descriptions").value();
    for (auto &descriptions : theJson) // attributeDescriptions = list of attributes, attributeTypeKey = attribute type
    {

        for (auto &descriptionsOfTheSameType : descriptions.items())
        {
            std::cout << descriptionsOfTheSameType.key() << "\n\n";
            std::cout << descriptionsOfTheSameType.value() << "\n\n\n\n\n";
            if (!descriptions_->addDescriptions(AttributeTypeConverter::StringToEnum(descriptionsOfTheSameType.key()), descriptionsOfTheSameType.value(), messagesHistory))
            {
                return false;
            }
        }
    }
    return true;

 }

bool AttributeDescriptionCluster::drawInputForChangingLimits(std::vector<Message> &messagesHistory)
{
    return false;
}


void AttributeDescriptionCluster::addItselfToVectorByCondition(std::vector<AttributeDescription*>& vector,AttributeType type) {
    if (type == type_) {
        vector.emplace_back(this);
    }
    descriptions_->findDescriptionsByType(vector,type);
}

AttributeDescriptionsContainer* AttributeDescriptionCluster::getContainer(std::string_view descriptionName,uint64_t descriptionId) {
    if (descriptionName.empty() || (descriptionName.compare(name_) == 0 && descriptionId == id_)) {
        return descriptions_.get();
    }
    return descriptions_->findDescriptionContainer(descriptionName, descriptionId);
}

AttributeDescriptionCluster::~AttributeDescriptionCluster() {
    descriptions_ = nullptr;
}



std::unique_ptr<AttributeDescription> AttributeDescription_int::clone() { return std::make_unique<AttributeDescription_int>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescription_double::clone() { return std::make_unique<AttributeDescription_double>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescription_float::clone() { return std::make_unique<AttributeDescription_float>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescription_long::clone() { return std::make_unique<AttributeDescription_long>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescription_uint::clone() { return std::make_unique<AttributeDescription_uint>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescription_char::clone() { return std::make_unique<AttributeDescription_char>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescription_bool::clone() { return std::make_unique<AttributeDescription_bool>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescriptionCluster::clone() { return std::make_unique<AttributeDescriptionCluster>(*this); }
