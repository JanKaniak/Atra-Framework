#pragma once
#include "AttributesContainer.h"
#include <variant>

#define Edit_type_int \
    X_INT(DEFAULT) \
    X_INT(SLIDER) \
    X_INT(VSLIDER) \
    X_INT(DRAG)



#define Edit_type_double \
    X_DOUBLE(DEFAULT) \
    X_DOUBLE(SLIDER) \
    X_DOUBLE(VSLIDER) \
    X_DOUBLE(DRAG)

#define Edit_type_float \
    X_FLOAT(DEFAULT) \
    X_FLOAT(SLIDER) \
    X_FLOAT(VSLIDER) \
    X_FLOAT(DRAG)

#define Edit_type_text \
    X_TEXT(DEFAULT) \
    X_TEXT(TEXT)


enum class EditTypeInt {
    #define X_INT(editType) editType,
    Edit_type_int
    #undef X_INT
};

enum class EditTypeDouble {
    #define X_DOUBLE(editType) editType,
    Edit_type_double
    #undef X_DOUBLE
};

enum class EditTypeFloat {
    #define X_FLOAT(editType) editType,
    Edit_type_float
    #undef X_FLOAT
};

enum class EditTypeChar {
    #define X_TEXT(editType) editType,
    Edit_type_text
    #undef X_TEXT
};

/*#define Master_list \
    Register_master(EditTypeInt) \
    Register_master(EditTypeDouble) \
    Register_master(EditTypeFloat) \
    Register_master(EditTypeText) 

#define Register_master(enumType) \
    std::string EnumToString(enumType editType) { \
        switch (editType) { \
            case enumType : return #editType; \
        } \
        return ""; \
    } \
    \
Master_list 
#undef Register_master 



#define Attribute_type(attributeType) \
class ConverterEnumAndString##attributeType { \
    private: \
    static ConverterEnumAndString##attributeType *instance_; \
    public: \
    ConverterEnumAndString##attributeType *getInstance() { \
        static ConverterEnumAndString##attributeType *instance_; \
        if (instance_ == nullptr) { \
            return instance_ = new ConverterEnumAndString##attributeType(); \
        } \
        return instance_; \
    } \
    \
    
}; 
Attribute_types
#undef Attribute_type*/
























class EditTypeIntConverter {
private:
    std::map<EditTypeInt, std::string> enumToString = {
        #define X_INT(editType) {EditTypeInt::editType, #editType},
        Edit_type_int
        #undef X_INT
    };

    std::map<std::string, EditTypeInt> stringToEnum = {
        #define X_INT(editType) {#editType, EditTypeInt::editType},
        Edit_type_int
        #undef X_INT
    };
    
private:
    static EditTypeIntConverter *instance_;
    EditTypeIntConverter() = default;
public:
    static EditTypeIntConverter *getInstance() {
       static EditTypeIntConverter *instance_;
       if (instance_ == nullptr) {
        return new EditTypeIntConverter();
       } 
       return instance_;
    }
     std::string enumToStringConverter(EditTypeInt type) {
        if (enumToString.find(type) == enumToString.end()) {
            return "";
        }
        return enumToString[type];
    }

    bool containsEnum(std::string type) {
        if (stringToEnum.find(type) == stringToEnum.end()) {
            return false;
        }
        return true;
    }

    EditTypeInt stringToEnumConverter(std::string type) {
        if (stringToEnum.find(type) == stringToEnum.end()) {
            return EditTypeInt::DEFAULT;
        }
        return stringToEnum[type];

    }

    bool containsString(EditTypeInt type) {
        if (enumToString.find(type) == enumToString.end()) {
            return false;
        }
        return true;
    }

};




class EditTypeDoubleConverter {
private:
    std::unordered_map<EditTypeDouble, std::string> enumToString = {
        #define X_DOUBLE(editType) {EditTypeDouble::editType, #editType},
        Edit_type_double
        #undef X_DOUBLE
    };

    std::unordered_map<std::string, EditTypeDouble> stringToEnum = {
        #define X_DOUBLE(editType) {#editType, EditTypeDouble::editType},
        Edit_type_double
        #undef X_DOUBLE
    };
    
private:
    static EditTypeDoubleConverter *instance_;
    EditTypeDoubleConverter() = default;
public:
    static EditTypeDoubleConverter *getInstance() {
       static EditTypeDoubleConverter *instance_;
       if (instance_ == nullptr) {
        return new EditTypeDoubleConverter();
       } 
       return instance_;
    }

     std::string enumToStringConverter(EditTypeDouble type) {
        if (enumToString.find(type) == enumToString.end()) {
            return "";
        }
        return enumToString[type];
    }

    bool containsEnum(std::string type) {
        if (stringToEnum.find(type) == stringToEnum.end()) {
            return false;
        }
        return true;
    }

    EditTypeDouble stringToEnumConverter(std::string type) {
        return stringToEnum[type];

    }

    bool containsString(EditTypeDouble type) {
        if (enumToString.find(type) == enumToString.end()) {
            return false;
        }
        return true;
    }
};







class EditTypeFloatConverter {
private:
    std::map<EditTypeFloat, std::string> enumToString = {
        #define X_FLOAT(editType) {EditTypeFloat::editType, #editType},
        Edit_type_float
        #undef X_FLOAT
    };

    std::map<std::string, EditTypeFloat> stringToEnum = {
        #define X_FLOAT(editType) {#editType, EditTypeFloat::editType},
        Edit_type_float
        #undef X_FLOAT
    };
    
private:
    static EditTypeFloatConverter *instance_;
    EditTypeFloatConverter() = default;
public:
    static EditTypeFloatConverter *getInstance() {
       static EditTypeFloatConverter *instance_;
       if (instance_ == nullptr) {
        return new EditTypeFloatConverter();
       } 
       return instance_;
    }


