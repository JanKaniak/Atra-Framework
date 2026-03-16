#include "NumericInput.h"

// Class IntSlider
void IntSlider::draw(std::vector<Message> &messageHistory)
{
    if ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }
    
    if (ImGui::SliderScalar(std::format("##{}" ,getName()).c_str(),ImGuiDataType_S32 ,&value_, &minimum_, &maximum_))
    {
        attribute_->setValue(value_);
    }
    ImGui::PopItemWidth();
}
//---------------------------------------------------------------------------------------

// Class IntVSSlider
void IntVSSlider::draw(std::vector<Message> &messageHistory)
{

    if (ImGui::VSliderScalar(std::format("##{}", getName()).c_str(), ImVec2(30, 100), ImGuiDataType_S32,&value_, &minimum_ ,&maximum_))
    {
        attribute_->setValue(value_);
    }
}

//---------------------------------------------------------------------------------------

// Class IntDrag
void IntDrag::draw(std::vector<Message> &messageHistory)
{
    if ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragInt(std::format("##{}", getName()).c_str(), &value_, 1.0f, attribute_->getMinimum(), attribute_->getMaximum()))
    {
        attribute_->setValue(value_);
    }
    ImGui::PopItemWidth();
}





//---------------------------------------------------------------------------------------

// Class DoubleSlider
void DoubleSlider::draw(std::vector<Message> &messageHistory) { 
    if ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }
    
    if (ImGui::SliderScalar(std::format("##{}", getName()).c_str(), ImGuiDataType_Double, &value_, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    ImGui::PopItemWidth();
}


//---------------------------------------------------------------------------------------

// Class DoubleVSSlider
void DoubleVSSlider::draw(std::vector<Message> &messageHistory) {
    if (ImGui::VSliderScalar(std::format("##{}", getName()).c_str(),ImVec2(30,100),ImGuiDataType_Double,&value_, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    } 
}

//---------------------------------------------------------------------------------------

// Class DoubleDrag
void DoubleDrag::draw(std::vector<Message> &messageHistory) { 
    if ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragScalar(std::format("##{}", getName()).c_str(),ImGuiDataType_Double,&value_,0.5f, &minimum_, &maximum_)) {
        attribute_->setValue(value_);
    }
    ImGui::PopItemWidth();
 }

//--------------------------------------------------------------------------------------





//---------------------------------------------------------------------------------------

// Class FloatSlider
void FloatSlider::draw(std::vector<Message> &messageHistory) {
    if ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::SliderFloat(std::format("##{}", getName()).c_str(), &value_, minimum_, maximum_)) {
        attribute_->setValue(value_);
    }
    ImGui::PopItemWidth();
}


//---------------------------------------------------------------------------------------

// Class FloatVSSlider
void FloatVSSlider::draw(std::vector<Message> &messageHistory) { 
    if (ImGui::VSliderFloat(std::format("##{}", getName()).c_str(),ImVec2(30,100),&value_, minimum_, maximum_)) {
        attribute_->setValue(value_);
    }
 }

//---------------------------------------------------------------------------------------

// Class FloatDrag
void FloatDrag::draw(std::vector<Message> &messageHistory) { 
    if ((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f > minimumWidth_) {
        ImGui::PushItemWidth((float)(attribute_->getMaximum() - attribute_->getMinimum()) * 0.99f);
    } else {
        ImGui::PushItemWidth(minimumWidth_);
    }

    if (ImGui::DragFloat(std::format("##{}", getName()).c_str(),&value_,0.5f, minimum_, maximum_)) {
        attribute_->setValue(value_);
    }
    ImGui::PopItemWidth();
 }

//--------------------------------------------------------------------------------------



