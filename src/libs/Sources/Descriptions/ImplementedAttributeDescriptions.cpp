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
    messagesHistory.emplace_back(Message(std::format("Error with attribute description: {}, minimum must be lower value than maximum!",name_)));
    return false;
}

template <typename TypeT, AttributeType AttributeTypeEnumT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
bool IntegerNumberBaseClass<TypeT, AttributeTypeEnumT, ImGuiDataTypeT, TypeEnumT>::jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
{
    if (json.find("Minimum") == json.end() || json.find("Maximum") == json.end() || json.find("Attribute name") == json.end())
    {

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
    static bool isSetLastLimit = false;
    static TypeT tmpMin = 0;
    static TypeT tmpMax = 0;

    if (!isSetLastLimit) {
        tmpMin = min_;
        tmpMax = max_;
        isSetLastLimit = true;
    }
    if (!ImGui::IsPopupOpen("Edit limit for description"))
    {
        ImGui::OpenPopup("Edit limit for description");
    }

    ImGui::SetNextWindowSize(ImVec2(0, 112));
    if (ImGui::BeginPopupModal("Edit limit for description"), nullptr, ImGuiWindowFlags_AlwaysAutoResize)
    {

        ImGui::InputScalar("Minimum", ImGuiDataTypeT, &tmpMin, nullptr, nullptr, nullptr, ImGuiInputTextFlags_CharsDecimal);
        ImGui::InputScalar("Maximum", ImGuiDataTypeT, &tmpMax, nullptr, nullptr, nullptr, ImGuiInputTextFlags_CharsDecimal);

        if (ImGui::Button("Save",ImVec2(60,30)))
        {
            if (setLimit(tmpMin, tmpMax, messagesHistory))
            {
                isSetLastLimit = false;
                ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
                return false;
            }
            isSetLastLimit = false;
            ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
            return true;
        }

        ImGui::SameLine();
        if (ImGui::Button("Close",ImVec2(60,30)))
        {
            isSetLastLimit = false;
            ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
            return false;
        }
        ImGui::EndPopup();
    }

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsPopupOpen("Edit limit for description"))
    {
        isSetLastLimit = false;
        ImGui::EndPopup();
        return false;
    }
    return true;
}

template <typename TypeT, AttributeType AttributeTypeEnumT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
void IntegerNumberBaseClass<TypeT, AttributeTypeEnumT, ImGuiDataTypeT, TypeEnumT>::addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type)
{
    if (type == AttributeTypeEnumT)
    {
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
    messagesHistory.emplace_back(Message(std::format("Error with attribute description: {}, minimum must be lower value than maximum!",name_)));
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
    static bool isSetLastLimit = false;
    static TypeT tmpMin = 0;
    static TypeT tmpMax = 0;

    if (!isSetLastLimit) {
        tmpMin = min_;
        tmpMax = max_;
        isSetLastLimit = true;
    }
    if (!ImGui::IsPopupOpen("Edit limit for description"))
    {
        ImGui::OpenPopup("Edit limit for description");
    }

    ImGui::SetNextWindowSize(ImVec2(400, 300));
    if (ImGui::BeginPopupModal("Edit limit for description"), nullptr, ImGuiWindowFlags_AlwaysAutoResize)
    {

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
            isSetLastLimit = false;
            ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
            return true;
        }

        ImGui::SameLine();
        if (ImGui::Button("Close"))
        {
            isSetLastLimit = false;
            ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
            return false;
        }
        ImGui::EndPopup();
    }

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsPopupOpen("Edit limit for description"))
    {
        isSetLastLimit = false;
        ImGui::EndPopup();
        return false;
    }
    return true;
}

template <typename TypeT, AttributeType AttributeTypeEnumT, ImGuiDataType ImGuiDataTypeT, nlohmann::json::value_t TypeEnumT>
void DecimalNumberBaseClass<TypeT, AttributeTypeEnumT, ImGuiDataTypeT, TypeEnumT>::addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type)
{
    if (type == AttributeTypeEnumT)
    {
        vector.emplace_back(this);
    }
}

//-------------------------------------------------------------

// BOOL --------------------------------------------------------

bool AttributeDescriptionBool::jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
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