     std::string enumToStringConverter(EditTypeFloat type) {
        if (enumToString.find(type) == enumToString.end()) {
            return "";
        }
        return enumToString[type];
    }

    bool containsEnum(std::string type) {
        if (stringToEnum.find(type) == stringToEnum.end()) {
            return false;
        }
        return true;
    }

    EditTypeFloat stringToEnumConverter(std::string type) {
        return stringToEnum[type];

    }

    bool containsString(EditTypeFloat type) {
        if (enumToString.find(type) == enumToString.end()) {
            return false;
        }
        return true;
    }
};


class EditTypeCharConverter {
private:
    std::map<EditTypeChar, std::string> enumToString = {
        #define X_TEXT(editType) {EditTypeChar::editType, #editType},
        Edit_type_text
        #undef X_TEXT
    };

    std::map<std::string, EditTypeChar> stringToEnum = {
        #define X_TEXT(editType) {#editType, EditTypeChar::editType},
        Edit_type_text
        #undef X_TEXT
    };
    
private:
    static EditTypeCharConverter *instance_;
    EditTypeCharConverter() = default;
public:
    static EditTypeCharConverter *getInstance() {
       static EditTypeCharConverter *instance_;
       if (instance_ == nullptr) {
        return new EditTypeCharConverter();
       } 
       return instance_;
    }


     std::string enumToStringConverter(EditTypeChar type) {
        if (enumToString.find(type) == enumToString.end()) {
            return "";
        }
        return enumToString[type];
    }

    bool containsEnum(std::string type) {
        if (stringToEnum.find(type) == stringToEnum.end()) {
            return false;
        }
        return true;
    }

    EditTypeChar stringToEnumConverter(std::string type) {
        return stringToEnum[type];

    }

    bool containsString(EditTypeChar type) {
        if (enumToString.find(type) == enumToString.end()) {
            return false;
        }
        return true;
    }
};










class ControlComponent
{
protected:
    std::string controlType_;

    public:
    std::string getType() { return controlType_; };

public:
    virtual void draw() = 0;
    virtual std::string getName() = 0;
    virtual ~ControlComponent() = default;
    virtual void setAttribute(Attribute *attribute) = 0;
    virtual std::unique_ptr<ControlComponent> clone() = 0;
    virtual Attribute *getAttribute() = 0;
};






#define Control_components \
    X(Int,int) \
    X(Double,double) \
    X(Float,float) \
    X(Char, char)


#define X(attributeTypeName,type) \
template <EditType##attributeTypeName TYPE> \
class ControlComponent##attributeTypeName : public ControlComponent \
{ \
protected: \
    type value_; \
    type minimum_; \
    type maximum_; \
    Attribute##attributeTypeName *attribute##attributeTypeName##_; \
    float minimumWidth_; \
 \
public: \
    static constexpr EditType##attributeTypeName type_ = TYPE; \
    void setAttribute(Attribute *attribute) override \
    { \
        controlType_ = EditType##attributeTypeName##Converter::getInstance()->enumToStringConverter(type_); \
        if (dynamic_cast<Attribute##attributeTypeName *>(attribute)) \
        { \
            attribute##attributeTypeName##_ = dynamic_cast<Attribute##attributeTypeName *>(attribute); \
            value_ = attribute##attributeTypeName##_->getValue(); \
            minimum_ = attribute##attributeTypeName##_->getMinimum(); \
            maximum_ = attribute##attributeTypeName##_->getMaximum(); \
        } \
    } \
    std::string getName() override { return attribute##attributeTypeName##_->getName(); }; \
    Attribute *getAttribute() override { return attribute##attributeTypeName##_; }; \
};
Control_components
#undef X



/*template <EditTypeInt TYPE>
class ControlComponentInt : public ControlComponent
{
protected:
    int value_;
    int minimum_;
    int maximum_;
    AttributeInt *attributeint_;
    float minimumWidth_;

public:
    static constexpr EditTypeInt type_ = TYPE;
    void setAttribute(Attribute *attribute) override;
    std::string getName() override { return attributeint_->getName(); };
    Attribute *getAttribute() override { return attributeint_; };
};

template <EditTypeDouble TYPE>
class ControlComponentDouble : public ControlComponent
{
protected:
    double value_;
    double minimum_;
    double maximum_;
    AttributeDouble *attributedouble_;
    float minimumWidth_;

public:
    static constexpr EditTypeDouble type_ = TYPE;
    void setAttribute(Attribute *attribute) override;
    std::string getName() override { return attributedouble_->getName(); };
    Attribute *getAttribute() override { return attributedouble_; };
};

template <EditTypeFloat TYPE>
class ControlComponentFloat : public ControlComponent
{
protected:
    float value_;
    float minimum_;
    float maximum_;
    AttributeFloat *attributefloat_;
    float minimumWidth_;

public:
    static constexpr EditTypeFloat type_ = TYPE;
    void setAttribute(Attribute *attribute) override;
    std::string getName() override { return attributefloat_->getName(); };
    Attribute *getAttribute() override { return attributefloat_; };
};


template <EditTypeText TYPE>
class ControlComponentChar : public ControlComponent
{
protected:
    char value_;
    int minimum_;
    int maximum_;
    AttributeChar *attributechar_;
    float minimumWidth_;

public:
    static constexpr EditTypeText type_ = TYPE;
    void setAttribute(Attribute *attribute) override;
    std::string getName() override { return attributechar_->getName(); };
    Attribute *getAttribute() override { return attributechar_; };
};
*/