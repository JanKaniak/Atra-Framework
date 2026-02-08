#include "NumericInput.h"

// Class IntSlider
void IntSlider::draw()
{
    if ((float)(attributeInt_->getMaximum() - attributeInt_->getMin()) * 0.99f > minimumWidth_) {
        ImGui::PushItemWidth((float)(attributeInt_->getMaximum() - attributeInt_->getMin()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }
    
    if (ImGui::SliderScalar(std::format("##{}" ,getName()).c_str(),ImGuiDataType_S32 ,&value_, &minimum_, &maximum_))
    {
        attributeInt_->setValue(value_);
    }
    ImGui::PopItemWidth();
}
//---------------------------------------------------------------------------------------

// Class IntVSSlider
void IntVSSlider::draw()
{

    if (ImGui::VSliderScalar(std::format("##{}", getName()).c_str(), ImVec2(30, 100), ImGuiDataType_S32,&value_, &minimum_ ,&maximum_))
    {
        attributeInt_->setValue(value_);
    }
}

//---------------------------------------------------------------------------------------

// Class IntDrag
void IntDrag::draw()
{
    if ((float)(attributeInt_->getMaximum() - attributeInt_->getMin()) * 0.99f > minimumWidth_) {
        ImGui::PushItemWidth((float)(attributeInt_->getMaximum() - attributeInt_->getMin()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragInt(std::format("##{}", getName()).c_str(), &value_, 1.0f, attributeInt_->getMin(), attributeInt_->getMaximum()))
    {
        attributeInt_->setValue(value_);
    }
    ImGui::PopItemWidth();
}





//---------------------------------------------------------------------------------------

// Class DoubleSlider
void DoubleSlider::draw() { 
    if ((float)(attributeDouble_->getMaximum() - attributeDouble_->getMin()) * 0.99f > minimumWidth_) {
        ImGui::PushItemWidth((float)(attributeDouble_->getMaximum() - attributeDouble_->getMin()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }
    
    if (ImGui::SliderScalar(std::format("##{}", getName()).c_str(), ImGuiDataType_Double, &value_, &minimum_, &maximum_)) {
        attributeDouble_->setValue(value_);
    }
    ImGui::PopItemWidth();
}


//---------------------------------------------------------------------------------------

// Class DoubleVSSlider
void DoubleVSSlider::draw() {
    if (ImGui::VSliderScalar(std::format("##{}", getName()).c_str(),ImVec2(30,100),ImGuiDataType_Double,&value_, &minimum_, &maximum_)) {
        attributeDouble_->setValue(value_);
    } 
}

//---------------------------------------------------------------------------------------

// Class DoubleDrag
void DoubleDrag::draw() { 
    if ((float)(attributeDouble_->getMaximum() - attributeDouble_->getMin()) * 0.99f > minimumWidth_) {
        ImGui::PushItemWidth((float)(attributeDouble_->getMaximum() - attributeDouble_->getMin()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragScalar(std::format("##{}", getName()).c_str(),ImGuiDataType_Double,&value_,0.5f, &minimum_, &maximum_)) {
        attributeDouble_->setValue(value_);
    }
    ImGui::PopItemWidth();
 }

//--------------------------------------------------------------------------------------





//---------------------------------------------------------------------------------------

// Class FloatSlider
void FloatSlider::draw() {
    if ((float)(attributeFloat_->getMaximum() - attributeFloat_->getMin()) * 0.99f > minimumWidth_) {
        ImGui::PushItemWidth((float)(attributeFloat_->getMaximum() - attributeFloat_->getMin()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::SliderFloat(std::format("##{}", getName()).c_str(), &value_, minimum_, maximum_)) {
        attributeFloat_->setValue(value_);
    }
    ImGui::PopItemWidth();
}


//---------------------------------------------------------------------------------------

// Class FloatVSSlider
void FloatVSSlider::draw() { 
    if (ImGui::VSliderFloat(std::format("##{}", getName()).c_str(),ImVec2(30,100),&value_, minimum_, maximum_)) {
        attributeFloat_->setValue(value_);
    }
 }

//---------------------------------------------------------------------------------------

// Class FloatDrag
void FloatDrag::draw() { 
    if ((float)(attributeFloat_->getMaximum() - attributeFloat_->getMin()) * 0.99f > minimumWidth_) {
        ImGui::PushItemWidth((float)(attributeFloat_->getMaximum() - attributeFloat_->getMin()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragFloat(std::format("##{}", getName()).c_str(),&value_,0.5f, minimum_, maximum_)) {
        attributeFloat_->setValue(value_);
    }
    ImGui::PopItemWidth();
 }

//--------------------------------------------------------------------------------------