void AttributeDescriptionBool::addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type)
{
    if (type == type_)
    {
        vector.emplace_back(this);
    }
}

//----------------------------------------------------------------

// CLUSTER --------------------------------------------------------

bool AttributeDescriptionCluster::jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
{
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
            if (!descriptions_->addDescription(AttributeTypeConverter::StringToEnum(descriptionsOfTheSameType.key()), descriptionsOfTheSameType.value(), messagesHistory))
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

void AttributeDescriptionCluster::addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type)
{
    if (type == type_)
    {
        vector.emplace_back(this);
    }
    descriptions_->findDescriptionsByType(vector, type);
}

AttributesDescriptionsContainer *AttributeDescriptionCluster::getContainer(std::string_view descriptionName, uint64_t descriptionId)
{
    if (descriptionName.empty() || (descriptionName.compare(name_) == 0 && descriptionId == id_))
    {
        return descriptions_.get();
    }
    return descriptions_->findDescriptionContainer(descriptionName, descriptionId);
}

AttributeDescriptionCluster::~AttributeDescriptionCluster()
{
    descriptions_ = nullptr;
}

//--------------------------------------------------------------

// CHAR text ---------------------------------------------------

bool AttributeDescriptionCharText::setLimit(uint8_t minimum, uint8_t maximum, std::vector<Message> &messagesHistory)
{
    if ((minimum < maximum) || (minimum > 0 && minimum <= maximum))
    {
        min_ = minimum;
        max_ = maximum;
        return true;
    }
    messagesHistory.emplace_back(Message(std::format("Error with attribute description: {}, minimum must be lower value than maximum!",name_)));
    return false;
}

bool AttributeDescriptionCharText::jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
{
    if (json.find("Minimum") == json.end() || json.find("Maximum") == json.end() || json.find("Attribute name") == json.end())
    {
        messagesHistory.emplace_back(Message("Incorrect json format!"));
        return false;
    }
    if ((!json["Minimum"].is_number_integer() && json["Minimum"].type() != nlohmann::ordered_json::value_t::number_unsigned) || (!json["Maximum"].is_number_integer() && json["Maximum"].type() != nlohmann::ordered_json::value_t::number_unsigned))
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
    return setLimit(json["Minimum"].get<uint8_t>(), json["Maximum"].get<uint8_t>(), messagesHistory);
}


bool AttributeDescriptionCharText::drawInputForChangingLimits(std::vector<Message> &messagesHistory)
{
   static bool isSetLastLimit = false;
    static uint8_t tmpMin = 0;
    static uint8_t tmpMax = 0;

    if (!isSetLastLimit) {
        tmpMin = min_;
        tmpMax = max_;
        isSetLastLimit = true;
    }
    if (!ImGui::IsPopupOpen("Edit limit for description"))
    {
        ImGui::OpenPopup("Edit limit for description");
    }

    ImGui::SetNextWindowSize(ImVec2(0, 112));
    if (ImGui::BeginPopupModal("Edit limit for description"), nullptr, ImGuiWindowFlags_AlwaysAutoResize)
    {

        ImGui::InputScalar("Minimum", dataType_, &tmpMin, nullptr, nullptr, nullptr, ImGuiInputTextFlags_CharsDecimal);
        ImGui::InputScalar("Maximum", dataType_, &tmpMax, nullptr, nullptr, nullptr, ImGuiInputTextFlags_CharsDecimal);

        if (ImGui::Button("Save",ImVec2(60,30)))
        {
            if (setLimit(tmpMin, tmpMax, messagesHistory))
            {
                isSetLastLimit = false;
                ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
                return false;
            }
            isSetLastLimit = false;
            ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
            return true;
        }

        ImGui::SameLine();
        if (ImGui::Button("Close",ImVec2(60,30)))
        {
            isSetLastLimit = false;
            ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
            return false;
        }
        ImGui::EndPopup();
    }

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsPopupOpen("Edit limit for description"))
    {
        isSetLastLimit = false;
        ImGui::EndPopup();
        return false;
    }
    return true;
}


void AttributeDescriptionCharText::addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type)
{
    if (type == type_)
    {
        vector.emplace_back(this);
    }
}

