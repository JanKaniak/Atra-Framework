#include "ControlComponent.h"
template <EditTypeInt TYPE>
void ControlComponentInt<TYPE>::setAttribute(Attribute *attribute)
    {
        controlType_ = EditTypeIntConverter::getInstance()->enumToStringConverter(type_);
        if (dynamic_cast<AttributeInt *>(attribute))
        {
            attributeInt_ = dynamic_cast<AttributeInt *>(attribute);
            value_ = attributeInt_->getValue();
            minimum_ = attributeInt_->getMin();
            maximum_ = attributeInt_->getMaximum();
        }
    }

template <EditTypeDouble TYPE>
    void ControlComponentDouble<TYPE>::setAttribute(Attribute *attribute) 
    {
        controlType_ = EditTypeDoubleConverter::getInstance()->enumToStringConverter(type_);
        if (dynamic_cast<AttributeDouble *>(attribute))
        {
            attributeDouble_ = dynamic_cast<AttributeDouble *>(attribute);
            value_ = attributeDouble_->getValue();
            minimum_ = attributeDouble_->getMin();
            maximum_ = attributeDouble_->getMaximum();
        }
    }

template <EditTypeFloat TYPE>
    void ControlComponentFloat<TYPE>::setAttribute(Attribute *attribute) 
    {
        controlType_ = EditTypeFloatConverter::getInstance()->enumToStringConverter(type_);
        if (dynamic_cast<AttributeFloat *>(attribute))
        {
            attributeFloat_ = dynamic_cast<AttributeFloat *>(attribute);
            value_ = attributeFloat_->getValue();
            minimum_ = attributeFloat_->getMin();
            maximum_ = attributeFloat_->getMaximum();
        }
    }

template <EditTypeChar TYPE>
    void ControlComponentChar<TYPE>::setAttribute(Attribute *attribute) 
    {
        controlType_ = EditTypeCharConverter::getInstance()->enumToStringConverter(type_);
        if (dynamic_cast<AttributeChar *>(attribute))
        {
            attributeChar_ = dynamic_cast<AttributeChar *>(attribute);
            value_ = attributeChar_->getValue();
            minimum_ = attributeChar_->getMin();
            maximum_ = attributeChar_->getMaximum();
        }
    }