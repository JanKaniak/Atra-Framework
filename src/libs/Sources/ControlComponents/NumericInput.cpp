#include "NumericInput.h"
#include "imgui.h"

// Class IntSlider
void IntSlider::draw()
{
    if ((float)(attributeint_->getMaximum() - attributeint_->getMin()) * 0.99f > minimumWidth_) {
        ImGui::PushItemWidth((float)(attributeint_->getMaximum() - attributeint_->getMin()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }
    
    if (ImGui::SliderInt(std::format("##{}", getName()).c_str(), &value_, attributeint_->getMin(), attributeint_->getMaximum()))
    {
        attributeint_->setValue(value_);
    }
    ImGui::PopItemWidth();
}
//---------------------------------------------------------------------------------------

// Class IntVSSlider
void IntVSSlider::draw()
{

    if (ImGui::VSliderInt(std::format("##{}", getName()).c_str(), ImVec2(50, 100), &value_, attributeint_->getMin(), attributeint_->getMaximum()))
    {
        attributeint_->setValue(value_);
    }
}

//---------------------------------------------------------------------------------------

// Class IntDrag
void IntDrag::draw()
{
    if ((float)(attributeint_->getMaximum() - attributeint_->getMin()) * 0.99f > minimumWidth_) {
        ImGui::PushItemWidth((float)(attributeint_->getMaximum() - attributeint_->getMin()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragInt(std::format("##{}", getName()).c_str(), &value_, 1.0f, attributeint_->getMin(), attributeint_->getMaximum()))
    {
        attributeint_->setValue(value_);
    }
    ImGui::PopItemWidth();
}





//---------------------------------------------------------------------------------------

// Class DoubleSlider
void DoubleSlider::draw() { 
    if ((float)(attributedouble_->getMaximum() - attributedouble_->getMin()) * 0.99f > minimumWidth_) {
        ImGui::PushItemWidth((float)(attributedouble_->getMaximum() - attributedouble_->getMin()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }
    
    if (ImGui::SliderScalar(std::format("##{}", getName()).c_str(), ImGuiDataType_Double, &value_, &minimum_, &maximum_)) {
        attributedouble_->setValue(value_);
    }
    ImGui::PopItemWidth();
}


//---------------------------------------------------------------------------------------

// Class DoubleVSSlider
void DoubleVSSlider::draw() {
    if (ImGui::VSliderScalar(std::format("##{}", getName()).c_str(),ImVec2(30,100),ImGuiDataType_Double,&value_, &minimum_, &maximum_)) {
        attributedouble_->setValue(value_);
    } 
}

//---------------------------------------------------------------------------------------

// Class DoubleDrag
void DoubleDrag::draw() { 
    if ((float)(attributedouble_->getMaximum() - attributedouble_->getMin()) * 0.99f > minimumWidth_) {
        ImGui::PushItemWidth((float)(attributedouble_->getMaximum() - attributedouble_->getMin()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragScalar(std::format("##{}", getName()).c_str(),ImGuiDataType_Double,&value_,0.5f, &minimum_, &maximum_)) {
        attributedouble_->setValue(value_);
    }
    ImGui::PopItemWidth();
 }

//--------------------------------------------------------------------------------------





//---------------------------------------------------------------------------------------

// Class FloatSlider
void FloatSlider::draw() {
    if ((float)(attributefloat_->getMaximum() - attributefloat_->getMin()) * 0.99f > minimumWidth_) {
        ImGui::PushItemWidth((float)(attributefloat_->getMaximum() - attributefloat_->getMin()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::SliderFloat(std::format("##{}", getName()).c_str(), &value_, minimum_, maximum_)) {
        attributefloat_->setValue(value_);
    }
    ImGui::PopItemWidth();
}


//---------------------------------------------------------------------------------------

// Class FloatVSSlider
void FloatVSSlider::draw() { 
    if (ImGui::VSliderFloat(std::format("##{}", getName()).c_str(),ImVec2(30,100),&value_, minimum_, maximum_)) {
        attributefloat_->setValue(value_);
    }
 }

//---------------------------------------------------------------------------------------

// Class FloatDrag
void FloatDrag::draw() { 
    if ((float)(attributefloat_->getMaximum() - attributefloat_->getMin()) * 0.99f > minimumWidth_) {
        ImGui::PushItemWidth((float)(attributefloat_->getMaximum() - attributefloat_->getMin()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragFloat(std::format("##{}", getName()).c_str(),&value_,0.5f, minimum_, maximum_)) {
        attributefloat_->setValue(value_);
    }
    ImGui::PopItemWidth();
 }

//--------------------------------------------------------------------------------------