//----------------------------------------------------------------

// STRING ---------------------------------------------------

bool AttributeDescriptionString::setLimit(uint32_t minimum, uint32_t maximum, std::vector<Message> &messagesHistory)
{
    if (minimum < maximum)
    {
        min_ = minimum;
        max_ = maximum;
        return true;
    }
    messagesHistory.emplace_back(Message(std::format("Error with attribute description: {}, minimum must be lower value than maximum!",name_)));
    return false;
}

bool AttributeDescriptionString::jsonParse(nlohmann::ordered_json &json, std::vector<Message> &messagesHistory)
{
    if (json.find("Minimum") == json.end() || json.find("Maximum") == json.end() || json.find("Attribute name") == json.end())
    {
        messagesHistory.emplace_back(Message("Incorrect json format!"));
        return false;
    }
    if ((!json["Minimum"].is_number_integer() && json["Minimum"].type() != nlohmann::ordered_json::value_t::number_unsigned) || (!json["Maximum"].is_number_integer() && json["Maximum"].type() != nlohmann::ordered_json::value_t::number_unsigned))
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
    return setLimit(json["Minimum"].get<uint32_t>(), json["Maximum"].get<uint32_t>(), messagesHistory);
}


bool AttributeDescriptionString::drawInputForChangingLimits(std::vector<Message> &messagesHistory)
{
    static bool isSetLastLimit = false;
    static uint32_t tmpMin = 0;
    static uint32_t tmpMax = 0;

    if (!isSetLastLimit) {
        tmpMin = min_;
        tmpMax = max_;
        isSetLastLimit = true;
    }
    if (!ImGui::IsPopupOpen("Edit limit for description"))
    {
        ImGui::OpenPopup("Edit limit for description");
    }

    ImGui::SetNextWindowSize(ImVec2(0, 112));
    if (ImGui::BeginPopupModal("Edit limit for description"), nullptr, ImGuiWindowFlags_AlwaysAutoResize)
    {

        ImGui::InputScalar("Minimum", dataType_, &tmpMin, nullptr, nullptr, nullptr, ImGuiInputTextFlags_CharsDecimal);
        ImGui::InputScalar("Maximum", dataType_, &tmpMax, nullptr, nullptr, nullptr, ImGuiInputTextFlags_CharsDecimal);

        if (ImGui::Button("Save",ImVec2(60,30)))
        {
            if (setLimit(tmpMin, tmpMax, messagesHistory))
            {
                isSetLastLimit = false;
                ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
                return false;
            }
            isSetLastLimit = false;
            ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
            return true;
        }

        ImGui::SameLine();
        if (ImGui::Button("Close",ImVec2(60,30)))
        {
            isSetLastLimit = false;
            ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
            return false;
        }
        ImGui::EndPopup();
    }

    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsPopupOpen("Edit limit for description"))
    {
        isSetLastLimit = false;
        ImGui::EndPopup();
        return false;
    }
    return true;
}


void AttributeDescriptionString::addItselfToVectorByCondition(std::vector<AttributeDescription *> &vector, AttributeType type)
{
    if (type == type_)
    {
        vector.emplace_back(this);
    }
}

//----------------------------------------------------------------











std::unique_ptr<AttributeDescription> AttributeDescriptionInt::clone() { return std::make_unique<AttributeDescriptionInt>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescriptionDouble::clone() { return std::make_unique<AttributeDescriptionDouble>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescriptionFloat::clone() { return std::make_unique<AttributeDescriptionFloat>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescriptionLong::clone() { return std::make_unique<AttributeDescriptionLong>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescriptionUint::clone() { return std::make_unique<AttributeDescriptionUint>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescriptionCharNumber::clone() { return std::make_unique<AttributeDescriptionCharNumber>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescriptionBool::clone() { return std::make_unique<AttributeDescriptionBool>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescriptionCluster::clone() { return std::make_unique<AttributeDescriptionCluster>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescriptionCharText::clone() { return std::make_unique<AttributeDescriptionCharText>(*this); }

std::unique_ptr<AttributeDescription> AttributeDescriptionString::clone() { return std::make_unique<AttributeDescriptionString>(*this); }
