#include "NumericInput.h"
#include "imgui.h"



// Class IntSlider
void IntSlider::draw() { 
    if (ImGui::SliderInt(std::format("##{}",attributeint_->getName()).c_str(),&value_,attributeint_->getMin(),attributeint_->getMaximum())) {
        attributeint_->setValue(value_);
    }
    
}
void IntSlider::setAttribute(Attribute *attribute)
{
    if (dynamic_cast<AttributeInt *>(attribute))
    {
        attributeint_ = dynamic_cast<AttributeInt *>(attribute);
        value_ = std::get<int>(attributeint_->getValue());
        minimum_ = attributeint_->getMin();
        maximum_ = attributeint_->getMaximum();
    }
}

//---------------------------------------------------------------------------------------

// Class IntVSSlider
void IntVSSlider::draw() { ImGui::VSliderInt(std::format("##{}",attributeint_->getName()).c_str(),ImVec2(20,50), &value_, attributeint_->getMin(), attributeint_->getMaximum());}
void IntVSSlider::setAttribute(Attribute *attribute)
{
    if (dynamic_cast<AttributeInt *>(attribute))
    {
        attributeint_ = dynamic_cast<AttributeInt *>(attribute);
        value_ = std::get<int>(attributeint_->getValue());
        minimum_ = attributeint_->getMin();
        maximum_ = attributeint_->getMaximum();
        
    }
}

//---------------------------------------------------------------------------------------

// Class IntDrag
void IntDrag::draw() { ImGui::DragInt(std::format("##{}",attributeint_->getName()).c_str(),&value_,1.0f,attributeint_->getMin(),attributeint_->getMaximum()); }
void IntDrag::setAttribute(Attribute *attribute)
{
    if (dynamic_cast<AttributeInt *>(attribute))
    {
        
    
    attributeint_ = dynamic_cast<AttributeInt *>(attribute);
    value_ = std::get<int>(attributeint_->getValue());
    minimum_ = attributeint_->getMin();
    maximum_ = attributeint_->getMaximum();
    }
}

/*



//---------------------------------------------------------------------------------------

// Class DoubleSlider
void DoubleSlider::draw() { ImGui::SliderScalar(atributeName_.c_str(), ImGuiDataType_Double, &value_,&minimum_, &maximum_);}
void DoubleSlider::setAtribute(Atribute *atribute)
{
    if (AtributeDouble *aatribute = dynamic_cast<AtributeDouble *>(atribute))
    {
        atributedouble_ = aatribute;
    }
    value_ = std::get<double>(atributedouble_->getValue());
    minimum_ = atributedouble_->getMin();
    maximum_ = atributedouble_->getMaximum();
    atributeName_ = atributedouble_->getName();
    atributeType_ = atributedouble_->getType();
}

//---------------------------------------------------------------------------------------

// Class DoubleVSSlider
void DoubleVSSlider::draw() { ImGui::VSliderScalar(atributeName_.c_str(),ImVec2(50,70),ImGuiDataType_Double,&value_,&minimum_,&maximum_); }
void DoubleVSSlider::setAtribute(Atribute *atribute)
{
    if (AtributeDouble* aatribute = dynamic_cast<AtributeDouble*>(atribute))
    {
        atributedouble_ = aatribute;
    }
    value_ = std::get<double>(atributedouble_->getValue());
    minimum_ = atributedouble_->getMin();
    maximum_ = atributedouble_->getMaximum();
    atributeName_ = atributedouble_->getName();
    atributeType_ = atributedouble_->getType();
}

//---------------------------------------------------------------------------------------

// Class DoubleDrag
void DoubleDrag::draw() { ImGui::DragScalar(atributeName_.c_str(),ImGuiDataType_Double,&value_,0.5f,&minimum_, &maximum_); }
void DoubleDrag::setAtribute(Atribute *atribute)
{
    if (AtributeDouble *aatribute = dynamic_cast<AtributeDouble *>(atribute))
    {
        atributedouble_ = aatribute;
    }
    value_ = std::get<double>(atributedouble_->getValue());
    minimum_ = atributedouble_->getMin();
    maximum_ = atributedouble_->getMaximum();
    atributeName_ = atributedouble_->getName();
    atributeType_ = atributedouble_->getType();
}

//--------------------------------------------------------------------------------------



*/