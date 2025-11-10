#include "NumericInput.h"
#include "imgui.h"

// Class IntSlider
void IntSlider::draw() { 
    ImGui::SliderInt(atributeName_.c_str(),&value_,minimum_,maximum_); 
    atributeint_->setValue(value_);
}
void IntSlider::setAtribute(Atribute *atribute)
{
    if (AtributeInt *aatribute = dynamic_cast<AtributeInt *>(atribute))
    {
        atributeint_ = aatribute;
        value_ = std::stoi(atributeint_->getValue());
        minimum_ = atributeint_->getMin();
        maximum_ = atributeint_->getMaximum();
        atributeName_ = atributeint_->getName();
        atributeType_ = atributeint_->getType();
    }
}

//---------------------------------------------------------------------------------------

// Class IntVSSlider
void IntVSSlider::draw() { ImGui::VSliderInt(atributeName_.c_str(),ImVec2(20,50), &value_, minimum_, maximum_);}
void IntVSSlider::setAtribute(Atribute *atribute)
{
    if (AtributeInt *aatribute = dynamic_cast<AtributeInt *>(atribute))
    {
        atributeint_ = aatribute;
        value_ = std::atof(atributeint_->getValue().c_str());
        minimum_ = atributeint_->getMin();
        maximum_ = atributeint_->getMaximum();
        atributeName_ = atributeint_->getName();
        atributeType_ = atributeint_->getType();
    }
}

//---------------------------------------------------------------------------------------

// Class IntDrag
void IntDrag::draw() { ImGui::DragInt(atributeName_.c_str(),&value_,minimum_,maximum_); }
void IntDrag::setAtribute(Atribute *atribute)
{
    if (AtributeInt *aatribute = dynamic_cast<AtributeInt *>(atribute))
    {
        atributeint_ = aatribute;
    }
    value_ = std::atof(atributeint_->getValue().c_str());
    minimum_ = atributeint_->getMin();
    maximum_ = atributeint_->getMaximum();
    atributeName_ = atributeint_->getName();
    atributeType_ = atributeint_->getType();
}

//---------------------------------------------------------------------------------------

// Class DoubleSlider
void DoubleSlider::draw() { ImGui::SliderScalar(atributeName_.c_str(), ImGuiDataType_Double, &value_,&minimum_, &maximum_);}
void DoubleSlider::setAtribute(Atribute *atribute)
{
    if (AtributeDouble *aatribute = dynamic_cast<AtributeDouble *>(atribute))
    {
        atributedouble_ = aatribute;
    }
    value_ = std::atof(atributedouble_->getValue().c_str());
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
    value_ = std::atof(atributedouble_->getValue().c_str());
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
    value_ = std::atof(atributedouble_->getValue().c_str());
    minimum_ = atributedouble_->getMin();
    maximum_ = atributedouble_->getMaximum();
    atributeName_ = atributedouble_->getName();
    atributeType_ = atributedouble_->getType();
}

//--------------------------------------------------------------------------------------
