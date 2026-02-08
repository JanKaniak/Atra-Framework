#pragma once

#include "json.hpp"
#include "imgui.h"
#include <string>
#include <variant>
#include <memory>

//ukldať pre jednotlivé deskripce (tych ktorých sa to týka) imguidatatype na input
//switch + macro X(INT, S16), X(string, null)
//



#define Attribute_types \
    Attribute_type(INT) \
    Attribute_type(DOUBLE) \
    Attribute_type(FLOAT) \
    Attribute_type(LONG) \
    Attribute_type(UINT) \
    Attribute_type(CHAR)


enum class AttributeType {
#define Attribute_type(attributeType) attributeType,
    Attribute_types
#undef Attribute_type
};

class AttributeTypeConverter {
    private:
    static AttributeTypeConverter *instance_;
    AttributeTypeConverter() = default;

private:
std::map<std::string, AttributeType> stringToEnum = {
    #define Attribute_type(attributeType)  { #attributeType, AttributeType::attributeType },
    Attribute_types
    #undef Attribute_type
};

std::map<AttributeType, std::string> enumToString = {
    #define Attribute_type(attributeType)  { AttributeType::attributeType, #attributeType },
    Attribute_types
    #undef Attribute_type
};

    public:
    std::string convertEnumToString(AttributeType type) {
        if (enumToString.find(type) == enumToString.end()) {
            return "";
        }
        return enumToString[type];

    }

    AttributeType convertStringtoEnum(std::string type) {
        return stringToEnum[type]; 
    }

    static AttributeTypeConverter *getInstance() {
        static AttributeTypeConverter *instance_;
        if (instance_ == nullptr) {
            return new AttributeTypeConverter();
        }
        return instance_;
    }


};





/*enum class Category {
    NUMERIC,
    TEXT,
    OTHER
};*/


class AttributeDescription
{
protected:
    std::string name_;
    AttributeType type_;
    std::string category_;
    ImGuiDataType dataType_;

public:
    AttributeDescription(AttributeType type) : type_(type) {};
    inline std::string getName() { return name_; };
    inline AttributeType getType() { return type_; };
    inline std::string getTypeString() { return AttributeTypeConverter::getInstance()->convertEnumToString(type_); }
    inline std::string getCategory() { return category_; };
    inline void setName(std::string name) { name_ = name; };
    inline void setCategory(std::string category) { category_ = category;}
    inline ImGuiDataType getDataType() { return dataType_;}

public:
    virtual ~AttributeDescription() = default;
    virtual std::unique_ptr<AttributeDescription> clone() = 0;
    virtual bool jsonParse(nlohmann::ordered_json &json, std::string &outputMessage) = 0;
};




